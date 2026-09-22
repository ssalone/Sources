#!/bin/sh
#################################################################
# FILE:    libtests.cmd
# PURPOSE: Run Singular library test suites written with test.lib
#          (TestSuite/TestCase/expectEqual/expectComparedBy) and
#          report a non-zero exit status if any test fails.
# USAGE:
#   libtests.cmd [-s <Singular>] [file.sng ...]
#     [-s <Singular>]  -- use <Singular> as executable (default:
#                          $SINGULAR_BIN or "Singular" from $PATH)
#     [file.sng ...]   -- run only the given scripts (default: all
#                          *.sng found next to this script)
# OUTPUT:
#   - console summary (see below)
#   - libtests-junit.xml  JUnit-style XML report (written into the
#                          current working directory) for use with
#                          CI systems (GitHub test annotations etc.)
#   - libtests-ctrf.json  CTRF (Concise Test Report Format) JSON
#                          report, the standardized JSON format for
#                          test results (https://ctrf.io); the
#                          JSON-native alternative to JUnit XML
# ENVIRONMENT:
#   SINGULAR_BIN     -- default binary, overridden by -s
#   LIBTESTS_TIMEOUT -- per-script timeout in seconds (default: 600,
#                          0 disables the timeout)
#
# A test script foo.sng is expected to load test.lib and to run one
# or more TestSuite(...) blocks.  Each TestSuite writes a CTRF test
# report "<suite name>.ctrf.json" next to the script.  Since Singular
# almost always exits with status 0 (even on runtime errors), failures
# are detected from
#   (a) the "status" fields in the CTRF reports,
#   (b) missing CTRF reports (a runtime error aborted the suite),
#   (c) Singular error messages (" ? ") in the output log,
#   (d) internal crashes ("Singular : signal ..." / "Segment fault"
#       lines in the output log: Singular may crash, restart itself,
#       still write all reports and exit 0),
#   (e) a non-zero process exit status (hard crash / timeout).
#################################################################

set -u

mydir=`dirname "$0"`
singular="${SINGULAR_BIN:-Singular}"
timeout_secs="${LIBTESTS_TIMEOUT:-600}"
junitfile="libtests-junit.xml"
ctrffile="libtests-ctrf.json"

while getopts "s:h" opt; do
  case "$opt" in
    s) singular="$OPTARG" ;;
    h) sed -n '2,35p' "$0"; exit 0 ;;
    *) sed -n '2,35p' "$0"; exit 1 ;;
  esac
done
shift $((OPTIND - 1))

# Space-safe collection of scripts: always re-glob from the directory
# when no explicit files are given.
if [ $# -gt 0 ]; then
  set -- "$@"
else
  set --
  for f in "$mydir"/*.sng; do
    [ -e "$f" ] && set -- "$@" "$f"
  done
fi

if [ $# -eq 0 ]; then
  echo "libtests: no test scripts (*.sng) found in $mydir" >&2
  exit 1
fi

# Sanity check: is the binary usable at all?
if ! "$singular" --version >/dev/null 2>&1; then
  echo "libtests: ERROR: cannot execute Singular binary '$singular'" >&2
  exit 2
fi

# make the binary path absolute: scripts run inside their own rundir,
# so a relative path would stop resolving there
case "$singular" in
  */*) singular=`cd \`dirname "$singular"\` && pwd`/`basename "$singular"` ;;
esac

have_jq=0
if command -v jq >/dev/null 2>&1; then
  have_jq=1
fi

workdir=`mktemp -d libtests.XXXXXX` || exit 2
trap 'rm -rf "$workdir"' EXIT INT TERM

# NOTE: test.lib lives in Singular/LIB/ and is found by the test
# scripts via the standard library search path (LIB "test.lib"),
# so there is nothing to copy here.  Auxiliary libraries shipped
# next to the test scripts are copied per script below.

failed=0
run=0
junit_tmp="$workdir/junit-body.xml"
: > "$junit_tmp"
ctrftmp="$workdir/ctrf-tests.ndjson"
: > "$ctrftmp"

