# Library test suites (test.lib)

This directory hosts test suites for Singular libraries, written in the
Singular language with `test.lib` (TestSuite / TestCase / expectEqual /
expectComparedBy).

## Layout

- `test.lib`   -- the testing library (procedures `TestSuite`, `TestCase`,
  `expectEqual`, `expectComparedBy`, `equal`, ...) lives in
  `Singular/LIB/` and is shipped with Singular (registered in
  `Singular/singular-libs`, section SLIB1).  Test scripts just use
  `LIB "test.lib";` and get it via the standard library search path.
- `*.sng`      -- test scripts.  Each script `foo.sng` loads test.lib and
  runs one or more `TestSuite(...)` blocks.  Convention: tests for a
  library `bar.lib` go into `bar.sng` (one script per library under test).
  A script may skip itself deliberately (e.g. when it tests a library
  that needs external programs which are not installed): print a line
  starting with `SKIP:` and run no TestSuite.  The runner then reports
  the script (and each of its would-be suites) as *skipped*, not failed.
  See `lrcalc.lib.test.sng` for an example.
- `libtests.cmd` -- the runner (POSIX shell, no dependencies beyond the
  Singular binary; `jq` is used if available).
- `libtests-junit.xml` -- on each run, the runner writes a standard
  JUnit XML report (into the current working directory).  CI systems
  consume this natively: GitHub shows per-test annotations and
  summaries via `mikepenz/action-junit-report`, and the file works
  with GitLab, Jenkins, TeamCity, etc. alike.
- `libtests-ctrf.json` -- a CTRF (Concise Test Report Format,
  https://ctrf.io) report: a *standardized JSON* schema for test
  results (`results.summary`, `results.tests[]` with `status`,
  `suite`, `message`).  CTRF is the single suite report format:
  test.lib natively writes one CTRF file per TestSuite
  (`<suite name>.ctrf.json`, via `createCtrfFile`), and the runner
  derives everything from these files -- console reporting, the
  combined `libtests-ctrf.json` (merged from the per-suite files),
  and the JUnit XML report (CTRF has no information JUnit XML
  needs that is missing).  Supported by dedicated tooling
  (GitHub PR comments via `ctrf-io/ctrf-action`, the `ctrf` CLI,
  validators, reporters).  GitHub itself only consumes JUnit XML /
  SARIF natively, which is why the runner additionally converts
  the CTRF data to JUnit XML for GitHub's test annotations.

## Running

    ./libtests.cmd                       # run all *.sng
    ./libtests.cmd -s /path/to/Singular  # explicit binary (or env SINGULAR_BIN)
    ./libtests.cmd mylib.sng             # single script

The runner reports failures and exits non-zero if any suite fails, any
runtime error occurred, or any expected CTRF report is missing
(a runtime error inside a TestCase currently aborts the whole suite --
this is detected and reported).

## How failures are detected

Singular almost always exits with status 0, even on runtime errors, and
has no `exit(code)`.  Worse, on an internal crash its signal handler
prints `Singular : signal ...` / `Segment fault/Bus error occurred`,
restarts itself, may still write all CTRF reports and then exits 0.
Therefore the runner judges success from:

1. the `status` fields of the CTRF reports written by each TestSuite,
2. missing CTRF reports (suite aborted by a runtime error),
3. Singular error messages (lines starting with `? `) in the output log,
4. internal crash messages (`Singular : signal ...`, `Segment fault/
   Bus error occurred`, `trying to restart`) in the output log,
5. non-zero process status (hard crash / timeout, via `LIBTESTS_TIMEOUT`).

## CI

`.github/workflows/libtests.yml` builds Singular and runs this directory
on every push / pull request; the CTRF and JUnit reports plus the run
logs are uploaded as artifacts.  As libraries gain their own test
suites, they are picked up automatically simply by adding `*.sng`
files here.
