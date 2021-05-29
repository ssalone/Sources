/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 7 "grammar.y"


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "kernel/mod2.h"
#include "Singular/grammar.h"

#include "misc/mylimits.h"
#include "omalloc/omalloc.h"
#include "Singular/tok.h"
#include "misc/options.h"
#include "Singular/stype.h"
#include "Singular/fehelp.h"
#include "Singular/ipid.h"
#include "misc/intvec.h"
#include "kernel/oswrapper/feread.h"
#include "Singular/fevoices.h"
#include "polys/matpol.h"
#include "polys/monomials/ring.h"
#include "kernel/GBEngine/kstd1.h"
#include "Singular/subexpr.h"
#include "Singular/ipshell.h"
#include "Singular/ipconv.h"
#include "Singular/sdb.h"
#include "kernel/ideals.h"
#include "coeffs/numbers.h"
#include "kernel/polys.h"
#include "kernel/combinatorics/stairc.h"
#include "kernel/oswrapper/timer.h"
#include "Singular/cntrlc.h"
#include "polys/monomials/maps.h"
#include "kernel/GBEngine/syz.h"
#include "Singular/lists.h"
#include "Singular/libparse.h"
#include "coeffs/bigintmat.h"

#if 0
void debug_list(leftv v)
{
  idhdl r=basePackHdl;
  idhdl h;
  BOOLEAN found=FALSE;
  const char *nn=v->name;
  h=IDROOT->get(nn,myynest);
  if (h!=NULL)
  {
     Print("Curr::%s, (%s)\n",nn,Tok2Cmdname((int)IDTYP(h)));
     found=TRUE;
  }
  else         Print("`%s` not found in IDROOT\n",nn);
  while (r!=NULL)
  {
    if ((IDTYP(r)==PACKAGE_CMD)
    || (IDTYP(r)==RING_CMD))
    {
      h=IDPACKAGE(r)->idroot->get(nn,myynest);
      if (h!=NULL)
      {
        Print("%s::%s, (%s)\n",r->id,nn,Tok2Cmdname((int)IDTYP(h)));
        found=TRUE;
      }
      else         Print("%s::%s not found\n",r->id,nn);
    }
    if (r==basePackHdl) r=IDPACKAGE(r)->idroot;
    r=r->next;
   if (r==basePackHdl) break;
  }
  if (!found)
  {
    listall(TRUE);
  }
}
#endif

/* From the bison docu:

     By defining the macro `YYMAXDEPTH', you can control how deep the
parser stack can become before a stack overflow occurs.  Define the
macro with a value that is an integer.  This value is the maximum number
of tokens that can be shifted (and not reduced) before overflow.  It
must be a constant expression whose value is known at compile time.

   The stack space allowed is not necessarily allocated.  If you
specify a large value for `YYMAXDEPTH', the parser actually allocates a
small stack at first, and then makes it bigger by stages as needed.
This increasing allocation happens automatically and silently.
Therefore, you do not need to make `YYMAXDEPTH' painfully small merely
to save space for ordinary inputs that do not need much stack.

   The default value of `YYMAXDEPTH', if you do not define it, is 10000.
*/
#define YYMAXDEPTH MAX_INT_VAL

extern int   yylineno;
extern FILE* yyin;

const  char *  currid;
BOOLEAN    yyInRingConstruction=FALSE;
BOOLEAN    expected_parms;
int        cmdtok;
int        inerror = 0;

#define TESTSETINT(a,i)                                \
   if ((a).Typ() != INT_CMD)                           \
   {                                                   \
     WerrorS("no int expression");                     \
     YYERROR;                                          \
   }                                                   \
   (i) = (int)((long)(a).Data());(a).CleanUp()

#define MYYERROR(a) { WerrorS(a); YYERROR; }

void yyerror(const char * fmt)
{

  BOOLEAN old_errorreported=errorreported;
  errorreported = TRUE;
  if (currid!=NULL)
  {
    killid(currid,&IDROOT);
    currid = NULL;
  }
  if(inerror==0)
  {
    {
      if ((strlen(fmt)>1)
      && (strncmp(fmt,"parse",5)!=0)
      && (strncmp(fmt,"syntax",6)!=0))
        WerrorS(fmt);
      Werror( "error occurred in or before %s line %d: `%s`"
             ,VoiceName(), yylineno, my_yylinebuf);
    }
    if (cmdtok!=0)
    {
      const char *s=Tok2Cmdname(cmdtok);
      if (expected_parms)
      {
        Werror("expected %s-expression. type \'help %s;\'",s,s);
      }
      else
      {
        Werror("wrong type declaration. type \'help %s;\'",s);
      }
    }
    if (!old_errorreported && (lastreserved!=NULL))
    {
      Werror("last reserved name was `%s`",lastreserved);
    }
    inerror=1;
  }
  if ((currentVoice!=NULL)
  && (currentVoice->prev!=NULL)
  && (myynest>0)
#ifdef HAVE_SDB
  && ((sdb_flags &1)==0)
#endif
  )
  {
    Werror("leaving %s (%d)",VoiceName(), VoiceLine());
  }
}