# append CTRF test-result objects (one per line, JSONL) for one script;
#   $1: script name, $2: rundir, $3: synthetic failure JSONL entries
# test.lib writes native CTRF files "<suite>.ctrf.json" (one report
# per TestSuite); their tests[] entries are collected verbatim.
emit_ctrf_script()
{
  [ $have_jq -eq 1 ] || return 0
  _sname="$1"; _rdir="$2"; _synth="$3"
  for _ctrf in "$_rdir"/*.ctrf.json; do
    [ -e "$_ctrf" ] || continue
    jq -c '.results.tests[]' "$_ctrf" >> "$ctrftmp" 2>/dev/null
  done
  if [ -n "$_synth" ]; then
    printf '%s\n' "$_synth" >> "$ctrftmp"
  fi
}

# synthetic CTRF entry for a script-level failure or skip;
#   $1: name, $2: message, $3: status ("failed" or "skipped")
synthetic_ctrf()
{
  [ $have_jq -eq 1 ] || return 0
  jq -cn --arg n "$1" --arg m "$2" --arg st "$3" \
    '{status: $st, name: $n, suite: $n, message: $m}'
}

# synthetic <testsuite> XML for a script-level skip;
#   $1: script name, $2: message
synthetic_junit_skip()
{
  [ $have_jq -eq 1 ] || return 0
  printf '<testsuite name="%s" tests="1" skipped="1"><testcase classname="%s" name="%s"><skipped message="suite skipped"><![CDATA[%s]]></skipped></testcase></testsuite>\n' \
    "$1" "$1" "$1" "$2"
}

# append <testsuite> XML for one script to the JUnit report.
#   $1: script name, $2: rundir, $3: xml entries for synthetic failures
junit_script_failures=""

emit_junit_script()
{
  [ $have_jq -eq 1 ] || return 0
  _sname="$1"; _rdir="$2"; _synth="$3"
  for _ctrf in "$_rdir"/*.ctrf.json; do
    [ -e "$_ctrf" ] || continue
    _fb=`basename "$_ctrf" .ctrf.json`
    jq -r --arg fb "$_fb" 'def esc: gsub("&";"\u0026amp;") | gsub("<";"\u0026lt;") | gsub(">";"\u0026gt;") | gsub("\\\"";"\u0026quot;") | gsub("\\x{27}";"\u0026apos;");
      .results.summary as $sum
      | (.results.tests[0].suite // $fb) as $suite
      | "<testsuite name=\"" + ($suite|esc) + "\""
      + " tests=\"" + (($sum.tests - ($sum.skipped // 0))|tostring) + "\""
      + " failures=\"" + ($sum.failed|tostring) + "\""
      + (if ($sum.tests == 0) then "/>\n"
         else ">\n"
         + ([.results.tests[]
             | select(.status != "skipped")
             | (if .status == "passed" then
                 "<testcase classname=\"" + (.suite|esc) + "\" name=\"" + (.name|esc) + "\"/>\n"
               else
                 "<testcase classname=\"" + (.suite|esc) + "\" name=\"" + (.name|esc) + "\">"
                 + "<failure message=\"assertion failed\"><![CDATA[" + ((.message // "") | gsub("\\]\\]>";"]]\u0026gt;")) + "]]></failure></testcase>\n"
               end)]
            | join(""))
         + "</testsuite>\n" end)' "$_ctrf" >> "$junit_tmp" 2>/dev/null
  done
  if [ -n "$_synth" ]; then
    printf '%s\n' "$_synth" >> "$junit_tmp"
  fi
}

# synthetic <testsuite> XML for a script that aborted before writing
# any (or all) reports;  $1: script name, $2: message
synthetic_junit()
{
  [ $have_jq -eq 1 ] || return 0
  printf '<testsuite name="%s" tests="1" failures="1"><testcase classname="%s" name="%s"><failure message="script error"><![CDATA[%s]]></failure></testcase></testsuite>\n' \
    "$1" "$1" "$1" "$2"
}

echo "=== Singular library test suites (test.lib) ==="
echo "    binary: $singular"
echo "    workdir: $workdir"
echo

for script in "$@"; do
  # a bare file name given on the command line refers to a script
  # in this script's own directory, not the caller's working dir
  case "$script" in
    */*) ;;
    *) script="$mydir/$script" ;;
  esac
  if [ ! -f "$script" ]; then
    echo "libtests: test script not found: $script" >&2
    exit 1
  fi
  name=`basename "$script" .sng`
  rundir="$workdir/$name"
  mkdir -p "$rundir"
  cp "$script" "$rundir/"
  # pick up auxiliary libraries shipped next to the test scripts
  for lib in "$mydir"/*.lib; do
    [ -e "$lib" ] || continue
    cp "$lib" "$rundir/"
  done

  echo "--- $name.sng"
  log="$rundir/$name.log"
  # run inside rundir: test.lib writes its CTRF reports into the
  # current working directory of the Singular process.
  # stdin is connected to /dev/null: on a syntax error (e.g. an
  # unterminated {...}) Singular otherwise waits for interactive
  # input and would hang until LIBTESTS_TIMEOUT kills it.
  if [ "$timeout_secs" -gt 0 ] && command -v timeout >/dev/null 2>&1; then
    ( cd "$rundir" && timeout "$timeout_secs" "$singular" -q --no-rc -t "$name.sng" > "$name.log" 2>&1 < /dev/null )
    rc=$?
  else
    ( cd "$rundir" && "$singular" -q --no-rc -t "$name.sng" > "$name.log" 2>&1 < /dev/null )
    rc=$?
  fi
  run=$((run + 1))

  script_failed=0
  junit_script_failures=""
  ctrf_script_failures=""

  # NOTE: Singular exits 0 even on errors, so rc is only meaningful
  # for crashes / timeouts (rc != 0 there is a real signal/abort).
  if [ $rc -ne 0 ]; then
    echo "    ERROR: Singular exited with status $rc (crash or timeout)"
    script_failed=1
    junit_script_failures="$junit_script_failures
`synthetic_junit "$name.sng" "Singular exited with status $rc (crash or timeout)"`"
    ctrf_script_failures="$ctrf_script_failures
`synthetic_ctrf "$name.sng" "Singular exited with status $rc (crash or timeout)" failed`"
  fi

  # (c) runtime errors: Singular prints error lines starting with " ? "
  # (d) internal crashes: Singular's signal handler (Singular/cntrlc.cc)
  #     prints "Singular : signal N", "Segment fault/Bus error occurred"
  #     and "trying to restart..." -- and may then continue, exit 0 and
  #     even have written a complete CTRF report.  Such a run is still
  #     a failure: the interpreter hit memory corruption.
  crashline=`grep -m1 -E '^Singular : signal|Segment fault/Bus error occurred|trying to restart' "$log" 2>/dev/null`
  if [ -n "$crashline" ]; then
    echo "    ERROR: Singular internal crash detected in output:"
    echo "      $crashline"
    script_failed=1
    junit_script_failures="$junit_script_failures
`synthetic_junit "$name.sng (crash)" "$crashline -- internal Singular crash (see log)"`"
    ctrf_script_failures="$ctrf_script_failures
`synthetic_ctrf "$name.sng (crash)" "$crashline -- internal Singular crash (see log)" failed`"
  fi

  # runtime errors: Singular prints error lines starting with " ? "
  errlines=`grep -E '^ +\? ' "$log" 2>/dev/null | head -10`
  if [ -n "$errlines" ]; then
    echo "    ERROR: runtime error(s) detected in output:"
    echo "$errlines" | sed 's/^/      /'
    script_failed=1
    junit_script_failures="$junit_script_failures
`synthetic_junit "$name.sng (runtime error)" "$(echo "$errlines" | tr -d '\0' | sed 's/]]>/]]\> /g')"`"
    ctrf_script_failures="$ctrf_script_failures
`synthetic_ctrf "$name.sng (runtime error)" "$(echo "$errlines" | tr -d '\0' | sed 's/]]>/]]\> /g')" failed`"
  fi

  # (a)+(b) CTRF reports: at least one, and all tests must have passed
  # NOTE: suite names may contain spaces, so we must iterate the glob
  # itself instead of a word-split "ls" listing
  found_ctrf=0
  for ctrf in "$rundir"/*.ctrf.json; do
    [ -e "$ctrf" ] || continue
    found_ctrf=1
    if [ $have_jq -eq 1 ]; then
      suite=`jq -r '.results.tests[0].suite // ""' "$ctrf" 2>/dev/null`
      if [ -z "$suite" ]; then
        suite=`basename "$ctrf" .ctrf.json`
      fi
      nfailed=`jq -r '.results.summary.failed' "$ctrf" 2>/dev/null`
      if [ "$nfailed" = "0" ]; then
        ncases=`jq -r '.results.summary.tests' "$ctrf" 2>/dev/null`
        echo "    OK suite: $suite ($ncases test cases)"
      else
        echo "    FAILED suite: $suite ($ctrf)"
        jq -r '.results.tests[] | select(.status == "failed") |
               "      test:  \(.name)\n      \(.message)\n"' "$ctrf" \
          2>/dev/null | head -40
        script_failed=1
      fi
    else
      # no jq: fall back to a textual check
      if grep -q '"status": "failed"' "$ctrf"; then
        echo "    FAILED suite report: $ctrf"
        script_failed=1
      else
        echo "    OK suite report: $ctrf"
      fi
    fi
  done
  if [ $found_ctrf -eq 0 ]; then
    # a script may deliberately skip itself (e.g. missing external
    # tools) by printing a line starting with "SKIP:" and not running
    # any TestSuite -- that is not a failure
    skipline=`grep -m1 '^SKIP:' "$log" 2>/dev/null`
    if [ -n "$skipline" ]; then
      echo "    SKIP: $name.sng"
      echo "      $skipline"
      junit_script_failures="$junit_script_failures
`synthetic_junit_skip "$name.sng" "$skipline"`"
      ctrf_script_failures="$ctrf_script_failures
`synthetic_ctrf "$name.sng" "$skipline" skipped`"
    else
      echo "    ERROR: no CTRF report written -- suite was probably aborted"
      script_failed=1
      junit_script_failures="$junit_script_failures
`synthetic_junit "$name.sng" "no CTRF report written -- suite was probably aborted by a runtime error"`"
      ctrf_script_failures="$ctrf_script_failures
`synthetic_ctrf "$name.sng" "no CTRF report written -- suite was probably aborted by a runtime error" failed`"
    fi
  fi

  emit_junit_script "$name" "$rundir" "$junit_script_failures"
  emit_ctrf_script "$name" "$rundir" "$ctrf_script_failures"

  if [ $script_failed -ne 0 ]; then
    failed=$((failed + 1))
    echo "    ==> $name.sng FAILED (full log: $log)"
  else
    echo "    ==> $name.sng PASSED"
  fi
  echo
done

# assemble the final JUnit XML report in the current directory
if [ $have_jq -eq 1 ]; then
  {
    echo '<?xml version="1.0" encoding="UTF-8"?>'
    echo '<testsuites name="Singular libtests">'
    cat "$junit_tmp"
    echo '</testsuites>'
  } > "$junitfile"
  echo "JUnit XML report written to $junitfile"

  # assemble the CTRF (standardized JSON) report:
  # https://ctrf.io  -- results.tool / summary / tests[]
  jq -s \
    '{results: {tool: {name: "Singular libtests"},
                summary: {tests: length,
                          passed: (map(select(.status == "passed")) | length),
                          failed: (map(select(.status == "failed")) | length),
                          skipped: (map(select(.status == "skipped")) | length)},
                tests: .}}' "$ctrftmp" > "$ctrffile" 2>/dev/null \
    && echo "CTRF JSON report written to $ctrffile" \
    || echo "NOTE: failed to write CTRF JSON report" >&2
else
  echo "NOTE: jq not found -- JUnit XML / CTRF JSON reports skipped" >&2
fi

echo "=== $run script(s) run, $failed failed ==="
if [ $failed -ne 0 ]; then
  exit 1
fi
exit 0