/* Line 189 of yacc.c  */
#line 241 "grammar.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DOTDOT = 258,
     EQUAL_EQUAL = 259,
     GE = 260,
     LE = 261,
     MINUSMINUS = 262,
     NOT = 263,
     NOTEQUAL = 264,
     PLUSPLUS = 265,
     COLONCOLON = 266,
     ARROW = 267,
     GRING_CMD = 268,
     BIGINTMAT_CMD = 269,
     INTMAT_CMD = 270,
     PROC_CMD = 271,
     RING_CMD = 272,
     BEGIN_RING = 273,
     BUCKET_CMD = 274,
     IDEAL_CMD = 275,
     MAP_CMD = 276,
     MATRIX_CMD = 277,
     MODUL_CMD = 278,
     NUMBER_CMD = 279,
     POLY_CMD = 280,
     RESOLUTION_CMD = 281,
     SMATRIX_CMD = 282,
     VECTOR_CMD = 283,
     BETTI_CMD = 284,
     E_CMD = 285,
     FETCH_CMD = 286,
     FREEMODULE_CMD = 287,
     KEEPRING_CMD = 288,
     IMAP_CMD = 289,
     KOSZUL_CMD = 290,
     MAXID_CMD = 291,
     MONOM_CMD = 292,
     PAR_CMD = 293,
     PREIMAGE_CMD = 294,
     VAR_CMD = 295,
     VALTVARS = 296,
     VMAXDEG = 297,
     VMAXMULT = 298,
     VNOETHER = 299,
     VMINPOLY = 300,
     END_RING = 301,
     CMD_1 = 302,
     CMD_2 = 303,
     CMD_3 = 304,
     CMD_12 = 305,
     CMD_13 = 306,
     CMD_23 = 307,
     CMD_123 = 308,
     CMD_M = 309,
     ROOT_DECL = 310,
     ROOT_DECL_LIST = 311,
     RING_DECL = 312,
     RING_DECL_LIST = 313,
     EXAMPLE_CMD = 314,
     EXPORT_CMD = 315,
     HELP_CMD = 316,
     KILL_CMD = 317,
     LIB_CMD = 318,
     LISTVAR_CMD = 319,
     SETRING_CMD = 320,
     TYPE_CMD = 321,
     STRINGTOK = 322,
     BLOCKTOK = 323,
     INT_CONST = 324,
     UNKNOWN_IDENT = 325,
     MONOM = 326,
     PROC_DEF = 327,
     APPLY = 328,
     ASSUME_CMD = 329,
     BREAK_CMD = 330,
     CONTINUE_CMD = 331,
     ELSE_CMD = 332,
     EVAL = 333,
     QUOTE = 334,
     FOR_CMD = 335,
     IF_CMD = 336,
     SYS_BREAK = 337,
     WHILE_CMD = 338,
     RETURN = 339,
     PARAMETER = 340,
     SYSVAR = 341,
     UMINUS = 342
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 369 "grammar.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2826

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  104
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  178
/* YYNRULES -- Number of states.  */
#define YYNSTATES  409

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   342

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    97,     2,
     100,   101,     2,    89,    95,    90,   102,    91,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    98,    96,
      88,    87,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    92,     2,    93,    94,     2,   103,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    99
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    12,    15,    17,    19,
      21,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      43,    45,    47,    49,    51,    53,    55,    57,    59,    61,
      64,    66,    68,    72,    76,    80,    85,    89,    91,    93,
      95,   100,   105,   110,   114,   119,   124,   128,   133,   138,
     143,   148,   155,   162,   169,   176,   185,   194,   203,   212,
     216,   221,   230,   235,   244,   249,   253,   258,   264,   270,
     274,   278,   280,   282,   284,   291,   296,   303,   310,   317,
     324,   331,   338,   342,   348,   354,   355,   361,   364,   367,
     369,   372,   375,   379,   383,   387,   391,   395,   399,   403,
     407,   411,   415,   418,   421,   424,   427,   429,   433,   436,
     439,   442,   445,   454,   457,   461,   464,   466,   468,   474,
     476,   478,   483,   485,   489,   491,   495,   497,   499,   501,
     503,   505,   508,   512,   515,   519,   522,   525,   529,   534,
     539,   544,   549,   554,   559,   564,   569,   576,   583,   590,
     597,   604,   611,   618,   622,   624,   633,   636,   641,   649,
     652,   654,   656,   659,   662,   664,   670,   673,   679,   681,
     683,   687,   693,   697,   701,   706,   709,   712,   717
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     105,     0,    -1,    -1,   105,   106,    -1,   107,    -1,   109,
      96,    -1,   121,    96,    -1,   147,    -1,    82,    -1,    96,
      -1,     1,    96,    -1,   142,    -1,   143,    -1,   108,    -1,
     144,    -1,   145,    -1,   130,    -1,   131,    -1,   132,    -1,
      59,    68,    -1,   110,    -1,   133,    -1,   134,    -1,   135,
      -1,   146,    -1,   137,    -1,   138,    -1,   140,    -1,   141,
      -1,   119,   112,    -1,    71,    -1,   120,    -1,   111,    11,
     111,    -1,   113,   102,   111,    -1,   111,   100,   101,    -1,
     111,   100,   112,   101,    -1,    92,   112,    93,    -1,    69,
      -1,    86,    -1,   122,    -1,    16,   100,   113,   101,    -1,
      55,   100,   113,   101,    -1,    56,   100,   112,   101,    -1,
      56,   100,   101,    -1,    57,   100,   113,   101,    -1,    58,
     100,   112,   101,    -1,    58,   100,   101,    -1,    47,   100,
     113,   101,    -1,    50,   100,   113,   101,    -1,    51,   100,
     113,   101,    -1,    53,   100,   113,   101,    -1,    48,   100,
     113,    95,   113,   101,    -1,    50,   100,   113,    95,   113,
     101,    -1,    52,   100,   113,    95,   113,   101,    -1,    53,
     100,   113,    95,   113,   101,    -1,    49,   100,   113,    95,
     113,    95,   113,   101,    -1,    51,   100,   113,    95,   113,
      95,   113,   101,    -1,    52,   100,   113,    95,   113,    95,
     113,   101,    -1,    53,   100,   113,    95,   113,    95,   113,
     101,    -1,    54,   100,   101,    -1,    54,   100,   112,   101,
      -1,   129,   100,   113,    95,   113,    95,   113,   101,    -1,
     129,   100,   113,   101,    -1,    17,   100,   123,    95,   123,
      95,   127,   101,    -1,    17,   100,   113,   101,    -1,   120,
      12,    68,    -1,   100,   101,    12,    68,    -1,   100,   120,
     101,    12,    68,    -1,   100,   112,   101,    12,    68,    -1,
     100,   112,   101,    -1,   112,    95,   113,    -1,   113,    -1,
     118,    -1,   111,    -1,   113,    92,   113,    95,   113,    93,
      -1,   113,    92,   113,    93,    -1,    73,   100,   113,    95,
      47,   101,    -1,    73,   100,   113,    95,    50,   101,    -1,
      73,   100,   113,    95,    51,   101,    -1,    73,   100,   113,
      95,    53,   101,    -1,    73,   100,   113,    95,    54,   101,
      -1,    73,   100,   113,    95,   113,   101,    -1,   115,   113,
     117,    -1,   115,   113,    87,   113,   117,    -1,   116,   113,
      95,   113,   117,    -1,    -1,    78,   100,   114,   113,   101,
      -1,    79,   100,    -1,    74,   100,    -1,   101,    -1,   113,
      10,    -1,   113,     7,    -1,   113,    89,   113,    -1,   113,
      90,   113,    -1,   113,    91,   113,    -1,   113,    94,   113,
      -1,   113,    88,   113,    -1,   113,    97,   113,    -1,   113,
       9,   113,    -1,   113,     4,   113,    -1,   113,     3,   113,
      -1,   113,    98,   113,    -1,     8,   113,    -1,    90,   113,
      -1,   121,   128,    -1,   112,   128,    -1,    70,    -1,   103,
     113,   103,    -1,    55,   111,    -1,    56,   111,    -1,    57,
     111,    -1,    58,   111,    -1,   129,   111,    92,   113,    93,
      92,   113,    93,    -1,   129,   111,    -1,   121,    95,   111,
      -1,    16,   111,    -1,    67,    -1,   113,    -1,   100,   113,
      95,   112,   101,    -1,    70,    -1,   124,    -1,   124,   100,
     112,   101,    -1,   125,    -1,   125,    95,   126,    -1,   125,
      -1,   100,   126,   101,    -1,    87,    -1,    22,    -1,    27,
      -1,    15,    -1,    14,    -1,    88,   122,    -1,    61,    67,
      96,    -1,    61,    96,    -1,    59,    67,    96,    -1,    60,
     112,    -1,    62,   111,    -1,   134,    95,   111,    -1,    64,
     100,    55,   101,    -1,    64,   100,    56,   101,    -1,    64,
     100,    57,   101,    -1,    64,   100,    58,   101,    -1,    64,
     100,    17,   101,    -1,    64,   100,   129,   101,    -1,    64,
     100,    16,   101,    -1,    64,   100,   111,   101,    -1,    64,
     100,   111,    95,    55,   101,    -1,    64,   100,   111,    95,
      56,   101,    -1,    64,   100,   111,    95,    57,   101,    -1,
      64,   100,   111,    95,    58,   101,    -1,    64,   100,   111,
      95,    17,   101,    -1,    64,   100,   111,    95,   129,   101,
      -1,    64,   100,   111,    95,    16,   101,    -1,    64,   100,
     101,    -1,    17,    -1,   136,   111,   128,   123,    95,   123,
      95,   127,    -1,   136,   111,    -1,   136,   111,   128,   111,
      -1,   136,   111,   128,   111,    92,   112,    93,    -1,    86,
     122,    -1,    65,    -1,    33,    -1,   139,   113,    -1,    66,
     113,    -1,   112,    -1,    81,   100,   113,   101,    68,    -1,
      77,    68,    -1,    81,   100,   113,   101,    75,    -1,    75,
      -1,    76,    -1,    83,    67,    68,    -1,    80,    67,    67,
      67,    68,    -1,    16,   120,    68,    -1,    72,    67,    68,
      -1,    72,    67,    67,    68,    -1,    85,   121,    -1,    85,
     113,    -1,    84,   100,   112,   101,    -1,    84,   100,   101,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   318,   318,   320,   354,   355,   357,   359,   363,   368,
     370,   421,   422,   423,   424,   425,   426,   427,   428,   432,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   446,
     453,   458,   462,   466,   470,   474,   488,   516,   540,   546,
     552,   556,   560,   564,   568,   572,   576,   580,   584,   588,
     592,   596,   600,   604,   608,   612,   616,   620,   624,   628,
     632,   638,   642,   646,   650,   654,   659,   665,   670,   675,
     679,   690,   693,   694,   695,   699,   703,   707,   711,   715,
     719,   723,   727,   731,   748,   755,   754,   772,   780,   788,
     797,   801,   805,   809,   813,   817,   821,   825,   829,   833,
     837,   841,   845,   857,   864,   865,   884,   885,   897,   902,
     907,   911,   915,   952,   976,   997,  1005,  1009,  1010,  1024,
    1032,  1041,  1086,  1087,  1096,  1097,  1103,  1110,  1111,  1112,
    1113,  1121,  1126,  1131,  1138,  1146,  1158,  1175,  1195,  1199,
    1203,  1208,  1212,  1216,  1220,  1224,  1229,  1235,  1241,  1247,
    1253,  1259,  1265,  1277,  1284,  1288,  1325,  1332,  1337,  1350,
    1357,  1357,  1360,  1428,  1432,  1461,  1474,  1491,  1500,  1505,
    1513,  1525,  1544,  1554,  1573,  1596,  1602,  1614,  1620
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DOTDOT", "EQUAL_EQUAL", "GE", "LE",
  "MINUSMINUS", "NOT", "NOTEQUAL", "PLUSPLUS", "COLONCOLON", "ARROW",
  "GRING_CMD", "BIGINTMAT_CMD", "INTMAT_CMD", "PROC_CMD", "RING_CMD",
  "BEGIN_RING", "BUCKET_CMD", "IDEAL_CMD", "MAP_CMD", "MATRIX_CMD",
  "MODUL_CMD", "NUMBER_CMD", "POLY_CMD", "RESOLUTION_CMD", "SMATRIX_CMD",
  "VECTOR_CMD", "BETTI_CMD", "E_CMD", "FETCH_CMD", "FREEMODULE_CMD",
  "KEEPRING_CMD", "IMAP_CMD", "KOSZUL_CMD", "MAXID_CMD", "MONOM_CMD",
  "PAR_CMD", "PREIMAGE_CMD", "VAR_CMD", "VALTVARS", "VMAXDEG", "VMAXMULT",
  "VNOETHER", "VMINPOLY", "END_RING", "CMD_1", "CMD_2", "CMD_3", "CMD_12",
  "CMD_13", "CMD_23", "CMD_123", "CMD_M", "ROOT_DECL", "ROOT_DECL_LIST",
  "RING_DECL", "RING_DECL_LIST", "EXAMPLE_CMD", "EXPORT_CMD", "HELP_CMD",
  "KILL_CMD", "LIB_CMD", "LISTVAR_CMD", "SETRING_CMD", "TYPE_CMD",
  "STRINGTOK", "BLOCKTOK", "INT_CONST", "UNKNOWN_IDENT", "MONOM",
  "PROC_DEF", "APPLY", "ASSUME_CMD", "BREAK_CMD", "CONTINUE_CMD",
  "ELSE_CMD", "EVAL", "QUOTE", "FOR_CMD", "IF_CMD", "SYS_BREAK",
  "WHILE_CMD", "RETURN", "PARAMETER", "SYSVAR", "'='", "'<'", "'+'", "'-'",
  "'/'", "'['", "']'", "'^'", "','", "';'", "'&'", "':'", "UMINUS", "'('",
  "')'", "'.'", "'`'", "$accept", "lines", "pprompt", "flowctrl",
  "example_dummy", "command", "assign", "elemexpr", "exprlist", "expr",
  "$@1", "quote_start", "assume_start", "quote_end", "expr_arithmetic",
  "left_value", "extendedid", "declare_ip_variable", "stringexpr", "rlist",
  "ordername", "orderelem", "OrderingList", "ordering", "cmdeq", "mat_cmd",
  "filecmd", "helpcmd", "examplecmd", "exportcmd", "killcmd", "listcmd",
  "ringcmd1", "ringcmd", "scriptcmd", "setrings", "setringcmd", "typecmd",
  "ifcmd", "whilecmd", "forcmd", "proccmd", "parametercmd", "returncmd", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,    61,    60,    43,
      45,    47,    91,    93,    94,    44,    59,    38,    58,   342,
      40,    41,    46,    96
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   104,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   107,   107,   107,   107,   107,   107,   107,   107,   108,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   110,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     112,   112,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   113,   115,   116,   117,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   119,   120,   120,   121,   121,
     121,   121,   121,   121,   121,   121,   122,   123,   123,   124,
     125,   125,   126,   126,   127,   127,   128,   129,   129,   129,
     129,   130,   131,   131,   132,   133,   134,   134,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   136,   137,   137,   137,   137,   138,
     139,   139,   140,   141,   141,   142,   142,   142,   142,   142,
     143,   144,   145,   145,   145,   146,   146,   147,   147
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     2,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     3,     3,     3,     4,     3,     1,     1,     1,
       4,     4,     4,     3,     4,     4,     3,     4,     4,     4,
       4,     6,     6,     6,     6,     8,     8,     8,     8,     3,
       4,     8,     4,     8,     4,     3,     4,     5,     5,     3,
       3,     1,     1,     1,     6,     4,     6,     6,     6,     6,
       6,     6,     3,     5,     5,     0,     5,     2,     2,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     1,     3,     2,     2,
       2,     2,     8,     2,     3,     2,     1,     1,     5,     1,
       1,     4,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     2,     3,     2,     3,     2,     2,     3,     4,     4,
       4,     4,     4,     4,     4,     4,     6,     6,     6,     6,
       6,     6,     6,     3,     1,     8,     2,     4,     7,     2,
       1,     1,     2,     2,     1,     5,     2,     5,     1,     1,
       3,     5,     3,     3,     4,     2,     2,     4,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,   130,   129,     0,   154,   127,
     128,   161,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   160,
       0,   116,    37,   106,    30,     0,     0,     0,   168,   169,
       0,     0,     0,     0,     0,     8,     0,     0,     0,    38,
       0,     0,     0,     9,     0,     0,     3,     4,    13,     0,
      20,    73,   164,    71,     0,     0,    72,     0,    31,     0,
      39,     0,    16,    17,    18,    21,    22,    23,     0,    25,
      26,     0,    27,    28,    11,    12,    14,    15,    24,     7,
      10,     0,     0,     0,     0,     0,     0,    38,   102,     0,
       0,    73,     0,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    73,     0,    73,     0,    73,     0,
      73,     0,    19,   135,     0,   133,    73,     0,   163,     0,
       0,    88,   166,    85,    87,     0,     0,     0,     0,     0,
     176,   175,   159,   131,   103,     0,     0,     0,    31,     0,
       5,     0,     0,   126,     0,   105,     0,     0,    91,     0,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,     0,     6,   104,     0,    73,     0,
      73,   162,     0,     0,     0,     0,     0,     0,    71,   172,
       0,   117,     0,     0,     0,     0,     0,     0,     0,     0,
      59,     0,    71,    43,     0,    71,    46,     0,   134,   132,
       0,     0,     0,     0,     0,     0,   153,    73,     0,     0,
     173,     0,     0,     0,     0,   170,   178,     0,    36,     0,
      69,     0,   107,    32,    34,     0,    70,   100,    99,    98,
      96,    92,    93,    94,     0,    95,    97,   101,    33,     0,
      89,    82,     0,    65,    73,     0,     0,    73,     0,     0,
       0,    43,     0,     0,    46,     0,     0,    40,    71,    64,
       0,    47,     0,     0,     0,    48,     0,    49,     0,     0,
      50,    60,    41,    42,    44,    45,   144,   142,   138,   139,
     140,   141,     0,   145,   143,   174,     0,     0,     0,     0,
     177,    66,     0,     0,    35,    75,     0,     0,     0,     0,
      62,     0,    73,   117,     0,    42,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    86,   171,
     165,   167,    68,    67,     0,    83,    84,     0,     0,     0,
       0,     0,     0,    51,     0,    52,     0,     0,    53,     0,
      54,   152,   150,   146,   147,   148,   149,   151,    76,    77,
      78,    79,    80,    81,    74,     0,     0,     0,     0,   118,
     119,     0,   120,   124,     0,     0,     0,     0,     0,     0,
       0,   158,     0,   122,     0,     0,    63,    55,    56,    57,
      58,    61,   112,   155,     0,   125,     0,   123,   121
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    56,    57,    58,    59,    60,    61,   147,    63,
     222,    64,    65,   251,    66,    67,    68,    69,    70,   192,
     382,   383,   394,   384,   155,    99,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -367
static const yytype_int16 yypact[] =
{
    -367,   388,  -367,   -76,  2120,  -367,  -367,  2187,   -77,  -367,
    -367,  -367,   -73,   -61,   -59,   -57,   -30,   -28,     2,    22,
    2254,  2321,  2388,  2455,    16,  2120,   -62,  2120,    41,  -367,
    2120,  -367,  -367,  -367,  -367,    19,    48,    66,  -367,  -367,
      31,    75,    77,   101,    96,  -367,   131,   106,  2522,   142,
     142,  2120,  2120,  -367,  1517,  2120,  -367,  -367,  -367,   127,
    -367,     8,   -51,  1385,  2120,  2120,  -367,  2120,   204,   -79,
    -367,  2589,  -367,  -367,  -367,  -367,   147,  -367,  2120,  -367,
    -367,  2120,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,
    -367,   126,   -77,   138,   144,   146,   150,  -367,    15,   168,
    1517,   184,  1385,    -8,  2656,  2120,  2120,  2120,  2120,  2120,
    2120,  2120,  1584,  1517,   276,  1651,   466,  1517,  1313,  1718,
    1332,   186,  -367,   199,   200,  -367,    24,  1785,  1385,    72,
    2120,  -367,  -367,  -367,  -367,   233,  2120,   237,  1852,  2187,
    1385,   211,  -367,  -367,    15,   -84,   295,   -45,    14,   221,
    -367,  2120,  1919,  -367,  2120,  -367,  2120,  2120,  -367,  2120,
    -367,  2120,  2120,  2120,  2120,  2120,  2120,  2120,  2120,  2120,
     248,     3,   199,   240,  2120,  -367,  -367,  1517,   169,  2120,
     145,  1385,  2120,  2120,  1986,  2120,  2053,  2120,   575,  -367,
    1517,   590,   219,   686,   701,   716,   263,   404,   731,   419,
    -367,   -34,   746,   295,   -32,   761,   295,   -27,  -367,  -367,
     -47,   113,   118,   120,   133,   136,  -367,    26,   148,   249,
    -367,   857,  2120,   255,   872,  -367,  -367,   -24,  -367,   258,
     315,   316,  -367,  -367,  -367,   -16,  1385,  1414,  1400,  1400,
    1428,    68,    68,    15,   515,    21,    55,    68,  -367,  2120,
    -367,  -367,  2120,  -367,  1347,   530,  2120,   105,  2656,   575,
     746,  -367,   -14,   761,  -367,   -13,   530,  -367,   887,  -367,
    2656,  -367,  2120,  2120,  2120,  -367,  2120,  -367,  2120,  2120,
    -367,  -367,  -367,   315,  -367,   315,  -367,  -367,  -367,  -367,
    -367,  -367,  1521,  -367,  -367,  -367,  2723,   902,   261,   -54,
    -367,  -367,   264,   265,  -367,  -367,  2120,   917,   917,  2120,
    -367,   932,   143,  1385,   246,  -367,  -367,  2120,   252,  1028,
    1043,  1058,  1073,   545,   560,   243,   266,   267,   268,   269,
     272,   273,   153,   159,   162,   175,   185,  1088,  -367,  -367,
    -367,  -367,  -367,  -367,  1103,  -367,  -367,  1199,   251,  2120,
    2656,   102,   -67,  -367,  2120,  -367,  2120,  2120,  -367,  2120,
    -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,  -367,  2120,  2120,   -53,   271,  -367,
    -367,   286,   259,  -367,   277,  1214,  1229,  1244,  1259,  1274,
    1370,  -367,   -67,   282,   279,  2120,  -367,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,   286,  -367,   116,  -367,  -367
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -367,  -367,  -367,  -367,  -367,  -367,  -367,   151,    -1,    25,
    -367,  -367,  -367,   -19,  -367,  -367,    50,   314,   242,  -240,
    -367,  -366,   -21,    -7,   -68,     1,  -367,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,
    -367,  -367,  -367,  -367
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -158
static const yytype_int16 yytable[] =
{
      62,   176,    71,   380,   173,   124,   156,   157,   153,   228,
     158,   154,   159,   160,   340,   393,   174,   175,   314,   151,
      90,   341,   158,   104,   123,   160,   173,   105,   158,    98,
     318,   160,   102,   381,   125,   151,   153,   151,   393,   106,
     391,   107,   154,   108,   154,   102,   102,   102,   102,    71,
     154,   145,   102,   182,   286,   128,   230,   103,   156,   157,
     189,   154,   158,   154,   159,   160,   172,   281,   154,   283,
     109,   154,   110,   140,   285,   158,   144,   300,   160,   154,
     149,   154,   154,   121,   122,   304,   129,   315,   316,   170,
     171,   161,   162,   163,   164,   165,   102,   166,   252,   132,
     167,   168,   111,   102,   148,   169,   181,   165,   152,   166,
     378,   201,   258,   165,   204,   231,   151,   169,   207,  -136,
    -136,   292,   112,   169,   152,   188,   152,   293,   218,   191,
     193,   194,   195,   196,   197,   198,   199,   227,   202,   219,
     220,   127,   205,   161,   162,   163,   164,   165,   130,   166,
     148,   235,   102,   168,   151,   221,   151,   169,   101,   164,
     165,   224,   166,   148,   102,   148,   131,   148,   135,   148,
     169,   114,   116,   118,   120,   133,   102,   134,   126,   236,
     151,   237,   238,   262,   239,   265,   240,   241,   242,   243,
     244,   245,   246,   247,   102,   151,   136,   154,   137,   102,
    -137,  -137,   255,   379,   102,   152,   138,   259,   260,    31,
     263,   154,   266,   104,   287,   268,   173,   408,   183,   288,
     184,   289,   178,   150,   156,   157,   182,   148,   158,   180,
     159,   160,   153,   185,   290,   349,   186,   291,   183,  -157,
     148,  -156,   179,   152,   184,   152,   185,   297,   187,   294,
     186,   156,   157,   105,   368,   158,  -113,   159,   160,   108,
     369,   256,   109,   370,  -113,  -113,   156,   157,   187,   152,
     158,  -115,   159,   160,   307,   111,   371,   308,   217,  -115,
    -115,   311,   208,   313,   152,   112,   372,   151,   345,   346,
     101,   142,   143,   331,   154,   313,   209,   319,   320,   321,
     223,   322,   233,   323,   324,   225,   174,   229,   253,   161,
     162,   163,   164,   165,   270,   166,   351,   295,   167,   168,
     248,   337,   298,   169,   232,   254,   301,   302,   303,   339,
     257,   344,   342,   343,   347,   249,   161,   162,   163,   164,
     165,   350,   166,   376,   361,   167,   168,   352,   377,   250,
     169,   161,   162,   163,   164,   165,   380,   166,   274,   395,
     167,   168,   141,  -108,   275,   169,   392,   362,   363,   364,
     365,  -108,  -108,   366,   367,   313,   152,   404,   396,   385,
     405,   386,   387,   407,   388,   403,     0,     0,     2,     3,
       0,     0,     0,     0,   406,     0,     4,     0,     0,     0,
     389,   390,     5,     6,     7,     8,     0,   156,   157,   312,
       9,   158,     0,   159,   160,    10,     0,     0,     0,     0,
       0,    11,   156,   157,     0,     0,   158,     0,   159,   160,
       0,     0,     0,     0,     0,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,     0,    28,    29,    30,    31,     0,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,     0,    50,   151,    51,     0,
      52,     0,     0,     0,    53,     0,     0,     0,    54,     0,
       0,    55,   161,   162,   163,   164,   165,     0,   166,   276,
       0,   167,   168,     0,     0,   277,   169,   161,   162,   163,
     164,   165,     0,   166,   279,     0,   167,   168,   156,   157,
     280,   169,   158,     0,   159,   160,     0,     0,     0,     0,
       0,     0,     0,   156,   157,     0,     0,   158,     0,   159,
     160,     0,     0,     0,     0,     0,     0,     0,   156,   157,
       0,     0,   158,  -109,   159,   160,     0,     0,     0,     0,
       0,  -109,  -109,   156,   157,     0,   152,   158,     0,   159,
     160,     0,     0,     0,     0,     0,     0,     0,   156,   157,
       0,     0,   158,     0,   159,   160,     0,     0,     0,     0,
       0,     0,     0,   156,   157,     0,     0,   158,     0,   159,
     160,     0,     0,   161,   162,   163,   164,   165,   305,   166,
     306,     0,   167,   168,     0,     0,     0,   169,   161,   162,
     163,   164,   165,     0,   166,   309,     0,   167,   168,     0,
       0,   310,   169,   161,   162,   163,   164,   165,     0,   166,
     357,     0,   167,   168,     0,     0,   358,   169,   161,   162,
     163,   164,   165,     0,   166,   359,     0,   167,   168,     0,
       0,   360,   169,   161,   162,   163,   164,   165,     0,   166,
       0,     0,   167,   168,     0,     0,   267,   169,   161,   162,
     163,   164,   165,     0,   166,     0,     0,   167,   168,   156,
     157,   269,   169,   158,     0,   159,   160,     0,     0,     0,
       0,     0,     0,     0,   156,   157,     0,     0,   158,     0,
     159,   160,     0,     0,     0,     0,     0,     0,     0,   156,
     157,     0,     0,   158,     0,   159,   160,     0,     0,     0,
       0,     0,     0,     0,   156,   157,     0,     0,   158,     0,
     159,   160,     0,     0,     0,     0,     0,     0,     0,   156,
     157,     0,     0,   158,     0,   159,   160,     0,     0,     0,
       0,     0,     0,     0,   156,   157,     0,     0,   158,     0,
     159,   160,     0,     0,   161,   162,   163,   164,   165,     0,
     166,     0,     0,   167,   168,     0,     0,   271,   169,   161,
     162,   163,   164,   165,     0,   166,   272,     0,   167,   168,
       0,     0,     0,   169,   161,   162,   163,   164,   165,     0,
     166,   273,     0,   167,   168,     0,     0,     0,   169,   161,
     162,   163,   164,   165,     0,   166,   278,     0,   167,   168,
       0,     0,     0,   169,   161,   162,   163,   164,   165,     0,
     166,     0,     0,   167,   168,     0,     0,   282,   169,   161,
     162,   163,   164,   165,     0,   166,     0,     0,   167,   168,
     156,   157,   284,   169,   158,     0,   159,   160,     0,     0,
       0,     0,     0,     0,     0,   156,   157,     0,     0,   158,
       0,   159,   160,     0,     0,     0,     0,     0,     0,     0,
     156,   157,     0,     0,   158,     0,   159,   160,     0,     0,
       0,     0,     0,     0,     0,   156,   157,     0,     0,   158,
       0,   159,   160,     0,     0,     0,     0,     0,     0,     0,
     156,   157,     0,     0,   158,     0,   159,   160,     0,     0,
       0,     0,     0,     0,     0,   156,   157,     0,     0,   158,
       0,   159,   160,     0,     0,   161,   162,   163,   164,   165,
       0,   166,   296,     0,   167,   168,     0,     0,     0,   169,
     161,   162,   163,   164,   165,     0,   166,     0,     0,   167,
     168,     0,     0,   299,   169,   161,   162,   163,   164,   165,
       0,   166,   317,     0,   167,   168,     0,     0,     0,   169,
     161,   162,   163,   164,   165,     0,   166,     0,     0,   167,
     168,     0,     0,   338,   169,   161,   162,   163,   164,   165,
       0,   166,     0,     0,   167,   168,     0,     0,   250,   169,
     161,   162,   163,   164,   165,   348,   166,     0,     0,   167,
     168,   156,   157,     0,   169,   158,     0,   159,   160,     0,
       0,     0,     0,     0,     0,     0,   156,   157,     0,     0,
     158,     0,   159,   160,     0,     0,     0,     0,     0,     0,
       0,   156,   157,     0,     0,   158,     0,   159,   160,     0,
       0,     0,     0,     0,     0,     0,   156,   157,     0,     0,
     158,     0,   159,   160,     0,     0,     0,     0,     0,     0,
       0,   156,   157,     0,     0,   158,     0,   159,   160,     0,
       0,     0,     0,     0,     0,     0,   156,   157,     0,     0,
     158,     0,   159,   160,     0,     0,   161,   162,   163,   164,
     165,     0,   166,     0,     0,   167,   168,     0,     0,   353,
     169,   161,   162,   163,   164,   165,     0,   166,   354,     0,
     167,   168,     0,     0,     0,   169,   161,   162,   163,   164,
     165,     0,   166,     0,     0,   167,   168,     0,     0,   355,
     169,   161,   162,   163,   164,   165,     0,   166,   356,     0,
     167,   168,     0,     0,     0,   169,   161,   162,   163,   164,
     165,     0,   166,     0,     0,   167,   168,     0,     0,   373,
     169,   161,   162,   163,   164,   165,   374,   166,     0,     0,
     167,   168,   156,   157,     0,   169,   158,     0,   159,   160,
       0,     0,     0,     0,     0,     0,     0,   156,   157,     0,
       0,   158,     0,   159,   160,     0,     0,     0,     0,     0,
       0,     0,   156,   157,     0,     0,   158,     0,   159,   160,
       0,     0,     0,     0,     0,     0,     0,   156,   157,     0,
       0,   158,     0,   159,   160,     0,     0,     0,     0,     0,
       0,     0,   156,   157,     0,     0,   158,     0,   159,   160,
       0,     0,     0,     0,     0,     0,     0,   156,   157,     0,
       0,   158,     0,   159,   160,     0,     0,   161,   162,   163,
     164,   165,     0,   166,   375,     0,   167,   168,     0,     0,
       0,   169,   161,   162,   163,   164,   165,     0,   166,     0,
       0,   167,   168,     0,     0,   397,   169,   161,   162,   163,
     164,   165,     0,   166,   151,     0,   167,   168,     0,     0,
     398,   169,   161,   162,   163,   164,   165,     0,   166,     0,
       0,   167,   168,   151,     0,   399,   169,   161,   162,   163,
     164,   165,     0,   166,     0,     0,   167,   168,   151,     0,
     400,   169,   161,   162,   163,   164,   165,     0,   166,     0,
       0,   167,   168,   156,   157,   401,   169,   158,     0,   159,
     160,     0,     0,     0,     0,     0,     0,     0,   156,   157,
       0,     0,   158,     0,   159,   160,     0,     0,     0,     0,
    -110,     0,     0,   156,     0,     0,     0,   158,  -110,  -110,
     160,     0,     0,   152,     0,     0,     0,  -158,     0,  -111,
       0,   158,     0,     0,   160,     0,     0,  -111,  -111,     0,
       0,   156,   152,     0,  -114,   158,     0,     0,   160,     0,
       0,     0,  -114,  -114,     0,     0,     0,   152,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   161,   162,
     163,   164,   165,   402,   166,     0,     0,   167,   168,     0,
       0,     0,   169,   161,   162,   163,   164,   165,     0,   166,
       0,     0,   167,   168,     0,     0,     0,   169,   161,   162,
     163,   164,   165,     0,   166,     0,     0,     0,   168,     0,
       0,     0,   169,   162,   163,   164,   165,     0,   166,     0,
       0,     0,   168,     0,     0,     0,   169,   162,   163,   164,
     165,     0,   166,     0,     0,     4,   168,     0,     0,     0,
     169,     5,     6,    91,    92,     5,     6,   325,   326,     9,
       0,     0,     0,     9,    10,     0,     0,     0,    10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,    13,    14,    15,    16,    17,
      18,    19,    93,    94,    95,    96,   327,   328,   329,   330,
       0,     0,     0,     0,    31,     0,    32,    33,    34,     0,
      36,    37,     4,     0,     0,    41,    42,     0,     5,     6,
      91,    92,     0,    97,     0,     0,     9,    51,     0,    52,
       0,    10,     0,     0,     0,     0,     0,    54,   146,     0,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,    13,    14,    15,    16,    17,    18,    19,    93,
      94,    95,    96,     0,     0,     0,     0,     0,     0,     0,
       0,    31,     0,    32,    33,    34,     0,    36,    37,     4,
       0,     0,    41,    42,     0,     5,     6,    91,    92,     0,
      97,     0,     0,     9,    51,     0,    52,     0,    10,     0,
       0,     0,     0,     0,    54,   200,     0,    55,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,    13,
      14,    15,    16,    17,    18,    19,    93,    94,    95,    96,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
      32,    33,    34,     0,    36,    37,     4,     0,     0,    41,
      42,     0,     5,     6,    91,    92,     0,    97,     0,     0,
       9,    51,     0,    52,     0,    10,     0,     0,     0,     0,
       0,    54,   203,     0,    55,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,    13,    14,    15,    16,
      17,    18,    19,    93,    94,    95,    96,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,    32,    33,    34,
       0,    36,    37,     4,     0,     0,    41,    42,     0,     5,
       6,   210,   211,     0,    97,     0,     0,     9,    51,     0,
      52,     0,    10,     0,     0,     0,     0,     0,    54,   206,
       0,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    12,    13,    14,    15,    16,    17,    18,    19,
     212,   213,   214,   215,     0,     0,     0,     0,     0,     0,
       0,     0,    31,     0,    32,    33,    34,     0,    36,    37,
       4,     0,     0,    41,    42,     0,     5,     6,    91,    92,
       0,    97,     0,     0,     9,    51,     0,    52,     0,    10,
       0,     0,     0,     0,     0,    54,   216,     0,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      13,    14,    15,    16,    17,    18,    19,    93,    94,    95,
      96,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,    32,    33,    34,     0,    36,    37,     4,     0,     0,
      41,    42,     0,     5,     6,    91,    92,     0,    97,     0,
       0,     9,    51,     0,    52,     0,    10,     0,     0,     0,
       0,     0,    54,   226,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,    13,    14,    15,
      16,    17,    18,    19,    93,    94,    95,    96,     0,     0,
       0,     0,     0,     0,     0,     0,    31,     0,    32,    33,
      34,     0,    36,    37,     4,     0,     0,    41,    42,     0,
       5,     6,    91,    92,     0,    97,     0,     0,     9,    51,
       0,    52,     0,    10,     0,     0,     0,     0,     0,    54,
     234,     0,    55,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,    13,    14,    15,    16,    17,    18,
      19,    93,    94,    95,    96,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,    32,    33,    34,     0,    36,
      37,     4,     0,     0,    41,    42,     0,     5,     6,    91,
      92,     0,    97,     0,     0,     9,    51,     0,    52,     0,
      10,     0,     0,     0,     0,     0,    54,   261,     0,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,    13,    14,    15,    16,    17,    18,    19,    93,    94,
      95,    96,     0,     0,     0,     0,     0,     0,     0,     0,
      31,     0,    32,    33,    34,     0,    36,    37,     4,     0,
       0,    41,    42,     0,     5,     6,    91,    92,     0,    97,
       0,     0,     9,    51,     0,    52,     0,    10,     0,     0,
       0,     0,     0,    54,   264,     0,    55,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    12,    13,    14,
      15,    16,    17,    18,    19,    93,    94,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,    31,     0,    32,
      33,    34,     0,    36,    37,     4,     0,     0,    41,    42,
       0,     5,     6,    91,    92,     0,    97,     0,     0,     9,
      51,     0,    52,     0,    10,     0,     0,     0,     0,     0,
      54,     0,     0,    55,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,    13,    14,    15,    16,    17,
      18,    19,    93,    94,    95,    96,     0,     0,     0,     0,
       0,     0,     0,     0,    31,     0,    32,    33,    34,     0,
      36,    37,     4,     0,     0,    41,    42,     0,     5,     6,
      91,    92,     0,    97,     0,     0,     9,    51,     0,    52,
       0,    10,     0,     0,     0,     0,     0,   100,     0,     0,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,    13,    14,    15,    16,    17,    18,    19,    93,
      94,    95,    96,     0,     0,     0,     0,     0,     0,     0,
       0,    31,     0,    32,    33,    34,     0,    36,    37,     4,
       0,     0,    41,    42,     0,     5,     6,    91,    92,     0,
      97,     0,     0,     9,    51,     0,    52,     0,    10,     0,
       0,     0,     0,     0,   113,     0,     0,    55,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,    13,
      14,    15,    16,    17,    18,    19,    93,    94,    95,    96,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
      32,    33,    34,     0,    36,    37,     4,     0,     0,    41,
      42,     0,     5,     6,    91,    92,     0,    97,     0,     0,
       9,    51,     0,    52,     0,    10,     0,     0,     0,     0,
       0,   115,     0,     0,    55,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,    13,    14,    15,    16,
      17,    18,    19,    93,    94,    95,    96,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,    32,    33,    34,
       0,    36,    37,     4,     0,     0,    41,    42,     0,     5,
       6,    91,    92,     0,    97,     0,     0,     9,    51,     0,
      52,     0,    10,     0,     0,     0,     0,     0,   117,     0,
       0,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    12,    13,    14,    15,    16,    17,    18,    19,
      93,    94,    95,    96,     0,     0,     0,     0,     0,     0,
       0,     0,    31,     0,    32,    33,    34,     0,    36,    37,
       4,     0,     0,    41,    42,     0,     5,     6,   139,    92,
       0,    97,     0,     0,     9,    51,     0,    52,     0,    10,
       0,     0,     0,     0,     0,   119,     0,     0,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,    32,    33,    34,     0,    36,    37,     4,     0,     0,
      41,    42,     0,     5,     6,    91,    92,     0,    97,     0,
       0,     9,    51,     0,    52,     0,    10,     0,     0,     0,
       0,     0,    54,     0,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,    13,    14,    15,
      16,    17,    18,    19,    93,    94,    95,    96,     0,     0,
       0,     0,     0,     0,     0,     0,    31,     0,    32,    33,
      34,     0,    36,    37,     4,     0,     0,    41,    42,     0,
       5,     6,    91,    92,     0,    97,     0,     0,     9,    51,
       0,    52,     0,    10,     0,     0,     0,     0,     0,   177,
       0,     0,    55,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,    13,    14,    15,    16,    17,    18,
      19,    93,    94,    95,    96,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,    32,    33,    34,     0,    36,
      37,     4,     0,     0,    41,    42,     0,     5,     6,    91,
      92,     0,    97,     0,     0,     9,    51,     0,    52,     0,
      10,     0,     0,     0,     0,     0,   190,     0,     0,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     332,    13,    14,   333,   334,    17,   335,   336,    93,    94,
      95,    96,     0,     0,     0,     0,     0,     0,     0,     0,
      31,     0,    32,    33,    34,     0,    36,    37,     0,     0,
       0,    41,    42,     0,     0,     0,     0,     0,     0,    97,
       0,     0,     0,    51,     0,    52,     0,     0,     0,     0,
       0,     0,     0,    54,     0,     0,    55
};

static const yytype_int16 yycheck[] =
{
       1,    69,     1,    70,    12,    67,     3,     4,    87,    93,
       7,    95,     9,    10,    68,   381,    95,    96,   258,    11,
      96,    75,     7,   100,    25,    10,    12,   100,     7,     4,
     270,    10,     7,   100,    96,    11,    87,    11,   404,   100,
      93,   100,    95,   100,    95,    20,    21,    22,    23,    48,
      95,    52,    27,   100,   101,    30,   101,     7,     3,     4,
      68,    95,     7,    95,     9,    10,    67,   101,    95,   101,
     100,    95,   100,    48,   101,     7,    51,   101,    10,    95,
      55,    95,    95,    67,    68,   101,    67,   101,   101,    64,
      65,    88,    89,    90,    91,    92,    71,    94,    95,    68,
      97,    98,   100,    78,    54,   102,    81,    92,   100,    94,
     350,   112,   180,    92,   115,   101,    11,   102,   119,    95,
      96,    95,   100,   102,   100,   100,   100,   101,   127,   104,
     105,   106,   107,   108,   109,   110,   111,   138,   113,    67,
      68,   100,   117,    88,    89,    90,    91,    92,   100,    94,
     100,   152,   127,    98,    11,   130,    11,   102,     7,    91,
      92,   136,    94,   113,   139,   115,   100,   117,    67,   119,
     102,    20,    21,    22,    23,   100,   151,   100,    27,   154,
      11,   156,   157,   184,   159,   186,   161,   162,   163,   164,
     165,   166,   167,   168,   169,    11,   100,    95,    67,   174,
      95,    96,   177,   101,   179,   100,   100,   182,   183,    67,
     185,    95,   187,   100,   101,   190,    12,   101,   100,   101,
     100,   101,    71,    96,     3,     4,   100,   177,     7,    78,
       9,    10,    87,   100,   101,    92,   100,   101,   100,    96,
     190,    96,    95,   100,   100,   100,   100,   222,   100,   101,
     100,     3,     4,   100,   101,     7,    87,     9,    10,   100,
     101,    92,   100,   101,    95,    96,     3,     4,   100,   100,
       7,    87,     9,    10,   249,   100,   101,   252,   127,    95,
      96,   256,    96,   258,   100,   100,   101,    11,   307,   308,
     139,    49,    50,   292,    95,   270,    96,   272,   273,   274,
      67,   276,   151,   278,   279,    68,    95,    12,    68,    88,
      89,    90,    91,    92,    95,    94,   317,    68,    97,    98,
     169,   296,    67,   102,   103,   174,    68,    12,    12,    68,
     179,   306,    68,    68,   309,    87,    88,    89,    90,    91,
      92,    95,    94,    92,   101,    97,    98,    95,   349,   101,
     102,    88,    89,    90,    91,    92,    70,    94,    95,   100,
      97,    98,    48,    87,   101,   102,    95,   101,   101,   101,
     101,    95,    96,   101,   101,   350,   100,    95,   101,   354,
     101,   356,   357,   404,   359,   392,    -1,    -1,     0,     1,
      -1,    -1,    -1,    -1,   395,    -1,     8,    -1,    -1,    -1,
     375,   376,    14,    15,    16,    17,    -1,     3,     4,   258,
      22,     7,    -1,     9,    10,    27,    -1,    -1,    -1,    -1,
      -1,    33,     3,     4,    -1,    -1,     7,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    64,    65,    66,    67,    -1,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    -1,    88,    11,    90,    -1,
      92,    -1,    -1,    -1,    96,    -1,    -1,    -1,   100,    -1,
      -1,   103,    88,    89,    90,    91,    92,    -1,    94,    95,
      -1,    97,    98,    -1,    -1,   101,   102,    88,    89,    90,
      91,    92,    -1,    94,    95,    -1,    97,    98,     3,     4,
     101,   102,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,    -1,    -1,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
      -1,    -1,     7,    87,     9,    10,    -1,    -1,    -1,    -1,
      -1,    95,    96,     3,     4,    -1,   100,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
      -1,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,    -1,    -1,     7,    -1,     9,
      10,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    -1,    97,    98,    -1,    -1,    -1,   102,    88,    89,
      90,    91,    92,    -1,    94,    95,    -1,    97,    98,    -1,
      -1,   101,   102,    88,    89,    90,    91,    92,    -1,    94,
      95,    -1,    97,    98,    -1,    -1,   101,   102,    88,    89,
      90,    91,    92,    -1,    94,    95,    -1,    97,    98,    -1,
      -1,   101,   102,    88,    89,    90,    91,    92,    -1,    94,
      -1,    -1,    97,    98,    -1,    -1,   101,   102,    88,    89,
      90,    91,    92,    -1,    94,    -1,    -1,    97,    98,     3,
       4,   101,   102,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,    -1,    -1,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,    -1,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,    -1,    -1,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,    -1,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,    -1,    -1,     7,    -1,
       9,    10,    -1,    -1,    88,    89,    90,    91,    92,    -1,
      94,    -1,    -1,    97,    98,    -1,    -1,   101,   102,    88,
      89,    90,    91,    92,    -1,    94,    95,    -1,    97,    98,
      -1,    -1,    -1,   102,    88,    89,    90,    91,    92,    -1,
      94,    95,    -1,    97,    98,    -1,    -1,    -1,   102,    88,
      89,    90,    91,    92,    -1,    94,    95,    -1,    97,    98,
      -1,    -1,    -1,   102,    88,    89,    90,    91,    92,    -1,
      94,    -1,    -1,    97,    98,    -1,    -1,   101,   102,    88,
      89,    90,    91,    92,    -1,    94,    -1,    -1,    97,    98,
       3,     4,   101,   102,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,    -1,    -1,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,    -1,    -1,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,     7,
      -1,     9,    10,    -1,    -1,    88,    89,    90,    91,    92,
      -1,    94,    95,    -1,    97,    98,    -1,    -1,    -1,   102,
      88,    89,    90,    91,    92,    -1,    94,    -1,    -1,    97,
      98,    -1,    -1,   101,   102,    88,    89,    90,    91,    92,
      -1,    94,    95,    -1,    97,    98,    -1,    -1,    -1,   102,
      88,    89,    90,    91,    92,    -1,    94,    -1,    -1,    97,
      98,    -1,    -1,   101,   102,    88,    89,    90,    91,    92,
      -1,    94,    -1,    -1,    97,    98,    -1,    -1,   101,   102,
      88,    89,    90,    91,    92,    93,    94,    -1,    -1,    97,
      98,     3,     4,    -1,   102,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,
       7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,    -1,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,
       7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,    -1,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,
       7,    -1,     9,    10,    -1,    -1,    88,    89,    90,    91,
      92,    -1,    94,    -1,    -1,    97,    98,    -1,    -1,   101,
     102,    88,    89,    90,    91,    92,    -1,    94,    95,    -1,
      97,    98,    -1,    -1,    -1,   102,    88,    89,    90,    91,
      92,    -1,    94,    -1,    -1,    97,    98,    -1,    -1,   101,
     102,    88,    89,    90,    91,    92,    -1,    94,    95,    -1,
      97,    98,    -1,    -1,    -1,   102,    88,    89,    90,    91,
      92,    -1,    94,    -1,    -1,    97,    98,    -1,    -1,   101,
     102,    88,    89,    90,    91,    92,    93,    94,    -1,    -1,
      97,    98,     3,     4,    -1,   102,     7,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,
      -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,    -1,    -1,     7,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,
      -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,    -1,    -1,     7,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,
      -1,     7,    -1,     9,    10,    -1,    -1,    88,    89,    90,
      91,    92,    -1,    94,    95,    -1,    97,    98,    -1,    -1,
      -1,   102,    88,    89,    90,    91,    92,    -1,    94,    -1,
      -1,    97,    98,    -1,    -1,   101,   102,    88,    89,    90,
      91,    92,    -1,    94,    11,    -1,    97,    98,    -1,    -1,
     101,   102,    88,    89,    90,    91,    92,    -1,    94,    -1,
      -1,    97,    98,    11,    -1,   101,   102,    88,    89,    90,
      91,    92,    -1,    94,    -1,    -1,    97,    98,    11,    -1,
     101,   102,    88,    89,    90,    91,    92,    -1,    94,    -1,
      -1,    97,    98,     3,     4,   101,   102,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
      -1,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      87,    -1,    -1,     3,    -1,    -1,    -1,     7,    95,    96,
      10,    -1,    -1,   100,    -1,    -1,    -1,     3,    -1,    87,
      -1,     7,    -1,    -1,    10,    -1,    -1,    95,    96,    -1,
      -1,     3,   100,    -1,    87,     7,    -1,    -1,    10,    -1,
      -1,    -1,    95,    96,    -1,    -1,    -1,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    -1,    -1,    97,    98,    -1,
      -1,    -1,   102,    88,    89,    90,    91,    92,    -1,    94,
      -1,    -1,    97,    98,    -1,    -1,    -1,   102,    88,    89,
      90,    91,    92,    -1,    94,    -1,    -1,    -1,    98,    -1,
      -1,    -1,   102,    89,    90,    91,    92,    -1,    94,    -1,
      -1,    -1,    98,    -1,    -1,    -1,   102,    89,    90,    91,
      92,    -1,    94,    -1,    -1,     8,    98,    -1,    -1,    -1,
     102,    14,    15,    16,    17,    14,    15,    16,    17,    22,
      -1,    -1,    -1,    22,    27,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,
      73,    74,     8,    -1,    -1,    78,    79,    -1,    14,    15,
      16,    17,    -1,    86,    -1,    -1,    22,    90,    -1,    92,
      -1,    27,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    69,    70,    71,    -1,    73,    74,     8,
      -1,    -1,    78,    79,    -1,    14,    15,    16,    17,    -1,
      86,    -1,    -1,    22,    90,    -1,    92,    -1,    27,    -1,
      -1,    -1,    -1,    -1,   100,   101,    -1,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      69,    70,    71,    -1,    73,    74,     8,    -1,    -1,    78,
      79,    -1,    14,    15,    16,    17,    -1,    86,    -1,    -1,
      22,    90,    -1,    92,    -1,    27,    -1,    -1,    -1,    -1,
      -1,   100,   101,    -1,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    70,    71,
      -1,    73,    74,     8,    -1,    -1,    78,    79,    -1,    14,
      15,    16,    17,    -1,    86,    -1,    -1,    22,    90,    -1,
      92,    -1,    27,    -1,    -1,    -1,    -1,    -1,   100,   101,
      -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    69,    70,    71,    -1,    73,    74,
       8,    -1,    -1,    78,    79,    -1,    14,    15,    16,    17,
      -1,    86,    -1,    -1,    22,    90,    -1,    92,    -1,    27,
      -1,    -1,    -1,    -1,    -1,   100,   101,    -1,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    70,    71,    -1,    73,    74,     8,    -1,    -1,
      78,    79,    -1,    14,    15,    16,    17,    -1,    86,    -1,
      -1,    22,    90,    -1,    92,    -1,    27,    -1,    -1,    -1,
      -1,    -1,   100,   101,    -1,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    70,
      71,    -1,    73,    74,     8,    -1,    -1,    78,    79,    -1,
      14,    15,    16,    17,    -1,    86,    -1,    -1,    22,    90,
      -1,    92,    -1,    27,    -1,    -1,    -1,    -1,    -1,   100,
     101,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,    73,
      74,     8,    -1,    -1,    78,    79,    -1,    14,    15,    16,
      17,    -1,    86,    -1,    -1,    22,    90,    -1,    92,    -1,
      27,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    69,    70,    71,    -1,    73,    74,     8,    -1,
      -1,    78,    79,    -1,    14,    15,    16,    17,    -1,    86,
      -1,    -1,    22,    90,    -1,    92,    -1,    27,    -1,    -1,
      -1,    -1,    -1,   100,   101,    -1,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
      70,    71,    -1,    73,    74,     8,    -1,    -1,    78,    79,
      -1,    14,    15,    16,    17,    -1,    86,    -1,    -1,    22,
      90,    -1,    92,    -1,    27,    -1,    -1,    -1,    -1,    -1,
     100,    -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,
      73,    74,     8,    -1,    -1,    78,    79,    -1,    14,    15,
      16,    17,    -1,    86,    -1,    -1,    22,    90,    -1,    92,
      -1,    27,    -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    69,    70,    71,    -1,    73,    74,     8,
      -1,    -1,    78,    79,    -1,    14,    15,    16,    17,    -1,
      86,    -1,    -1,    22,    90,    -1,    92,    -1,    27,    -1,
      -1,    -1,    -1,    -1,   100,    -1,    -1,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      69,    70,    71,    -1,    73,    74,     8,    -1,    -1,    78,
      79,    -1,    14,    15,    16,    17,    -1,    86,    -1,    -1,
      22,    90,    -1,    92,    -1,    27,    -1,    -1,    -1,    -1,
      -1,   100,    -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    70,    71,
      -1,    73,    74,     8,    -1,    -1,    78,    79,    -1,    14,
      15,    16,    17,    -1,    86,    -1,    -1,    22,    90,    -1,
      92,    -1,    27,    -1,    -1,    -1,    -1,    -1,   100,    -1,
      -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    69,    70,    71,    -1,    73,    74,
       8,    -1,    -1,    78,    79,    -1,    14,    15,    16,    17,
      -1,    86,    -1,    -1,    22,    90,    -1,    92,    -1,    27,
      -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    69,    70,    71,    -1,    73,    74,     8,    -1,    -1,
      78,    79,    -1,    14,    15,    16,    17,    -1,    86,    -1,
      -1,    22,    90,    -1,    92,    -1,    27,    -1,    -1,    -1,
      -1,    -1,   100,    -1,    -1,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    70,
      71,    -1,    73,    74,     8,    -1,    -1,    78,    79,    -1,
      14,    15,    16,    17,    -1,    86,    -1,    -1,    22,    90,
      -1,    92,    -1,    27,    -1,    -1,    -1,    -1,    -1,   100,
      -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    69,    70,    71,    -1,    73,
      74,     8,    -1,    -1,    78,    79,    -1,    14,    15,    16,
      17,    -1,    86,    -1,    -1,    22,    90,    -1,    92,    -1,
      27,    -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    69,    70,    71,    -1,    73,    74,    -1,    -1,
      -1,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    -1,    90,    -1,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,    -1,    -1,   103
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   105,     0,     1,     8,    14,    15,    16,    17,    22,
      27,    33,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    64,    65,
      66,    67,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      88,    90,    92,    96,   100,   103,   106,   107,   108,   109,
     110,   111,   112,   113,   115,   116,   118,   119,   120,   121,
     122,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
      96,    16,    17,    55,    56,    57,    58,    86,   113,   129,
     100,   111,   113,   120,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   111,   100,   111,   100,   111,   100,
     111,    67,    68,   112,    67,    96,   111,   100,   113,    67,
     100,   100,    68,   100,   100,    67,   100,    67,   100,    16,
     113,   121,   122,   122,   113,   112,   101,   112,   120,   113,
      96,    11,   100,    87,    95,   128,     3,     4,     7,     9,
      10,    88,    89,    90,    91,    92,    94,    97,    98,   102,
     113,   113,   112,    12,    95,    96,   128,   100,   111,    95,
     111,   113,   100,   100,   100,   100,   100,   100,   113,    68,
     100,   113,   123,   113,   113,   113,   113,   113,   113,   113,
     101,   112,   113,   101,   112,   113,   101,   112,    96,    96,
      16,    17,    55,    56,    57,    58,   101,   111,   129,    67,
      68,   113,   114,    67,   113,    68,   101,   112,    93,    12,
     101,   101,   103,   111,   101,   112,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   111,    87,
     101,   117,    95,    68,   111,   113,    92,   111,   128,   113,
     113,   101,   112,   113,   101,   112,   113,   101,   113,   101,
      95,   101,    95,    95,    95,   101,    95,   101,    95,    95,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,    95,   101,   101,    68,    95,   113,    67,   101,
     101,    68,    12,    12,   101,    93,    95,   113,   113,    95,
     101,   113,   111,   113,   123,   101,   101,    95,   123,   113,
     113,   113,   113,   113,   113,    16,    17,    55,    56,    57,
      58,   129,    47,    50,    51,    53,    54,   113,   101,    68,
      68,    75,    68,    68,   113,   117,   117,   113,    93,    92,
      95,   112,    95,   101,    95,   101,    95,    95,   101,    95,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,    93,    95,    92,   112,   123,   101,
      70,   100,   124,   125,   127,   113,   113,   113,   113,   113,
     113,    93,    95,   125,   126,   100,   101,   101,   101,   101,
     101,   101,    93,   127,    95,   101,   112,   126,   101
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1464 of yacc.c  */
#line 321 "grammar.y"
    {
            if (timerv)
            {
              writeTime("used time:");
              startTimer();
            }
            if (rtimerv)
            {
              writeRTime("used real time:");
              startRTimer();
            }
            prompt_char = '>';
#ifdef HAVE_SDB
            if (sdb_flags & 2) { sdb_flags=1; YYERROR; }
#endif
            if(siCntrlc)
            {
              WerrorS("abort...");
              while((currentVoice!=NULL) && (currentVoice->prev!=NULL)) exitVoice();
              if (currentVoice!=NULL) currentVoice->ifsw=0;
            }
            if (errorreported) /* also catches abort... */
            {
              yyerror("");
            }
            if (inerror==2) PrintLn();
            errorreported = inerror = cmdtok = 0;
            lastreserved = currid = NULL;
            expected_parms = siCntrlc = FALSE;
          ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 356 "grammar.y"
    {currentVoice->ifsw=0;;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 358 "grammar.y"
    { (yyvsp[(1) - (2)].lv).CleanUp(); currentVoice->ifsw=0;;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 360 "grammar.y"
    {
            YYACCEPT;
          ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 364 "grammar.y"
    {
            currentVoice->ifsw=0;
            iiDebug();
          ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 369 "grammar.y"
    {currentVoice->ifsw=0;;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 371 "grammar.y"
    {
            #ifdef SIQ
            siq=0;
            #endif
            yyInRingConstruction = FALSE;
            currentVoice->ifsw=0;
            if (inerror)
            {
/*  bison failed here*/
              if ((inerror!=3) && ((yyvsp[(1) - (2)].i)<UMINUS) && ((yyvsp[(1) - (2)].i)>' '))
              {
                // 1: yyerror called
                // 2: scanner put actual string
                // 3: error rule put token+\n
                inerror=3;
                Print(" error at token `%s`\n",iiTwoOps((yyvsp[(1) - (2)].i)));
              }
/**/

            }
            if (!errorreported) WerrorS("...parse error");
            yyerror("");
            yyerrok;
#ifdef HAVE_SDB
            if ((sdb_flags & 1) && currentVoice->pi!=NULL)
            {
              currentVoice->pi->trace_flag |=1;
            }
            else
#endif
            if (myynest>0)
            {
              feBufferTypes t=currentVoice->Typ();
              //PrintS("leaving yyparse\n");
              exitBuffer(BT_proc);
              if (t==BT_example)
                YYACCEPT;
              else
                YYABORT;
            }
            else if (currentVoice->prev!=NULL)
            {
              exitVoice();
            }
#ifdef HAVE_SDB
            if (sdb_flags &2) sdb_flags=1;
#endif
          ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 429 "grammar.y"
    {if (currentVoice!=NULL) currentVoice->ifsw=0;;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 432 "grammar.y"
    { omFree((ADDRESS)(yyvsp[(2) - (2)].name)); ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 447 "grammar.y"
    {
            if(iiAssign(&(yyvsp[(1) - (2)].lv),&(yyvsp[(2) - (2)].lv))) YYERROR;
          ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 454 "grammar.y"
    {
            if (currRing==NULL) MYYERROR("no ring active (7)");
            syMakeMonom(&(yyval.lv),(yyvsp[(1) - (1)].name));
          ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 459 "grammar.y"
    {
            syMake(&(yyval.lv),(yyvsp[(1) - (1)].name));
          ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 463 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv), &(yyvsp[(1) - (3)].lv), COLONCOLON, &(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 467 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv), &(yyvsp[(1) - (3)].lv), '.', &(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 471 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(1) - (3)].lv),'(')) YYERROR;
          ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 475 "grammar.y"
    {
            if ((yyvsp[(1) - (4)].lv).next==NULL)
            {
              (yyvsp[(1) - (4)].lv).next=(leftv)omAllocBin(sleftv_bin);
              memcpy((yyvsp[(1) - (4)].lv).next,&(yyvsp[(3) - (4)].lv),sizeof(sleftv));
              if(iiExprArithM(&(yyval.lv),&(yyvsp[(1) - (4)].lv),'(')) YYERROR;
            }
            else if ((yyvsp[(1) - (4)].lv).rtyp==UNKNOWN)
            { // for x(i)(j)
              if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (4)].lv),'(',&(yyvsp[(3) - (4)].lv))) YYERROR;
            }
            else YYERROR;
          ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 489 "grammar.y"
    {
            if (currRing==NULL) MYYERROR("no ring active (8)");
            int j = 0;
            memset(&(yyval.lv),0,sizeof(sleftv));
            (yyval.lv).rtyp=VECTOR_CMD;
            leftv v = &(yyvsp[(2) - (3)].lv);
            while (v!=NULL)
            {
              int i,t;
              sleftv tmp;
              memset(&tmp,0,sizeof(tmp));
              i=iiTestConvert((t=v->Typ()),POLY_CMD);
              if((i==0) || (iiConvert(t /*v->Typ()*/,POLY_CMD,i,v,&tmp)))
              {
                pDelete((poly *)&(yyval.lv).data);
                (yyvsp[(2) - (3)].lv).CleanUp();
                MYYERROR("expected '[poly,...'");
              }
              poly p = (poly)tmp.CopyD(POLY_CMD);
              pSetCompP(p,++j);
              (yyval.lv).data = (void *)pAdd((poly)(yyval.lv).data,p);
              v->next=tmp.next;tmp.next=NULL;
              tmp.CleanUp();
              v=v->next;
            }
            (yyvsp[(2) - (3)].lv).CleanUp();
          ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 517 "grammar.y"
    {
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            int i = atoi((yyvsp[(1) - (1)].name));
            /*remember not to omFree($1)
            *because it is a part of the scanner buffer*/
            (yyval.lv).rtyp  = INT_CMD;
            (yyval.lv).data = (void *)(long)i;

            /* check: out of range input */
            int l = strlen((yyvsp[(1) - (1)].name))+2;
            number n;
            if (l >= MAX_INT_LEN)
            {
              char tmp[MAX_INT_LEN+5];
              sprintf(tmp,"%d",i);
              if (strcmp(tmp,(yyvsp[(1) - (1)].name))!=0)
              {
                n_Read((yyvsp[(1) - (1)].name),&n,coeffs_BIGINT);
                (yyval.lv).rtyp=BIGINT_CMD;
                (yyval.lv).data = n;
              }
            }
          ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 541 "grammar.y"
    {
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            (yyval.lv).rtyp = (yyvsp[(1) - (1)].i);
            (yyval.lv).data = (yyval.lv).Data();
          ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 547 "grammar.y"
    {
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            (yyval.lv).rtyp  = STRING_CMD;
            (yyval.lv).data = (yyvsp[(1) - (1)].name);
          ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 553 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i))) YYERROR;
          ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 557 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i))) YYERROR;
          ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 561 "grammar.y"
    {
            if(iiExprArithM(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i))) YYERROR;
          ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 565 "grammar.y"
    {
            if(iiExprArithM(&(yyval.lv),NULL,(yyvsp[(1) - (3)].i))) YYERROR;
          ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 569 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i))) YYERROR;
          ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 573 "grammar.y"
    {
            if(iiExprArithM(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i))) YYERROR;
          ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 577 "grammar.y"
    {
            if(iiExprArithM(&(yyval.lv),NULL,(yyvsp[(1) - (3)].i))) YYERROR;
          ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 581 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i))) YYERROR;
          ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 585 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i))) YYERROR;
          ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 589 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i))) YYERROR;
          ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 593 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i))) YYERROR;
          ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 597 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(3) - (6)].lv),(yyvsp[(1) - (6)].i),&(yyvsp[(5) - (6)].lv),TRUE)) YYERROR;
          ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 601 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(3) - (6)].lv),(yyvsp[(1) - (6)].i),&(yyvsp[(5) - (6)].lv),TRUE)) YYERROR;
          ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 605 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(3) - (6)].lv),(yyvsp[(1) - (6)].i),&(yyvsp[(5) - (6)].lv),TRUE)) YYERROR;
          ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 609 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(3) - (6)].lv),(yyvsp[(1) - (6)].i),&(yyvsp[(5) - (6)].lv),TRUE)) YYERROR;
          ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 613 "grammar.y"
    {
            if(iiExprArith3(&(yyval.lv),(yyvsp[(1) - (8)].i),&(yyvsp[(3) - (8)].lv),&(yyvsp[(5) - (8)].lv),&(yyvsp[(7) - (8)].lv))) YYERROR;
          ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 617 "grammar.y"
    {
            if(iiExprArith3(&(yyval.lv),(yyvsp[(1) - (8)].i),&(yyvsp[(3) - (8)].lv),&(yyvsp[(5) - (8)].lv),&(yyvsp[(7) - (8)].lv))) YYERROR;
          ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 621 "grammar.y"
    {
            if(iiExprArith3(&(yyval.lv),(yyvsp[(1) - (8)].i),&(yyvsp[(3) - (8)].lv),&(yyvsp[(5) - (8)].lv),&(yyvsp[(7) - (8)].lv))) YYERROR;
          ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 625 "grammar.y"
    {
            if(iiExprArith3(&(yyval.lv),(yyvsp[(1) - (8)].i),&(yyvsp[(3) - (8)].lv),&(yyvsp[(5) - (8)].lv),&(yyvsp[(7) - (8)].lv))) YYERROR;
          ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 629 "grammar.y"
    {
            if(iiExprArithM(&(yyval.lv),NULL,(yyvsp[(1) - (3)].i))) YYERROR;
          ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 633 "grammar.y"
    {
            int b=iiExprArithM(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i)); // handle branchTo
            if (b==TRUE) YYERROR;
            if (b==2) YYACCEPT;
          ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 639 "grammar.y"
    {
            if(iiExprArith3(&(yyval.lv),(yyvsp[(1) - (8)].i),&(yyvsp[(3) - (8)].lv),&(yyvsp[(5) - (8)].lv),&(yyvsp[(7) - (8)].lv))) YYERROR;
          ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 643 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(3) - (4)].lv),(yyvsp[(1) - (4)].i))) YYERROR;
          ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 647 "grammar.y"
    {
            if(iiExprArith3(&(yyval.lv),RING_CMD,&(yyvsp[(3) - (8)].lv),&(yyvsp[(5) - (8)].lv),&(yyvsp[(7) - (8)].lv))) YYERROR;
          ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 651 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(3) - (4)].lv),RING_CMD)) YYERROR;
          ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 655 "grammar.y"
    {
            if (iiARROW(&(yyval.lv),(yyvsp[(1) - (3)].name),(yyvsp[(3) - (3)].name))) YYERROR;
            omFree((ADDRESS)(yyvsp[(3) - (3)].name));
          ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 660 "grammar.y"
    {
             char emptyString[] = {'\0'};
             if (iiARROWnew(&(yyval.lv),emptyString,(yyvsp[(4) - (4)].name))) YYERROR;
             omFree((ADDRESS)(yyvsp[(4) - (4)].name));
           ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 666 "grammar.y"
    {
             if (iiARROWnew(&(yyval.lv),(yyvsp[(2) - (5)].name),(yyvsp[(5) - (5)].name))) YYERROR;
             omFree((ADDRESS)(yyvsp[(5) - (5)].name));
           ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 671 "grammar.y"
    {
             if (iiARROWnew(&(yyval.lv),&(yyvsp[(2) - (5)].lv),(yyvsp[(5) - (5)].name))) YYERROR;
             omFree((ADDRESS)(yyvsp[(5) - (5)].name));
           ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 675 "grammar.y"
    { (yyval.lv) = (yyvsp[(2) - (3)].lv); ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 680 "grammar.y"
    {
            leftv v = &(yyvsp[(1) - (3)].lv);
            while (v->next!=NULL)
            {
              v=v->next;
            }
            v->next = (leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&((yyvsp[(3) - (3)].lv)),sizeof(sleftv));
            (yyval.lv) = (yyvsp[(1) - (3)].lv);
          ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 696 "grammar.y"
    {
            if(iiExprArith3(&(yyval.lv),'[',&(yyvsp[(1) - (6)].lv),&(yyvsp[(3) - (6)].lv),&(yyvsp[(5) - (6)].lv))) YYERROR;
          ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 700 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (4)].lv),'[',&(yyvsp[(3) - (4)].lv))) YYERROR;
          ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 704 "grammar.y"
    {
            if (iiApply(&(yyval.lv), &(yyvsp[(3) - (6)].lv), (yyvsp[(5) - (6)].i), NULL)) YYERROR;
          ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 708 "grammar.y"
    {
            if (iiApply(&(yyval.lv), &(yyvsp[(3) - (6)].lv), (yyvsp[(5) - (6)].i), NULL)) YYERROR;
          ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 712 "grammar.y"
    {
            if (iiApply(&(yyval.lv), &(yyvsp[(3) - (6)].lv), (yyvsp[(5) - (6)].i), NULL)) YYERROR;
          ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 716 "grammar.y"
    {
            if (iiApply(&(yyval.lv), &(yyvsp[(3) - (6)].lv), (yyvsp[(5) - (6)].i), NULL)) YYERROR;
          ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 720 "grammar.y"
    {
            if (iiApply(&(yyval.lv), &(yyvsp[(3) - (6)].lv), (yyvsp[(5) - (6)].i), NULL)) YYERROR;
          ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 724 "grammar.y"
    {
            if (iiApply(&(yyval.lv), &(yyvsp[(3) - (6)].lv), 0, &(yyvsp[(5) - (6)].lv))) YYERROR;
          ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 728 "grammar.y"
    {
            (yyval.lv)=(yyvsp[(2) - (3)].lv);
          ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 732 "grammar.y"
    {
            #ifdef SIQ
            siq++;
            if (siq>0)
            { if (iiExprArith2(&(yyval.lv),&(yyvsp[(2) - (5)].lv),'=',&(yyvsp[(4) - (5)].lv))) YYERROR; }
            else
            #endif
            {
              memset(&(yyval.lv),0,sizeof((yyval.lv)));
              (yyval.lv).rtyp=NONE;
              if (iiAssign(&(yyvsp[(2) - (5)].lv),&(yyvsp[(4) - (5)].lv))) YYERROR;
            }
            #ifdef SIQ
            siq--;
            #endif
          ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 749 "grammar.y"
    {
            iiTestAssume(&(yyvsp[(2) - (5)].lv),&(yyvsp[(4) - (5)].lv));
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            (yyval.lv).rtyp=NONE;
          ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 755 "grammar.y"
    {
            #ifdef SIQ
            siq--;
            #endif
          ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 761 "grammar.y"
    {
            #ifdef SIQ
            if (siq<=0) (yyvsp[(4) - (5)].lv).Eval();
            #endif
            (yyval.lv)=(yyvsp[(4) - (5)].lv);
            #ifdef SIQ
            siq++;
            #endif
          ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 773 "grammar.y"
    {
            #ifdef SIQ
            siq++;
            #endif
          ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 781 "grammar.y"
    {
            #ifdef SIQ
            siq++;
            #endif
          ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 789 "grammar.y"
    {
            #ifdef SIQ
            siq--;
            #endif
          ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 798 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(1) - (2)].lv),PLUSPLUS)) YYERROR;
          ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 802 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(1) - (2)].lv),MINUSMINUS)) YYERROR;
          ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 806 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (3)].lv),'+',&(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 810 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (3)].lv),'-',&(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 814 "grammar.y"
    { /* also for *,% */
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (3)].lv),(yyvsp[(2) - (3)].i),&(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 818 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (3)].lv),'^',&(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 822 "grammar.y"
    { /* also for > */
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (3)].lv),(yyvsp[(2) - (3)].i),&(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 826 "grammar.y"
    { /* also for |*/
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (3)].lv),(yyvsp[(2) - (3)].i),&(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 830 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (3)].lv),NOTEQUAL,&(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 834 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (3)].lv),EQUAL_EQUAL,&(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 838 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (3)].lv),DOTDOT,&(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 842 "grammar.y"
    {
            if(iiExprArith2(&(yyval.lv),&(yyvsp[(1) - (3)].lv),':',&(yyvsp[(3) - (3)].lv))) YYERROR;
          ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 846 "grammar.y"
    {
            if (siq>0)
            { if (iiExprArith1(&(yyval.lv),&(yyvsp[(2) - (2)].lv),NOT)) YYERROR; }
            else
            {
              memset(&(yyval.lv),0,sizeof((yyval.lv)));
              int i; TESTSETINT((yyvsp[(2) - (2)].lv),i);
              (yyval.lv).rtyp  = INT_CMD;
              (yyval.lv).data = (void *)(long)(i == 0 ? 1 : 0);
            }
          ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 858 "grammar.y"
    {
            if(iiExprArith1(&(yyval.lv),&(yyvsp[(2) - (2)].lv),'-')) YYERROR;
          ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 866 "grammar.y"
    {
            if ((yyvsp[(1) - (2)].lv).rtyp==0)
            {
              Werror("`%s` is undefined",(yyvsp[(1) - (2)].lv).Fullname());
              YYERROR;
            }
            else if (((yyvsp[(1) - (2)].lv).rtyp==MODUL_CMD)
            // matrix m; m[2]=...
            && ((yyvsp[(1) - (2)].lv).e!=NULL) && ((yyvsp[(1) - (2)].lv).e->next==NULL))
            {
              MYYERROR("matrix must have 2 indices");
            }
            (yyval.lv) = (yyvsp[(1) - (2)].lv);
          ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 886 "grammar.y"
    {
            if ((yyvsp[(2) - (3)].lv).Typ()!=STRING_CMD)
            {
              MYYERROR("string expression expected");
            }
            (yyval.name) = (char *)(yyvsp[(2) - (3)].lv).CopyD(STRING_CMD);
            (yyvsp[(2) - (3)].lv).CleanUp();
          ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 898 "grammar.y"
    {
            if (iiDeclCommand(&(yyval.lv),&(yyvsp[(2) - (2)].lv),myynest,(yyvsp[(1) - (2)].i),&((yyvsp[(2) - (2)].lv).req_packhdl->idroot)))
              YYERROR;
          ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 903 "grammar.y"
    {
            if (iiDeclCommand(&(yyval.lv),&(yyvsp[(2) - (2)].lv),myynest,(yyvsp[(1) - (2)].i),&((yyvsp[(2) - (2)].lv).req_packhdl->idroot)))
              YYERROR;
          ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 908 "grammar.y"
    {
            if (iiDeclCommand(&(yyval.lv),&(yyvsp[(2) - (2)].lv),myynest,(yyvsp[(1) - (2)].i),&(currRing->idroot), TRUE)) YYERROR;
          ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 912 "grammar.y"
    {
            if (iiDeclCommand(&(yyval.lv),&(yyvsp[(2) - (2)].lv),myynest,(yyvsp[(1) - (2)].i),&(currRing->idroot), TRUE)) YYERROR;
          ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 916 "grammar.y"
    {
            int r; TESTSETINT((yyvsp[(4) - (8)].lv),r);
            int c; TESTSETINT((yyvsp[(7) - (8)].lv),c);
            leftv v;
            idhdl h;
            if (((yyvsp[(1) - (8)].i) == MATRIX_CMD) || ((yyvsp[(1) - (8)].i) == SMATRIX_CMD ))
            {
              if (iiDeclCommand(&(yyval.lv),&(yyvsp[(2) - (8)].lv),myynest,(yyvsp[(1) - (8)].i),&(currRing->idroot), TRUE)) YYERROR;
              v=&(yyval.lv);
              h=(idhdl)v->data;
              idDelete(&IDIDEAL(h));
              if ((yyvsp[(1) - (8)].i) == MATRIX_CMD)
                IDMATRIX(h) = mpNew(r,c);
              else
                IDIDEAL(h) = idInit(c,r);
              if (IDMATRIX(h)==NULL) YYERROR;
            }
            else if (((yyvsp[(1) - (8)].i) == INTMAT_CMD)||((yyvsp[(1) - (8)].i) == BIGINTMAT_CMD))
            {
              if (iiDeclCommand(&(yyval.lv),&(yyvsp[(2) - (8)].lv),myynest,(yyvsp[(1) - (8)].i),&((yyvsp[(2) - (8)].lv).req_packhdl->idroot)))
                YYERROR;
              v=&(yyval.lv);
              h=(idhdl)v->data;
              if ((yyvsp[(1) - (8)].i)==INTMAT_CMD)
              {
                delete IDINTVEC(h);
                IDINTVEC(h) = new intvec(r,c,0);
              }
              else
              {
                delete IDBIMAT(h);
                IDBIMAT(h) = new bigintmat(r, c, coeffs_BIGINT);
              }
              if (IDINTVEC(h)==NULL) YYERROR;
            }
          ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 953 "grammar.y"
    {
            if (((yyvsp[(1) - (2)].i) == MATRIX_CMD)||((yyvsp[(1) - (2)].i) == SMATRIX_CMD))
            {
              if (iiDeclCommand(&(yyval.lv),&(yyvsp[(2) - (2)].lv),myynest,(yyvsp[(1) - (2)].i),&(currRing->idroot), TRUE)) YYERROR;
            }
            else if (((yyvsp[(1) - (2)].i) == INTMAT_CMD)||((yyvsp[(1) - (2)].i) == BIGINTMAT_CMD))
            {
              if (iiDeclCommand(&(yyval.lv),&(yyvsp[(2) - (2)].lv),myynest,(yyvsp[(1) - (2)].i),&((yyvsp[(2) - (2)].lv).req_packhdl->idroot)))
                YYERROR;
              if ((yyvsp[(1) - (2)].i) == INTMAT_CMD)
              {
                leftv v=&(yyval.lv);
                idhdl h;
                do
                {
                  h=(idhdl)v->data;
                  delete IDINTVEC(h);
                  IDINTVEC(h) = new intvec(1,1,0);
                  v=v->next;
                } while (v!=NULL);
              }
            }
          ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 977 "grammar.y"
    {
            int t=(yyvsp[(1) - (3)].lv).Typ();
            sleftv r;
            memset(&r,0,sizeof(sleftv));
            if ((BEGIN_RING<t) && (t<END_RING))
            {
              if (iiDeclCommand(&r,&(yyvsp[(3) - (3)].lv),myynest,t,&(currRing->idroot), TRUE))
                YYERROR;
            }
            else
            {
              if (iiDeclCommand(&r,&(yyvsp[(3) - (3)].lv),myynest,t,&((yyvsp[(3) - (3)].lv).req_packhdl->idroot)))
                YYERROR;
            }
            leftv v=&(yyvsp[(1) - (3)].lv);
            while (v->next!=NULL) v=v->next;
            v->next=(leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&r,sizeof(sleftv));
            (yyval.lv)=(yyvsp[(1) - (3)].lv);
          ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 998 "grammar.y"
    {
            if (iiDeclCommand(&(yyval.lv),&(yyvsp[(2) - (2)].lv),myynest,(yyvsp[(1) - (2)].i),&((yyvsp[(2) - (2)].lv).req_packhdl->idroot)))
              YYERROR;
          ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 1011 "grammar.y"
    {
            leftv v = &(yyvsp[(2) - (5)].lv);
            while (v->next!=NULL)
            {
              v=v->next;
            }
            v->next = (leftv)omAllocBin(sleftv_bin);
            memcpy(v->next,&((yyvsp[(4) - (5)].lv)),sizeof(sleftv));
            (yyval.lv) = (yyvsp[(2) - (5)].lv);
          ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 1025 "grammar.y"
    {
          // let rInit take care of any errors
          (yyval.i)=rOrderName((yyvsp[(1) - (1)].name));
        ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 1033 "grammar.y"
    {
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            intvec *iv = new intvec(2);
            (*iv)[0] = 1;
            (*iv)[1] = (yyvsp[(1) - (1)].i);
            (yyval.lv).rtyp = INTVEC_CMD;
            (yyval.lv).data = (void *)iv;
          ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 1042 "grammar.y"
    {
            memset(&(yyval.lv),0,sizeof((yyval.lv)));
            leftv sl = &(yyvsp[(3) - (4)].lv);
            int slLength;
            {
              slLength =  exprlist_length(sl);
              int l = 2 +  slLength;
              intvec *iv = new intvec(l);
              (*iv)[0] = slLength;
              (*iv)[1] = (yyvsp[(1) - (4)].i);

              int i = 2;
              while ((i<l) && (sl!=NULL))
              {
                if (sl->Typ() == INT_CMD)
                {
                  (*iv)[i++] = (int)((long)(sl->Data()));
                }
                else if ((sl->Typ() == INTVEC_CMD)
                ||(sl->Typ() == INTMAT_CMD))
                {
                  intvec *ivv = (intvec *)(sl->Data());
                  int ll = 0,l = ivv->length();
                  for (; l>0; l--)
                  {
                    (*iv)[i++] = (*ivv)[ll++];
                  }
                }
                else
                {
                  delete iv;
                  (yyvsp[(3) - (4)].lv).CleanUp();
                  MYYERROR("wrong type in ordering");
                }
                sl = sl->next;
              }
              (yyval.lv).rtyp = INTVEC_CMD;
              (yyval.lv).data = (void *)iv;
            }
            (yyvsp[(3) - (4)].lv).CleanUp();
          ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 1088 "grammar.y"
    {
            (yyval.lv) = (yyvsp[(1) - (3)].lv);
            (yyval.lv).next = (sleftv *)omAllocBin(sleftv_bin);
            memcpy((yyval.lv).next,&(yyvsp[(3) - (3)].lv),sizeof(sleftv));
          ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 1098 "grammar.y"
    {
            (yyval.lv) = (yyvsp[(2) - (3)].lv);
          ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 1104 "grammar.y"
    {
            expected_parms = TRUE;
          ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 1122 "grammar.y"
    { newFile((yyvsp[(2) - (2)].name)); omFree((yyvsp[(2) - (2)].name)); ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 1127 "grammar.y"
    {
            feHelp((yyvsp[(2) - (3)].name));
            omFree((ADDRESS)(yyvsp[(2) - (3)].name));
          ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 1132 "grammar.y"
    {
            feHelp(NULL);
          ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 1139 "grammar.y"
    {
            singular_example((yyvsp[(2) - (3)].name));
            omFree((ADDRESS)(yyvsp[(2) - (3)].name));
          ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 1147 "grammar.y"
    {
          if (basePack!=(yyvsp[(2) - (2)].lv).req_packhdl)
          {
            if(iiExport(&(yyvsp[(2) - (2)].lv),0,currPack)) YYERROR;
          }
          else
            if (iiExport(&(yyvsp[(2) - (2)].lv),0)) YYERROR;
        ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 1159 "grammar.y"
    {
          leftv v=&(yyvsp[(2) - (2)].lv);
          if (v->rtyp!=IDHDL)
          {
            if (v->name!=NULL)
            {
               Werror("`%s` is undefined in kill",v->name);
               omFree((ADDRESS)v->name); v->name=NULL;
            }
            else               WerrorS("kill what ?");
          }
          else
          {
            killhdl((idhdl)v->data,v->req_packhdl);
          }
        ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 1176 "grammar.y"
    {
          leftv v=&(yyvsp[(3) - (3)].lv);
          if (v->rtyp!=IDHDL)
          {
            if (v->name!=NULL)
            {
               Werror("`%s` is undefined in kill",v->name);
               omFree((ADDRESS)v->name); v->name=NULL;
            }
            else               WerrorS("kill what ?");
          }
          else
          {
            killhdl((idhdl)v->data,v->req_packhdl);
          }
        ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 1196 "grammar.y"
    {
            list_cmd((yyvsp[(3) - (4)].i),NULL,"// ",TRUE);
          ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 1200 "grammar.y"
    {
            list_cmd((yyvsp[(3) - (4)].i),NULL,"// ",TRUE);
          ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 1204 "grammar.y"
    {
            if ((yyvsp[(3) - (4)].i)==QRING_CMD) (yyvsp[(3) - (4)].i)=RING_CMD;
            list_cmd((yyvsp[(3) - (4)].i),NULL,"// ",TRUE);
          ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 1209 "grammar.y"
    {
            list_cmd((yyvsp[(3) - (4)].i),NULL,"// ",TRUE);
          ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 1213 "grammar.y"
    {
            list_cmd(RING_CMD,NULL,"// ",TRUE);
          ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 1217 "grammar.y"
    {
            list_cmd((yyvsp[(3) - (4)].i),NULL,"// ",TRUE);
           ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 1221 "grammar.y"
    {
            list_cmd(PROC_CMD,NULL,"// ",TRUE);
          ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 1225 "grammar.y"
    {
            list_cmd(0,(yyvsp[(3) - (4)].lv).Fullname(),"// ",TRUE);
            (yyvsp[(3) - (4)].lv).CleanUp();
          ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 1230 "grammar.y"
    {
            if((yyvsp[(3) - (6)].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[(5) - (6)].i),NULL,"// ",TRUE);
            (yyvsp[(3) - (6)].lv).CleanUp();
          ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 1236 "grammar.y"
    {
            if((yyvsp[(3) - (6)].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[(5) - (6)].i),NULL,"// ",TRUE);
            (yyvsp[(3) - (6)].lv).CleanUp();
          ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 1242 "grammar.y"
    {
            if((yyvsp[(3) - (6)].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[(5) - (6)].i),NULL,"// ",TRUE);
            (yyvsp[(3) - (6)].lv).CleanUp();
          ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 1248 "grammar.y"
    {
            if((yyvsp[(3) - (6)].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[(5) - (6)].i),NULL,"// ",TRUE);
            (yyvsp[(3) - (6)].lv).CleanUp();
          ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 1254 "grammar.y"
    {
            if((yyvsp[(3) - (6)].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[(5) - (6)].i),NULL,"// ",TRUE);
            (yyvsp[(3) - (6)].lv).CleanUp();
          ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 1260 "grammar.y"
    {
            if((yyvsp[(3) - (6)].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[(5) - (6)].i),NULL,"// ",TRUE);
            (yyvsp[(3) - (6)].lv).CleanUp();
          ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 1266 "grammar.y"
    {
            if((yyvsp[(3) - (6)].lv).Typ() == PACKAGE_CMD)
              list_cmd((yyvsp[(5) - (6)].i),NULL,"// ",TRUE);
            (yyvsp[(3) - (6)].lv).CleanUp();
          ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 1278 "grammar.y"
    {
            list_cmd(-1,NULL,"// ",TRUE);
          ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 1284 "grammar.y"
    { yyInRingConstruction = TRUE; ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 1293 "grammar.y"
    {
            const char *ring_name = (yyvsp[(2) - (8)].lv).name;
            ring b=
            rInit(&(yyvsp[(4) - (8)].lv),            /* characteristik and list of parameters*/
                  &(yyvsp[(6) - (8)].lv),            /* names of ringvariables */
                  &(yyvsp[(8) - (8)].lv));            /* ordering */
            idhdl newRingHdl=NULL;

            if (b!=NULL)
            {
              newRingHdl=enterid(ring_name, myynest, RING_CMD,
                                   &((yyvsp[(2) - (8)].lv).req_packhdl->idroot),FALSE);
              (yyvsp[(2) - (8)].lv).CleanUp();
              if (newRingHdl!=NULL)
              {
                IDRING(newRingHdl)=b;
              }
              else
              {
                rKill(b);
              }
            }
            yyInRingConstruction = FALSE;
            if (newRingHdl==NULL)
            {
              MYYERROR("cannot make ring");
            }
            else
            {
              rSetHdl(newRingHdl);
            }
          ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 1326 "grammar.y"
    {
            const char *ring_name = (yyvsp[(2) - (2)].lv).name;
            if (!inerror) rDefault(ring_name);
            yyInRingConstruction = FALSE;
            (yyvsp[(2) - (2)].lv).CleanUp();
          ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 1333 "grammar.y"
    {
            yyInRingConstruction = FALSE;
            if (iiAssignCR(&(yyvsp[(2) - (4)].lv),&(yyvsp[(4) - (4)].lv))) YYERROR;
          ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 1338 "grammar.y"
    {
          yyInRingConstruction = FALSE;
          sleftv tmp;
          (yyvsp[(4) - (7)].lv).next=(leftv)omAlloc(sizeof(sleftv));
          memcpy((yyvsp[(4) - (7)].lv).next,&(yyvsp[(6) - (7)].lv),sizeof(sleftv));
          memset(&(yyvsp[(6) - (7)].lv),0,sizeof(sleftv));
          if (iiExprArithM(&tmp,&(yyvsp[(4) - (7)].lv),'[')) YYERROR;
          if (iiAssignCR(&(yyvsp[(2) - (7)].lv),&tmp)) YYERROR;
        ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 1351 "grammar.y"
    {
            if (((yyvsp[(1) - (2)].i)!=LIB_CMD)||(jjLOAD((yyvsp[(2) - (2)].name),TRUE))) YYERROR;
            omFree((yyvsp[(2) - (2)].name));
          ;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 1361 "grammar.y"
    {
            if (((yyvsp[(1) - (2)].i)==KEEPRING_CMD) && (myynest==0))
               MYYERROR("only inside a proc allowed");
            const char * n=(yyvsp[(2) - (2)].lv).Name();
            if (((yyvsp[(2) - (2)].lv).Typ()==RING_CMD)
            && ((yyvsp[(2) - (2)].lv).rtyp==IDHDL))
            {
              idhdl h=(idhdl)(yyvsp[(2) - (2)].lv).data;
              if ((yyvsp[(2) - (2)].lv).e!=NULL) h=rFindHdl((ring)(yyvsp[(2) - (2)].lv).Data(),NULL);
              //Print("setring %s lev %d (ptr:%x)\n",IDID(h),IDLEV(h),IDRING(h));
              if ((yyvsp[(1) - (2)].i)==KEEPRING_CMD)
              {
                if (h!=NULL)
                {
                  if (IDLEV(h)!=0)
                  {
                    if (iiExport(&(yyvsp[(2) - (2)].lv),myynest-1)) YYERROR;
#if 1
                    idhdl p=IDRING(h)->idroot;
                    idhdl root=p;
                    int prevlev=myynest-1;
                    while (p!=NULL)
                    {
                      if (IDLEV(p)==myynest)
                      {
                        idhdl old=root->get(IDID(p),prevlev);
                        if (old!=NULL)
                        {
                          if (BVERBOSE(V_REDEFINE))
                            Warn("redefining %s",IDID(p));
                          killhdl2(old,&root,IDRING(h));
                          IDRING(h)->idroot=root;
                        }
                        IDLEV(p)=prevlev;
                      }
                      p=IDNEXT(p);
                    }
#endif
                  }
                  iiLocalRing[myynest-1]=IDRING(h);
                }
                else
                {
                  Werror("%s is no identifier",n);
                  (yyvsp[(2) - (2)].lv).CleanUp();
                  YYERROR;
                }
              }
              if (h!=NULL) rSetHdl(h);
              else
              {
                Werror("cannot find the name of the basering %s",n);
                (yyvsp[(2) - (2)].lv).CleanUp();
                YYERROR;
              }
              (yyvsp[(2) - (2)].lv).CleanUp();
            }
            else
            {
              Werror("%s is no name of a ring/qring",n);
              (yyvsp[(2) - (2)].lv).CleanUp();
              YYERROR;
            }
          ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 1429 "grammar.y"
    {
            type_cmd(&((yyvsp[(2) - (2)].lv)));
          ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 1433 "grammar.y"
    {
            //Print("typ is %d, rtyp:%d\n",$1.Typ(),$1.rtyp);
            #ifdef SIQ
            if ((yyvsp[(1) - (1)].lv).rtyp!=COMMAND)
            {
            #endif
              if ((yyvsp[(1) - (1)].lv).Typ()==UNKNOWN)
              {
                if ((yyvsp[(1) - (1)].lv).name!=NULL)
                {
                  Werror("`%s` is undefined",(yyvsp[(1) - (1)].lv).name);
                  omFree((ADDRESS)(yyvsp[(1) - (1)].lv).name);
                }
                YYERROR;
              }
            #ifdef SIQ
            }
            #endif
            (yyvsp[(1) - (1)].lv).Print(&sLastPrinted);
            (yyvsp[(1) - (1)].lv).CleanUp(currRing);
            if (errorreported) YYERROR;
          ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 1462 "grammar.y"
    {
            int i; TESTSETINT((yyvsp[(3) - (5)].lv),i);
            if (i!=0)
            {
              newBuffer( (yyvsp[(5) - (5)].name), BT_if);
            }
            else
            {
              omFree((ADDRESS)(yyvsp[(5) - (5)].name));
              currentVoice->ifsw=1;
            }
          ;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 1475 "grammar.y"
    {
            if (currentVoice->ifsw==1)
            {
              currentVoice->ifsw=0;
              newBuffer( (yyvsp[(2) - (2)].name), BT_else);
            }
            else
            {
              if (currentVoice->ifsw!=2)
              {
                Warn("`else` without `if` in level %d",myynest);
              }
              omFree((ADDRESS)(yyvsp[(2) - (2)].name));
            }
            currentVoice->ifsw=0;
          ;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 1492 "grammar.y"
    {
            int i; TESTSETINT((yyvsp[(3) - (5)].lv),i);
            if (i)
            {
              if (exitBuffer(BT_break)) YYERROR;
            }
            currentVoice->ifsw=0;
          ;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 1501 "grammar.y"
    {
            if (exitBuffer(BT_break)) YYERROR;
            currentVoice->ifsw=0;
          ;}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 1506 "grammar.y"
    {
            if (contBuffer(BT_break)) YYERROR;
            currentVoice->ifsw=0;
          ;}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 1514 "grammar.y"
    {
            /* -> if(!$2) break; $3; continue;*/
            char * s = (char *)omAlloc( strlen((yyvsp[(2) - (3)].name)) + strlen((yyvsp[(3) - (3)].name)) + 36);
            sprintf(s,"whileif (!(%s)) break;\n%scontinue;\n " ,(yyvsp[(2) - (3)].name),(yyvsp[(3) - (3)].name));
            newBuffer(s,BT_break);
            omFree((ADDRESS)(yyvsp[(2) - (3)].name));
            omFree((ADDRESS)(yyvsp[(3) - (3)].name));
          ;}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 1526 "grammar.y"
    {
            /* $2 */
            /* if (!$3) break; $5; $4; continue; */
            char * s = (char *)omAlloc( strlen((yyvsp[(3) - (5)].name))+strlen((yyvsp[(4) - (5)].name))+strlen((yyvsp[(5) - (5)].name))+36);
            sprintf(s,"forif (!(%s)) break;\n%s%s;\ncontinue;\n "
                   ,(yyvsp[(3) - (5)].name),(yyvsp[(5) - (5)].name),(yyvsp[(4) - (5)].name));
            omFree((ADDRESS)(yyvsp[(3) - (5)].name));
            omFree((ADDRESS)(yyvsp[(4) - (5)].name));
            omFree((ADDRESS)(yyvsp[(5) - (5)].name));
            newBuffer(s,BT_break);
            s = (char *)omAlloc( strlen((yyvsp[(2) - (5)].name)) + 3);
            sprintf(s,"%s;\n",(yyvsp[(2) - (5)].name));
            omFree((ADDRESS)(yyvsp[(2) - (5)].name));
            newBuffer(s,BT_if);
          ;}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 1545 "grammar.y"
    {
            idhdl h = enterid((yyvsp[(2) - (3)].name),myynest,PROC_CMD,&IDROOT,TRUE);
            if (h==NULL) {omFree((ADDRESS)(yyvsp[(2) - (3)].name));omFree((ADDRESS)(yyvsp[(3) - (3)].name)); YYERROR;}
            iiInitSingularProcinfo(IDPROC(h),"", (yyvsp[(2) - (3)].name), 0, 0);
            IDPROC(h)->data.s.body = (char *)omAlloc(strlen((yyvsp[(3) - (3)].name))+31);;
            sprintf(IDPROC(h)->data.s.body,"parameter list #;\n%s;return();\n\n",(yyvsp[(3) - (3)].name));
            omFree((ADDRESS)(yyvsp[(3) - (3)].name));
            omFree((ADDRESS)(yyvsp[(2) - (3)].name));
          ;}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 1555 "grammar.y"
    {
            idhdl h = enterid((yyvsp[(1) - (3)].name),myynest,PROC_CMD,&IDROOT,TRUE);
            if (h==NULL)
            {
              omFree((ADDRESS)(yyvsp[(1) - (3)].name));
              omFree((ADDRESS)(yyvsp[(2) - (3)].name));
              omFree((ADDRESS)(yyvsp[(3) - (3)].name));
              YYERROR;
            }
            char *args=iiProcArgs((yyvsp[(2) - (3)].name),FALSE);
            omFree((ADDRESS)(yyvsp[(2) - (3)].name));
            iiInitSingularProcinfo(IDPROC(h),"", (yyvsp[(1) - (3)].name), 0, 0);
            IDPROC(h)->data.s.body = (char *)omAlloc(strlen((yyvsp[(3) - (3)].name))+strlen(args)+14);;
            sprintf(IDPROC(h)->data.s.body,"%s\n%s;return();\n\n",args,(yyvsp[(3) - (3)].name));
            omFree((ADDRESS)args);
            omFree((ADDRESS)(yyvsp[(3) - (3)].name));
            omFree((ADDRESS)(yyvsp[(1) - (3)].name));
          ;}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 1574 "grammar.y"
    {
            omFree((ADDRESS)(yyvsp[(3) - (4)].name));
            idhdl h = enterid((yyvsp[(1) - (4)].name),myynest,PROC_CMD,&IDROOT,TRUE);
            if (h==NULL)
            {
              omFree((ADDRESS)(yyvsp[(1) - (4)].name));
              omFree((ADDRESS)(yyvsp[(2) - (4)].name));
              omFree((ADDRESS)(yyvsp[(4) - (4)].name));
              YYERROR;
            }
            char *args=iiProcArgs((yyvsp[(2) - (4)].name),FALSE);
            omFree((ADDRESS)(yyvsp[(2) - (4)].name));
            iiInitSingularProcinfo(IDPROC(h),"", (yyvsp[(1) - (4)].name), 0, 0);
            omFree((ADDRESS)(yyvsp[(1) - (4)].name));
            IDPROC(h)->data.s.body = (char *)omAlloc(strlen((yyvsp[(4) - (4)].name))+strlen(args)+14);;
            sprintf(IDPROC(h)->data.s.body,"%s\n%s;return();\n\n",args,(yyvsp[(4) - (4)].name));
            omFree((ADDRESS)args);
            omFree((ADDRESS)(yyvsp[(4) - (4)].name));
          ;}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 1597 "grammar.y"
    {
            // decl. of type proc p(int i)
            if ((yyvsp[(1) - (2)].i)==PARAMETER)  { if (iiParameter(&(yyvsp[(2) - (2)].lv))) YYERROR; }
            else                { if (iiAlias(&(yyvsp[(2) - (2)].lv))) YYERROR; }
          ;}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 1603 "grammar.y"
    {
            // decl. of type proc p(i)
            sleftv tmp_expr;
            if ((yyvsp[(1) - (2)].i)==ALIAS_CMD) MYYERROR("alias requires a type");
            if ((iiDeclCommand(&tmp_expr,&(yyvsp[(2) - (2)].lv),myynest,DEF_CMD,&IDROOT))
            || (iiParameter(&tmp_expr)))
              YYERROR;
          ;}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 1615 "grammar.y"
    {
            iiSetReturn(&(yyvsp[(3) - (4)].lv));
            (yyvsp[(3) - (4)].lv).CleanUp();
            if (exitBuffer(BT_proc)) YYERROR;
          ;}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 1621 "grammar.y"
    {
            if ((yyvsp[(1) - (3)].i)==RETURN)
            {
              iiRETURNEXPR.Init();
              iiRETURNEXPR.rtyp=NONE;
              if (exitBuffer(BT_proc)) YYERROR;
            }
          ;}
    break;



/* Line 1464 of yacc.c  */
#line 4299 "grammar.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



