/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PLUS = 258,
     MINUS = 259,
     TIMES = 260,
     SLASH = 261,
     LES = 262,
     LEQ = 263,
     GTR = 264,
     GEQ = 265,
     EQL = 266,
     NEQ = 267,
     BECOMES = 268,
     OR = 269,
     AND = 270,
     NOT = 271,
     SEMICOLON = 272,
     LPAREN = 273,
     RPAREN = 274,
     LBRACKET = 275,
     RBRACKET = 276,
     LBRACE = 277,
     RBRACE = 278,
     COMMA = 279,
     IF = 280,
     ELSE = 281,
     WHILE = 282,
     WRITE = 283,
     READ = 284,
     INT = 285,
     BOOL = 286,
     CONST = 287,
     CHAR = 288,
     SELFADD = 289,
     SELFMIUNS = 290,
     REPEAT = 291,
     UNTIL = 292,
     XOR = 293,
     MOD = 294,
     ODD = 295,
     TRUE = 296,
     FALSE = 297,
     CALL = 298,
     DO = 299,
     FUNC = 300,
     EXIT = 301,
     FOR = 302,
     IDENT = 303,
     NUMBER = 304,
     CHARACTER = 305,
     IFX = 306
   };
#endif
/* Tokens.  */
#define PLUS 258
#define MINUS 259
#define TIMES 260
#define SLASH 261
#define LES 262
#define LEQ 263
#define GTR 264
#define GEQ 265
#define EQL 266
#define NEQ 267
#define BECOMES 268
#define OR 269
#define AND 270
#define NOT 271
#define SEMICOLON 272
#define LPAREN 273
#define RPAREN 274
#define LBRACKET 275
#define RBRACKET 276
#define LBRACE 277
#define RBRACE 278
#define COMMA 279
#define IF 280
#define ELSE 281
#define WHILE 282
#define WRITE 283
#define READ 284
#define INT 285
#define BOOL 286
#define CONST 287
#define CHAR 288
#define SELFADD 289
#define SELFMIUNS 290
#define REPEAT 291
#define UNTIL 292
#define XOR 293
#define MOD 294
#define ODD 295
#define TRUE 296
#define FALSE 297
#define CALL 298
#define DO 299
#define FUNC 300
#define EXIT 301
#define FOR 302
#define IDENT 303
#define NUMBER 304
#define CHARACTER 305
#define IFX 306




/* Copy the first part of user declarations.  */
#line 1 "cx.y"

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    #define true 1
    #define false 0
    #define bool int
    
    #define TXMAX 100 //符号表容量
    #define AL 10 //标识符最长长度
    #define LEVMAX 5 //嵌套深度
    #define AMAX 2047 //地址上界
    #define STACKSIZE 500 //栈元素上界
    #define CXMAX 200 //最多的pcode条数

    enum object {
        constant, 
        variable, 
        procedure
    };

    enum vartype {
        inttype,
        booltype,
        chartype
    };

    /* 符号表结构 */
    struct table1 {
        char name[AL]; /* 名字 */
        enum object kind;  /* 类型：const，var，procedure */
        int val; /* 数值，仅const使用 */
        int level;
        int adr; /* 地址，仅const不使用 */
        int size;
        enum vartype type; /* var的具体类型 */
    } table[TXMAX];

    enum fct {lit, opr, lod, sto, cal, ini, jmp, jpc, jpe, ext, blo, fre};

    struct instruction {
        enum fct f;
        int l;
        int a;
    } code[CXMAX];

    int tx; //符号表当前尾指针
    int cx; // pcode索引
    int lev; // 层次记录
    int leveltable[5]; // 嵌套索引表
    char id[AL];
    int num;
    bool listswitch;   /* 显示虚拟机代码与否 */
    bool tableswitch;  /* 显示符号表与否 */
    bool stackswitch;  /* 显示栈信息与否 */

    FILE* fin;      /* 输入源文件 */
    FILE* ftable;   /* 输出符号表 */
    FILE* fcode;    /* 输出虚拟机代码 */
    FILE* foutput;  /* 输出出错示意（如有错） */
    FILE* fresult;  /* 输出执行结果 */
    FILE* fstack;   /* 输出每一步栈的结果 */
    int err; // 程序中的错误个数
    extern int line;

    char varType[10]; //判断当前id是整形还是布尔类型还是字符类型

    void init();
    void enter(enum vartype t, enum object k);
    int position(char* s);
    void setdx(int n);
    void gen(enum fct x, int y, int z);
    void listall();
    void displaytable();
    void interpret();
    int base(int l, int *s, int b);
    
    int yylex();
    void yyerror(const char *s);
    void redirectInput(FILE *fin);

    #define YYERROR_VERBOSE 1


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 86 "cx.y"
{
    char *ident;
    int number;
}
/* Line 193 of yacc.c.  */
#line 288 "cx.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 301 "cx.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   281

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNRULES -- Number of states.  */
#define YYNSTATES  231

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     7,     8,    18,    19,    20,
      21,    22,    34,    38,    41,    42,    44,    48,    52,    55,
      56,    60,    63,    65,    67,    69,    71,    75,    77,    79,
      82,    83,    84,    91,    92,    93,    94,    95,   108,   111,
     112,   114,   116,   118,   120,   123,   125,   127,   129,   131,
     133,   135,   137,   139,   144,   149,   154,   160,   162,   166,
     168,   174,   176,   180,   183,   186,   189,   190,   199,   200,
     205,   206,   207,   216,   217,   229,   230,   242,   243,   244,
     245,   261,   263,   265,   267,   268,   270,   271,   275,   279,
     281,   285,   287,   289,   291,   294,   297,   301,   303,   307,
     311,   315,   319,   323,   327,   329,   331,   333,   335,   337,
     340,   343,   345,   349,   353,   355,   359,   363,   367,   371,
     373,   377,   379,   380,   381,   382
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    54,    -1,    -1,    -1,    -1,    22,    55,
      63,    66,    56,    71,    57,    79,    23,    -1,    -1,    -1,
      -1,    -1,    22,   120,    59,    63,    66,    60,    79,    61,
      23,    62,   121,    -1,    32,    64,    17,    -1,    32,    64,
      -1,    -1,    65,    -1,    64,    24,    65,    -1,    48,    13,
      49,    -1,    66,    67,    -1,    -1,    68,    69,    17,    -1,
      68,    69,    -1,    30,    -1,    31,    -1,    33,    -1,    70,
      -1,    69,    24,    70,    -1,     1,    -1,    48,    -1,    71,
      72,    -1,    -1,    -1,    45,    48,    18,    19,    73,    74,
      -1,    -1,    -1,    -1,    -1,    22,   120,    75,   118,    63,
      66,    76,    79,    77,    23,    78,   121,    -1,    79,    80,
      -1,    -1,    81,    -1,    82,    -1,    85,    -1,    87,    -1,
      88,    17,    -1,    89,    -1,    93,    -1,    58,    -1,   106,
      -1,    95,    -1,    97,    -1,    99,    -1,     1,    -1,   117,
      13,   114,    17,    -1,   117,    13,   112,    17,    -1,   117,
      13,   113,    17,    -1,    29,    18,    83,    19,    17,    -1,
      84,    -1,    83,    24,    84,    -1,   117,    -1,    28,    18,
      86,    19,    17,    -1,   114,    -1,    86,    24,   114,    -1,
      46,    17,    -1,   117,    34,    -1,   117,    35,    -1,    -1,
      25,    18,   107,    19,   119,    90,    80,    91,    -1,    -1,
      26,   119,    92,    80,    -1,    -1,    -1,    27,   119,    18,
     107,    19,   119,    94,    80,    -1,    -1,    44,   119,    80,
     119,    27,    18,   107,   119,    96,    19,    17,    -1,    -1,
      36,   119,    80,   119,    37,    18,   107,   119,    98,    19,
      17,    -1,    -1,    -1,    -1,    47,    18,   103,   119,   104,
     100,    17,   119,   101,   119,   105,    19,   102,   119,    80,
      -1,    81,    -1,    17,    -1,   107,    -1,    -1,    88,    -1,
      -1,    43,   117,    17,    -1,   107,    14,   108,    -1,   108,
      -1,   108,    15,   109,    -1,   109,    -1,   117,    -1,   112,
      -1,    16,   109,    -1,    40,   111,    -1,    18,   107,    19,
      -1,   110,    -1,   111,    11,   114,    -1,   111,    12,   114,
      -1,   111,     7,   114,    -1,   111,     8,   114,    -1,   111,
       9,   114,    -1,   111,    10,   114,    -1,   117,    -1,    49,
      -1,    41,    -1,    42,    -1,    50,    -1,     3,   115,    -1,
       4,   115,    -1,   115,    -1,   114,     3,   115,    -1,   114,
       4,   115,    -1,   116,    -1,   115,     5,   116,    -1,   115,
       6,   116,    -1,   115,    39,   116,    -1,   115,    38,   116,
      -1,   111,    -1,    18,   114,    19,    -1,    48,    -1,    -1,
      -1,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   113,   113,   118,   123,   127,   117,   143,   148,   155,
     159,   141,   167,   168,   172,   177,   178,   183,   192,   197,
     204,   208,   216,   220,   224,   232,   236,   240,   245,   260,
     261,   266,   265,   276,   281,   290,   294,   274,   302,   303,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   324,   333,   342,   355,   360,   361,   366,
     384,   389,   400,   414,   422,   437,   457,   456,   468,   467,
     476,   484,   483,   497,   495,   506,   504,   514,   519,   524,
     513,   537,   538,   542,   547,   553,   554,   558,   571,   575,
     579,   583,   587,   598,   599,   603,   607,   608,   612,   616,
     620,   624,   628,   632,   639,   662,   670,   675,   682,   690,
     694,   699,   703,   708,   717,   721,   726,   731,   736,   745,
     749,   756,   763,   769,   775,   783
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PLUS", "MINUS", "TIMES", "SLASH", "LES",
  "LEQ", "GTR", "GEQ", "EQL", "NEQ", "BECOMES", "OR", "AND", "NOT",
  "SEMICOLON", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LBRACE",
  "RBRACE", "COMMA", "IF", "ELSE", "WHILE", "WRITE", "READ", "INT", "BOOL",
  "CONST", "CHAR", "SELFADD", "SELFMIUNS", "REPEAT", "UNTIL", "XOR", "MOD",
  "ODD", "TRUE", "FALSE", "CALL", "DO", "FUNC", "EXIT", "FOR", "IDENT",
  "NUMBER", "CHARACTER", "IFX", "$accept", "program", "mainblock", "@1",
  "@2", "@3", "blockstm", "@4", "@5", "@6", "@7", "constdecl", "constlist",
  "constdef", "vardecls", "vardecl", "type", "varlist", "vardef",
  "procdecls", "procdecl", "@8", "procbody", "@9", "@10", "@11", "@12",
  "statements", "statement", "assignmentstm", "readstm", "readvarlist",
  "readvar", "writestm", "writeexplist", "exitstm", "selfaddminus",
  "ifstm", "@13", "elsestm", "@14", "whilestm", "@15", "dowhilestm", "@16",
  "repeatstm", "@17", "forstm", "@18", "@19", "@20", "for1", "for2",
  "for3", "callstm", "bexpr", "bterm", "bfactor", "rel", "idornum",
  "trueorfalse", "character", "expression", "term", "factor", "ident",
  "get_table_addr", "get_code_addr", "inc_level", "dec_level", 0
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
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    55,    56,    57,    54,    59,    60,    61,
      62,    58,    63,    63,    63,    64,    64,    65,    66,    66,
      67,    67,    68,    68,    68,    69,    69,    69,    70,    71,
      71,    73,    72,    75,    76,    77,    78,    74,    79,    79,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    81,    81,    81,    82,    83,    83,    84,
      85,    86,    86,    87,    88,    88,    90,    89,    92,    91,
      91,    94,    93,    96,    95,    98,    97,   100,   101,   102,
      99,   103,   103,   104,   104,   105,   105,   106,   107,   107,
     108,   108,   109,   109,   109,   109,   109,   109,   110,   110,
     110,   110,   110,   110,   111,   111,   112,   112,   113,   114,
     114,   114,   114,   114,   115,   115,   115,   115,   115,   116,
     116,   117,   118,   119,   120,   121
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     0,     0,     9,     0,     0,     0,
       0,    11,     3,     2,     0,     1,     3,     3,     2,     0,
       3,     2,     1,     1,     1,     1,     3,     1,     1,     2,
       0,     0,     6,     0,     0,     0,     0,    12,     2,     0,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     4,     5,     1,     3,     1,
       5,     1,     3,     2,     2,     2,     0,     8,     0,     4,
       0,     0,     8,     0,    11,     0,    11,     0,     0,     0,
      15,     1,     1,     1,     0,     1,     0,     3,     3,     1,
       3,     1,     1,     1,     2,     2,     3,     1,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     2,
       2,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     1,     0,     0,     0,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     2,    14,     1,     0,    19,     0,    13,
      15,     4,     0,    12,     0,    22,    23,    24,    30,    18,
       0,    17,    16,     5,    27,    28,    21,    25,     0,    39,
      29,    20,     0,     0,     0,    26,     0,    52,   124,     6,
       0,   123,     0,     0,   123,     0,   123,     0,     0,   121,
      47,    38,    40,    41,    42,    43,     0,    45,    46,    49,
      50,    51,    48,     0,    31,     7,     0,     0,     0,     0,
       0,     0,     0,    63,     0,    44,     0,    64,    65,     0,
      14,     0,     0,     0,   106,   107,   105,     0,    89,    91,
      97,     0,    93,   104,     0,     0,     0,     0,     0,   119,
      61,   111,   114,   104,     0,    57,    59,   123,    87,   123,
      82,    81,   123,     0,   108,     0,     0,     0,   124,    32,
      19,    94,     0,    95,     0,   123,     0,     0,     0,     0,
       0,     0,     0,     0,   109,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    84,
      54,    55,    53,    33,     8,    96,    88,    66,    90,   100,
     101,   102,   103,    98,    99,   123,   120,    60,    62,   112,
     113,   115,   116,   118,   117,    56,    58,     0,     0,    77,
      83,   122,    39,     0,    71,     0,     0,     0,    14,     0,
      70,     0,   123,   123,   123,    19,     0,   123,    67,    72,
      75,    73,    78,    34,    10,    68,     0,     0,   123,    39,
     125,     0,     0,     0,    86,     0,    11,    69,    76,    74,
      85,     0,     0,     0,    79,    36,   123,   125,     0,    37,
      80
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    18,    29,    50,    80,   182,   196,
     210,     7,     9,    10,    11,    19,    20,    26,    27,    23,
      30,    79,   119,   181,   209,   223,   227,    34,    51,    52,
      53,   104,   105,    54,    98,    55,    56,    57,   183,   198,
     211,    58,   191,    59,   207,    60,   206,    61,   187,   208,
     226,   112,   179,   221,    62,    87,    88,    89,    90,    99,
      92,   116,   100,   101,   102,   103,   188,    67,    65,   216
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -168
static const yytype_int16 yypact[] =
{
      12,  -168,    28,  -168,    30,  -168,    39,  -168,    76,     2,
    -168,    13,    52,  -168,    39,  -168,  -168,  -168,  -168,  -168,
       6,  -168,  -168,    60,  -168,  -168,    44,  -168,    59,  -168,
    -168,  -168,    63,   105,   143,  -168,   121,  -168,  -168,  -168,
     127,  -168,   128,   129,  -168,   100,  -168,   133,   135,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,   137,  -168,  -168,  -168,
    -168,  -168,  -168,    51,  -168,  -168,    88,   138,    27,   100,
     233,   141,   233,  -168,    -7,  -168,     9,  -168,  -168,   139,
      30,    88,    88,    83,  -168,  -168,  -168,    64,   145,  -168,
    -168,   205,  -168,   124,    88,     7,     7,    27,    72,  -168,
     123,    61,  -168,  -168,    78,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,   156,  -168,   157,   158,    20,  -168,  -168,
    -168,  -168,    84,  -168,    88,  -168,    88,    27,    27,    27,
      27,    27,    27,    94,    61,    61,    90,   165,    27,     7,
       7,     7,     7,     7,     7,   166,   100,   136,   161,    88,
    -168,  -168,  -168,  -168,    13,  -168,   145,  -168,  -168,   123,
     123,   123,   123,   123,   123,  -168,  -168,  -168,   123,    61,
      61,  -168,  -168,  -168,  -168,  -168,  -168,   167,   174,  -168,
     170,  -168,  -168,   233,  -168,    88,    88,   176,    30,   175,
     169,   233,   170,   170,  -168,  -168,   178,  -168,  -168,  -168,
    -168,  -168,  -168,    13,  -168,  -168,   180,   187,  -168,  -168,
    -168,   233,   190,   191,   100,   204,  -168,  -168,  -168,  -168,
    -168,   201,    99,   186,  -168,  -168,  -168,  -168,   233,  -168,
    -168
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,   -78,  -168,   196,  -114,  -168,  -168,  -168,   192,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -167,   -69,   151,
    -168,  -168,    82,  -168,  -168,  -168,    16,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,   -65,   111,   -77,  -168,   -61,
     160,  -168,   -58,   -87,   -25,   -34,  -168,   -30,   119,    11
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -93
static const yytype_int16 yytable[] =
{
      63,   107,   120,   109,   121,    91,   154,    24,   134,   135,
     110,    71,    95,    96,    70,   189,    72,   122,   117,    13,
      91,    91,   123,   139,   140,    97,    14,    97,     5,   133,
      95,    96,    93,    91,     1,   106,    63,   152,    63,   136,
     113,    49,   215,    15,    16,    97,    17,    93,    93,   158,
      84,    85,   169,   170,    25,    49,    86,    49,    86,   114,
      93,    31,     6,    91,    76,    91,   141,   142,    32,   159,
     160,   161,   162,   163,   164,    49,    86,   147,   124,   148,
     168,   203,   149,   125,   180,    77,    78,     8,    91,    12,
      93,   137,    93,   139,   140,   157,   138,   145,   124,   143,
     144,    21,   146,   155,    81,    28,    82,    33,   124,   166,
     195,    25,   106,   165,   190,    93,   171,   172,   173,   174,
     192,   193,   199,    36,    91,    91,   139,   140,    83,    84,
      85,    49,    86,    77,    78,   184,    49,    86,   -92,   -92,
      64,   -92,   217,   -92,    37,    66,    68,    69,    49,    63,
      73,    93,    93,    74,    75,    63,    94,    63,   108,   230,
     126,   118,   200,   201,   202,    38,    39,   205,    40,    76,
      41,    42,    43,   177,   150,   151,    37,    63,   214,    44,
     222,    63,   167,   175,   124,   185,    45,    46,   178,    47,
      48,    49,   186,   194,    63,   197,   228,    38,    -9,   212,
      40,   204,    41,    42,    43,    37,   213,   218,   219,   225,
      22,    44,   127,   128,   129,   130,   131,   132,    45,    46,
     224,    47,    48,    49,    35,   111,    38,   -35,   176,    40,
     220,    41,    42,    43,    37,   156,   115,   153,   229,     0,
      44,     0,     0,     0,     0,     0,     0,    45,    46,     0,
      47,    48,    49,     0,     0,    38,     0,     0,    40,     0,
      41,    42,    43,     0,     0,     0,     0,     0,     0,    44,
       0,     0,     0,     0,     0,     0,    45,    46,     0,    47,
      48,    49
};

static const yytype_int16 yycheck[] =
{
      34,    70,    80,    72,    81,    66,   120,     1,    95,    96,
      17,    45,     3,     4,    44,   182,    46,    82,    76,    17,
      81,    82,    83,     3,     4,    18,    24,    18,     0,    94,
       3,     4,    66,    94,    22,    69,    70,    17,    72,    97,
      74,    48,   209,    30,    31,    18,    33,    81,    82,   126,
      41,    42,   139,   140,    48,    48,    49,    48,    49,    50,
      94,    17,    32,   124,    13,   126,     5,     6,    24,   127,
     128,   129,   130,   131,   132,    48,    49,   107,    14,   109,
     138,   195,   112,    19,   149,    34,    35,    48,   149,    13,
     124,    19,   126,     3,     4,   125,    24,    19,    14,    38,
      39,    49,    24,    19,    16,    45,    18,    48,    14,    19,
     188,    48,   146,    19,   183,   149,   141,   142,   143,   144,
     185,   186,   191,    18,   185,   186,     3,     4,    40,    41,
      42,    48,    49,    34,    35,   165,    48,    49,    14,    15,
      19,    17,   211,    19,     1,    18,    18,    18,    48,   183,
      17,   185,   186,    18,    17,   189,    18,   191,    17,   228,
      15,    22,   192,   193,   194,    22,    23,   197,    25,    13,
      27,    28,    29,    37,    17,    17,     1,   211,   208,    36,
     214,   215,    17,    17,    14,    18,    43,    44,    27,    46,
      47,    48,    18,    17,   228,    26,   226,    22,    23,    19,
      25,    23,    27,    28,    29,     1,    19,    17,    17,    23,
      14,    36,     7,     8,     9,    10,    11,    12,    43,    44,
      19,    46,    47,    48,    32,    74,    22,    23,   146,    25,
     214,    27,    28,    29,     1,   124,    76,   118,   227,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,
      46,    47,    48,    -1,    -1,    22,    -1,    -1,    25,    -1,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    46,
      47,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    22,    53,    54,    55,     0,    32,    63,    48,    64,
      65,    66,    13,    17,    24,    30,    31,    33,    56,    67,
      68,    49,    65,    71,     1,    48,    69,    70,    45,    57,
      72,    17,    24,    48,    79,    70,    18,     1,    22,    23,
      25,    27,    28,    29,    36,    43,    44,    46,    47,    48,
      58,    80,    81,    82,    85,    87,    88,    89,    93,    95,
      97,    99,   106,   117,    19,   120,    18,   119,    18,    18,
     119,   117,   119,    17,    18,    17,    13,    34,    35,    73,
      59,    16,    18,    40,    41,    42,    49,   107,   108,   109,
     110,   111,   112,   117,    18,     3,     4,    18,    86,   111,
     114,   115,   116,   117,    83,    84,   117,    80,    17,    80,
      17,    81,   103,   117,    50,   112,   113,   114,    22,    74,
      63,   109,   107,   111,    14,    19,    15,     7,     8,     9,
      10,    11,    12,   107,   115,   115,   114,    19,    24,     3,
       4,     5,     6,    38,    39,    19,    24,   119,   119,   119,
      17,    17,    17,   120,    66,    19,   108,   119,   109,   114,
     114,   114,   114,   114,   114,    19,    19,    17,   114,   115,
     115,   116,   116,   116,   116,    17,    84,    37,    27,   104,
     107,    75,    60,    90,   119,    18,    18,   100,   118,    79,
      80,    94,   107,   107,    17,    63,    61,    26,    91,    80,
     119,   119,   119,    66,    23,   119,    98,    96,   101,    76,
      62,    92,    19,    19,   119,    79,   121,    80,    17,    17,
      88,   105,   117,    77,    19,    23,   102,    78,   119,   121,
      80
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

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
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 118 "cx.y"
    {
        (yyval.number) = cx;
        gen(jmp, 0, 0);
    ;}
    break;

  case 4:
#line 123 "cx.y"
    {
        setdx((yyvsp[(4) - (4)].number));
    ;}
    break;

  case 5:
#line 127 "cx.y"
    {
        code[(yyvsp[(2) - (6)].number)].a = cx;
        gen(ini, 0, (yyvsp[(4) - (6)].number) + 3);
        printf("mainblock:\n");
        displaytable();
    ;}
    break;

  case 6:
#line 135 "cx.y"
    {
        gen(opr, 0, 0);
    ;}
    break;

  case 7:
#line 143 "cx.y"
    {
        leveltable[lev] = tx;
        gen(blo, 0, 0);
    ;}
    break;

  case 8:
#line 148 "cx.y"
    {
        setdx((yyvsp[(5) - (5)].number));
        gen(ini, 0, (yyvsp[(5) - (5)].number) + 3);
        printf("blockstm:\n");
        displaytable();
    ;}
    break;

  case 9:
#line 155 "cx.y"
    {
        gen(fre, 0, 0);
    ;}
    break;

  case 10:
#line 159 "cx.y"
    {
        tx = leveltable[lev];
    ;}
    break;

  case 13:
#line 169 "cx.y"
    {
        yyerror("Miss SEMICOLON");  //错误处理，常量声明缺少结尾分号
    ;}
    break;

  case 17:
#line 184 "cx.y"
    {        
        strcpy(id, (yyvsp[(1) - (3)].ident));   
        num = (yyvsp[(3) - (3)].number);
        enter(inttype, constant);
    ;}
    break;

  case 18:
#line 193 "cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (2)].number) + (yyvsp[(2) - (2)].number);
    ;}
    break;

  case 19:
#line 197 "cx.y"
    {
        (yyval.number) = 0;
    ;}
    break;

  case 20:
#line 205 "cx.y"
    {
        (yyval.number) = (yyvsp[(2) - (3)].number);         /* 传递变量声明的个数 */
    ;}
    break;

  case 21:
#line 209 "cx.y"
    {
        (yyval.number) = (yyvsp[(2) - (2)].number);         
        yyerror("Miss SEMICOLON");  //错误处理，变量声明缺少结尾分号
    ;}
    break;

  case 22:
#line 217 "cx.y"
    {
        strcpy(varType, "int");
    ;}
    break;

  case 23:
#line 221 "cx.y"
    {
        strcpy(varType, "bool");
    ;}
    break;

  case 24:
#line 225 "cx.y"
    {
        strcpy(varType, "char");
    ;}
    break;

  case 25:
#line 233 "cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (1)].number);
    ;}
    break;

  case 26:
#line 237 "cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (3)].number) + (yyvsp[(3) - (3)].number);  /* 变量声明的个数相加 */
    ;}
    break;

  case 27:
#line 240 "cx.y"
    {/*错误处理*/;}
    break;

  case 28:
#line 246 "cx.y"
    {
        strcpy(id, (yyvsp[(1) - (1)].ident));
        if (!strcmp(varType, "int")) 
            enter(inttype, variable); 
        else if(!strcmp(varType, "bool"))
            enter(booltype, variable);
        else if(!strcmp(varType, "char"))
            enter(chartype, variable);
        (yyval.number) = 1;
    ;}
    break;

  case 31:
#line 266 "cx.y"
    {
        strcpy(id, (yyvsp[(2) - (4)].ident));
        enter(-1, procedure);
    ;}
    break;

  case 33:
#line 276 "cx.y"
    {
        leveltable[lev] = tx;
    ;}
    break;

  case 34:
#line 281 "cx.y"
    {
        setdx((yyvsp[(6) - (6)].number));
        table[(yyvsp[(4) - (6)].number)].adr = cx;
        table[(yyvsp[(4) - (6)].number)].size = (yyvsp[(6) - (6)].number) + 3;
        gen(ini, 0, (yyvsp[(6) - (6)].number) + 3);
        printf("procbody:\n");        
        displaytable();
    ;}
    break;

  case 35:
#line 290 "cx.y"
    {
        gen(opr, 0, 0);
    ;}
    break;

  case 36:
#line 294 "cx.y"
    {
        tx = leveltable[lev];
    ;}
    break;

  case 52:
#line 319 "cx.y"
    {/*错误处理*/;}
    break;

  case 53:
#line 325 "cx.y"
    {
        if ((yyvsp[(1) - (4)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (4)].number)].kind == variable && table[(yyvsp[(1) - (4)].number)].type == inttype)
            gen(sto, lev - table[(yyvsp[(1) - (4)].number)].level, table[(yyvsp[(1) - (4)].number)].adr);
        else
            yyerror("Symbol should be a variable and type should be int");
    ;}
    break;

  case 54:
#line 334 "cx.y"
    {
        if ((yyvsp[(1) - (4)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (4)].number)].kind == variable && table[(yyvsp[(1) - (4)].number)].type == booltype) 
            gen(sto, lev - table[(yyvsp[(1) - (4)].number)].level, table[(yyvsp[(1) - (4)].number)].adr);
        else
            yyerror("Symbol should be a variable and type should be bool");
    ;}
    break;

  case 55:
#line 343 "cx.y"
    {
        if ((yyvsp[(1) - (4)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (4)].number)].kind == variable && table[(yyvsp[(1) - (4)].number)].type == chartype) 
            gen(sto, lev - table[(yyvsp[(1) - (4)].number)].level, table[(yyvsp[(1) - (4)].number)].adr);
        else
            yyerror("Symbol should be a variable and type should be char");
    ;}
    break;

  case 59:
#line 367 "cx.y"
    {
        if (table[(yyvsp[(1) - (1)].number)].kind == variable && table[(yyvsp[(1) - (1)].number)].type == inttype) {
            gen(opr, 0, 16);
            gen(sto, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
        }
        else if (table[(yyvsp[(1) - (1)].number)].kind == variable && table[(yyvsp[(1) - (1)].number)].type == chartype) {
            gen(opr, 0, 17);
            gen(sto, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
        }
        else {
            yyerror("Can only read int or char variable");
        }
    ;}
    break;

  case 61:
#line 390 "cx.y"
    {
        if ((yyvsp[(1) - (1)].number) == 1) {  //字符
            gen(opr, 0, 23);
            gen(opr, 0, 15);
        }
        else {  // 整数
            gen(opr, 0, 14);
            gen(opr, 0, 15);
        }
    ;}
    break;

  case 62:
#line 401 "cx.y"
    {
        if ((yyvsp[(3) - (3)].number) == 1) {  //　字符
            gen(opr, 0, 23);
            gen(opr, 0, 15);
        }
        else {  // 整数
            gen(opr, 0, 14);
            gen(opr, 0, 15);
        }
    ;}
    break;

  case 63:
#line 415 "cx.y"
    {
        gen(ext, 0, 0);
    ;}
    break;

  case 64:
#line 423 "cx.y"
    { 
        if ((yyvsp[(1) - (2)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (2)].number)].kind == constant) 
            yyerror("Constant cannot selfadd");
        else if (table[(yyvsp[(1) - (2)].number)].kind == variable && table[(yyvsp[(1) - (2)].number)].type != inttype) 
            yyerror("Only int variable can selfadd");
        else if (table[(yyvsp[(1) - (2)].number)].kind == variable && table[(yyvsp[(1) - (2)].number)].type == inttype) {
            gen(lod, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
            gen(lit, 0, 1);
            gen(opr, 0, 2);
            gen(sto, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
        }
    ;}
    break;

  case 65:
#line 438 "cx.y"
    {
        if ((yyvsp[(1) - (2)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (2)].number)].kind == constant) 
            yyerror("Constant cannot selfminus");
        else if (table[(yyvsp[(1) - (2)].number)].kind == variable && table[(yyvsp[(1) - (2)].number)].type != inttype) 
            yyerror("Only int variable can selfminus");
        else if (table[(yyvsp[(1) - (2)].number)].kind == variable && table[(yyvsp[(1) - (2)].number)].type == inttype) {
            gen(lod, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
            gen(lit, 0, 1);
            gen(opr, 0, 3);
            gen(sto, lev - table[(yyvsp[(1) - (2)].number)].level, table[(yyvsp[(1) - (2)].number)].adr);
        }
    ;}
    break;

  case 66:
#line 457 "cx.y"
    {
        gen(jpc, 0, 0);
    ;}
    break;

  case 67:
#line 461 "cx.y"
    {
        code[(yyvsp[(5) - (8)].number)].a = (yyvsp[(8) - (8)].number); //回填，不满足条件时跳到哪里
    ;}
    break;

  case 68:
#line 468 "cx.y"
    {
        gen(jmp, 0, 0); //满足if条件的直接jmp走
    ;}
    break;

  case 69:
#line 472 "cx.y"
    {
        (yyval.number) = (yyvsp[(2) - (4)].number) + 1; //jmp的后一条指令位置
        code[(yyvsp[(2) - (4)].number)].a = cx; //回填，满足if条件的跳到哪里
    ;}
    break;

  case 70:
#line 477 "cx.y"
    {
        (yyval.number) = cx;
    ;}
    break;

  case 71:
#line 484 "cx.y"
    {
        gen(jpc, 0, 0);
    ;}
    break;

  case 72:
#line 488 "cx.y"
    {
        gen(jmp, 0, (yyvsp[(2) - (8)].number));
        code[(yyvsp[(6) - (8)].number)].a = cx;
    ;}
    break;

  case 73:
#line 497 "cx.y"
    {
        gen(jpe, 0, (yyvsp[(2) - (8)].number));
    ;}
    break;

  case 75:
#line 506 "cx.y"
    {
        gen(jpc, 0, (yyvsp[(2) - (8)].number));
    ;}
    break;

  case 77:
#line 514 "cx.y"
    {
        if ((yyvsp[(5) - (5)].number) == 1)
            gen(lit, 0, 1);
    ;}
    break;

  case 78:
#line 519 "cx.y"
    {
        gen(jpe, 0, 0);
        gen(jmp, 0, 0);
    ;}
    break;

  case 79:
#line 524 "cx.y"
    {
        gen(jmp, 0, (yyvsp[(4) - (12)].number));
    ;}
    break;

  case 80:
#line 529 "cx.y"
    {
        gen(jmp, 0, (yyvsp[(10) - (15)].number));
        code[(yyvsp[(8) - (15)].number)].a = (yyvsp[(14) - (15)].number);
        code[(yyvsp[(8) - (15)].number) + 1].a = cx;
    ;}
    break;

  case 83:
#line 543 "cx.y"
    {
        (yyval.number) = 0; 
    ;}
    break;

  case 84:
#line 547 "cx.y"
    {
        (yyval.number) = 1; //无条件
    ;}
    break;

  case 87:
#line 559 "cx.y"
    {
        if ((yyvsp[(2) - (3)].number) == 0)
            yyerror("Call symbol does not exist");
        else if (table[(yyvsp[(2) - (3)].number)].kind != procedure)
            yyerror("Call symbol should be a procedure");
        else
            gen(cal, lev - table[(yyvsp[(2) - (3)].number)].level, table[(yyvsp[(2) - (3)].number)].adr);    
    ;}
    break;

  case 88:
#line 572 "cx.y"
    {
        gen(opr, 0, 22);
    ;}
    break;

  case 90:
#line 580 "cx.y"
    {
        gen(opr, 0, 21);
    ;}
    break;

  case 92:
#line 588 "cx.y"
    { 
        if ((yyvsp[(1) - (1)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (1)].number)].kind == procedure)
            yyerror("Symbol should not be a procedure");
        else if (table[(yyvsp[(1) - (1)].number)].kind == constant)
            gen(lit, 0, table[(yyvsp[(1) - (1)].number)].val);
        else if (table[(yyvsp[(1) - (1)].number)].kind == variable)
            gen(lod, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
    ;}
    break;

  case 94:
#line 600 "cx.y"
    {
        gen(opr, 0, 20);
    ;}
    break;

  case 95:
#line 604 "cx.y"
    {
        gen(opr, 0, 6);
    ;}
    break;

  case 98:
#line 613 "cx.y"
    {
        gen(opr, 0, 8);
    ;}
    break;

  case 99:
#line 617 "cx.y"
    {
        gen(opr, 0, 9);
    ;}
    break;

  case 100:
#line 621 "cx.y"
    {
        gen(opr, 0, 10);
    ;}
    break;

  case 101:
#line 625 "cx.y"
    {
        gen(opr, 0, 13);
    ;}
    break;

  case 102:
#line 629 "cx.y"
    {
        gen(opr, 0, 12);
    ;}
    break;

  case 103:
#line 633 "cx.y"
    {
        gen(opr, 0, 11);
    ;}
    break;

  case 104:
#line 640 "cx.y"
    { 
        if ((yyvsp[(1) - (1)].number) == 0)
            yyerror("Symbol does not exist");
        else if (table[(yyvsp[(1) - (1)].number)].kind == procedure)
            yyerror("Symbol should not be a procedure");
        else if (table[(yyvsp[(1) - (1)].number)].kind == constant) {
            (yyval.number) = 0;
            gen(lit, 0, table[(yyvsp[(1) - (1)].number)].val);
        }
        else if (table[(yyvsp[(1) - (1)].number)].kind == variable && table[(yyvsp[(1) - (1)].number)].type == inttype) {
            (yyval.number) = 0; 
            gen(lod, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
        }
        else if (table[(yyvsp[(1) - (1)].number)].kind == variable && table[(yyvsp[(1) - (1)].number)].type == booltype) {
            (yyval.number) = 0; 
            gen(lod, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
        }
        else if (table[(yyvsp[(1) - (1)].number)].kind == variable && table[(yyvsp[(1) - (1)].number)].type == chartype) {
            (yyval.number) = 1;
            gen(lod, lev - table[(yyvsp[(1) - (1)].number)].level, table[(yyvsp[(1) - (1)].number)].adr);
        }
    ;}
    break;

  case 105:
#line 663 "cx.y"
    {
        (yyval.number) = 0;
        gen(lit, 0, (yyvsp[(1) - (1)].number));
    ;}
    break;

  case 106:
#line 671 "cx.y"
    {
        gen(lit, 0, 1);
    ;}
    break;

  case 107:
#line 676 "cx.y"
    {
        gen(lit, 0, 0);
    ;}
    break;

  case 108:
#line 683 "cx.y"
    {
        gen(lit, 0, (yyvsp[(1) - (1)].ident)[1]);
    ;}
    break;

  case 109:
#line 691 "cx.y"
    {
        (yyval.number) = 0;
    ;}
    break;

  case 110:
#line 695 "cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 1);
    ;}
    break;

  case 111:
#line 700 "cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (1)].number);
    ;}
    break;

  case 112:
#line 704 "cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 2);
    ;}
    break;

  case 113:
#line 709 "cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 3);
    ;}
    break;

  case 114:
#line 718 "cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (1)].number);
    ;}
    break;

  case 115:
#line 722 "cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 4);
    ;}
    break;

  case 116:
#line 727 "cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 5);
    ;}
    break;

  case 117:
#line 732 "cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 18);
    ;}
    break;

  case 118:
#line 737 "cx.y"
    {
        (yyval.number) = 0;
        gen(opr, 0, 19);
    ;}
    break;

  case 119:
#line 746 "cx.y"
    {
        (yyval.number) = (yyvsp[(1) - (1)].number);
    ;}
    break;

  case 120:
#line 750 "cx.y"
    {
        (yyval.number) = 0;
    ;}
    break;

  case 121:
#line 757 "cx.y"
    {
        (yyval.number) = position((yyvsp[(1) - (1)].ident)); 
    ;}
    break;

  case 122:
#line 763 "cx.y"
    {
        (yyval.number) = tx;
    ;}
    break;

  case 123:
#line 769 "cx.y"
    {
        (yyval.number) = cx;
    ;}
    break;

  case 124:
#line 775 "cx.y"
    {
        lev++;               
        if (lev > LEVMAX)   /* 嵌套层数过多 */
            yyerror("Lev is too big");    
    ;}
    break;

  case 125:
#line 783 "cx.y"
    {
        lev--;
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2451 "cx.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 788 "cx.y"


void yyerror(const char *s) {
    err++;
    printf("%s in line %d\n", s, line);
    fprintf(foutput, "%s in line %d\n", s, line);
}

void init() {
    tx = 0;
    cx = 0;
    lev = 0;   
    leveltable[0] = 0;
    num = 0;
    err = 0;
}

/* 在符号表中加入一项 */
void enter(enum vartype t, enum object k) {
    tx = tx + 1;
    strcpy(table[tx].name, id);
    table[tx].kind = k;
    switch(k) {
    case constant:
        table[tx].val = num;
        break;
    case variable:
        table[tx].level = lev;
        table[tx].type = t;
        break;
    case procedure:
        table[tx].level = lev;
        break;
    }
}

/* 查找标识符在符号表中的位置 */
int position(char id[]) {
    int i;
    strcpy(table[0].name, id);
    i = tx;
    while (strcmp(table[i].name,id) != 0) {
        i--;
    }
    return i;
}

/* 为本层变量分配相对地址，从3开始分配 */
void setdx(int n) {
    int i;
    for (i = 1; i <= n; i++) {
        table[tx - i + 1].adr = n - i + 3;
    }
}

/* 生成虚拟机代码 */
void gen(enum fct x, int y, int z) {
    if (cx >= CXMAX) {
        printf("Program is too long!\n"); /* 生成的虚拟机代码程序过长 */
        exit(1);
    }
    if (z >= AMAX) {
        printf("Displacement address is too big!\n"); /* 地址偏移越界 */
        exit(1);
    }
    code[cx].f = x;
    code[cx].l = y;
    code[cx].a = z;
    cx++;
}

/* 输出所有目标代码  */
void listall() {
    int i;
    char name[][5] = {
        {"lit"}, {"opr"}, {"lod"}, {"sto"}, {"cal"}, {"int"}, 
        {"jmp"}, {"jpc"}, {"jpe"}, {"ext"}, {"blo"}, {"fre"}
    };
    if (listswitch) {
        for (i = 0; i < cx; i++) {
            printf("%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
            fprintf(fcode,"%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
        }
        printf("\n");
    }
}

/* 输出符号表 */
void displaytable() {
    int i;
    if (tableswitch) {
        for (i = 1; i <= tx; i++) {
            switch (table[i].kind)
            {
            case constant:
                printf("    %d const %s ", i, table[i].name);
                printf("val=%d\n", table[i].val);
                fprintf(ftable, "    %d const %s ", i, table[i].name);
                fprintf(ftable, "val=%d\n", table[i].val);
                break;
            case variable:
                printf("    %d var   %s ", i, table[i].name);
                printf("lev=%d addr=%d type=%d \n", table[i].level, table[i].adr,  table[i].type);
                fprintf(ftable, "    %d var   %s ", i, table[i].name);
                fprintf(ftable, "lev=%d addr=%d\n", table[i].level, table[i].adr);
                break;
            case procedure:
                printf("    %d proc  %s ", i, table[i].name);
                printf("lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
                fprintf(ftable,"    %d proc  %s ", i, table[i].name);
                fprintf(ftable,"lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
                break;
            }
        }
        printf("\n");
        fprintf(ftable, "\n");
    }
}

void printstack(int t, int p, int *s) {
    int i;
    if (stackswitch) {
        fprintf(fstack, "pcode %2d: |", p);
        for (i = 1; i <= t; i++)
            fprintf(fstack, " %2d |", s[i]);
        fprintf(fstack, "%s", "\n");
    }
}

/* 解释程序 */
void interpret() {
	int p = 0; /* 指令指针 */
    int b = 1; /* 指令基址 */
    int t = 0; /* 栈顶指针 */
    struct instruction i; /* 存放当前指令 */
    int s[STACKSIZE]; /* 栈 */

	printf("Start CX interpret\n");
 	fprintf(fresult,"Start CX interpret\n");
	s[0] = 0;
	s[1] = 0;
	s[2] = 0;
	s[3] = 0;
	do {
		i = code[p];  /* 读当前指令 */
        p = p + 1;
        switch (i.f)
        {
        case lit: /* 将常量a的值取到栈顶 */
            t = t + 1;
            s[t] = i.a;
            printstack(t, p, s);
            break;
        case opr: /* 数学、逻辑运算 */
            switch(i.a) {
            case 0:  /* 函数调用结束后返回 */
                t = b - 1;
                p = s[t + 3];
                b = s[t + 2];
                break;
            case 1: /* 栈顶元素取反 */
                s[t] = -s[t];
                break;
            case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
                t = t - 1;
                s[t] = s[t] + s[t + 1];
                break;
            case 3:/* 次栈顶项减去栈顶项 */
                t = t - 1;
                s[t] = s[t] - s[t + 1];
                break;
            case 4:/* 次栈顶项乘以栈顶项 */
                t = t - 1;
                s[t] = s[t] * s[t + 1];
                break;
            case 5:/* 次栈顶项除以栈顶项 */
                t = t - 1;
                s[t] = s[t] / s[t + 1];
                break;
            case 6:/* 栈顶元素的奇偶判断 */
                s[t] = s[t] % 2;
                break;
            case 8:/* 次栈顶项与栈顶项是否相等 */
                t = t - 1;
                s[t] = (s[t] == s[t + 1]);
                break;
            case 9:/* 次栈顶项与栈顶项是否不等 */
                t = t - 1;
                s[t] = (s[t] != s[t + 1]);
                break;
            case 10:/* 次栈顶项是否小于栈顶项 */
                t = t - 1;
                s[t] = (s[t] < s[t + 1]);
                break;
            case 11:/* 次栈顶项是否大于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] >= s[t + 1]);
                break;
            case 12:/* 次栈顶项是否大于栈顶项 */
                t = t - 1;
                s[t] = (s[t] > s[t + 1]);
                break;
            case 13: /* 次栈顶项是否小于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] <= s[t + 1]);
                break;
            case 14:/* 栈顶值输出 */
                printf("%d", s[t]);
                fprintf(fresult, "%d", s[t]);
                t = t - 1;
                break;
            case 15:/* 输出换行符 */
                printf("\n");
                fprintf(fresult,"\n");
                break;
            case 16:/* 读入一个数置于栈顶 */
                t = t + 1;
                printf("input a number: ");
                fprintf(fresult, "input a number: ");
                scanf("%d", &(s[t]));
                getchar();
                fprintf(fresult, "%d\n", s[t]);           
                break;
            case 17:/* 读入一个字符置于栈顶 */
                {
                    char ch;
                    t = t + 1;
                    printf("input a character: ");
                    fprintf(fresult, "input a character: ");
                    scanf("%c", &ch);
                    getchar();
                    s[t] = ch;
                    fprintf(fresult, "%c\n", s[t]);           
                    break;
                }
                
            case 18:/* 次栈顶项求余栈顶项 */ 
                t = t - 1;
                s[t] = s[t] % s[t + 1];
                break;
            case 19:/* 次栈顶项异或栈顶项 */
                t = t - 1;
                s[t] = s[t] ^ s[t + 1];
                break;
            case 20:/* 栈顶的值取not */
                s[t] = !s[t];
                break;
            case 21:/* 次栈顶项and栈顶项 */
                t = t - 1;
                s[t] = s[t] && s[t + 1];
                break;
            case 22:/* 次栈顶项or栈顶项 */
                t = t - 1;
                s[t] = s[t] || s[t + 1];
                break;
            case 23:/* 栈顶字符输出 */
                printf("%c", s[t]);
                fprintf(fresult, "%c", s[t]);
                t = t - 1;
                break;
            }
            printstack(t, p, s);
            break;	
        case lod: /* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
            t = t + 1;
            s[t] = s[base(i.l, s, b) + i.a];
            printstack(t, p, s);            
            break;
        case sto: /* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
            s[base(i.l, s, b) + i.a] = s[t];
            t = t - 1;
            printstack(t, p, s);
            break;
        case cal: /* 调用子过程 */
            s[t + 1] = base(i.l, s, b); /* 将父过程基地址入栈，即建立静态链 */
            s[t + 2] = b; /* 将本过程基地址入栈，即建立动态链 */
            s[t + 3] = p; /* 将当前指令指针入栈，即保存返回地址 */
            b = t + 1;  /* 改变基地址指针值为新过程的基地址 */
            p = i.a;  /* 跳转 */
            printstack(t, p, s);
            break;
        case ini: /* 在数据栈中为被调用的过程开辟a个单元的数据区 */
            t = t + i.a;
            printstack(t, p, s);
            break;
        case jmp: /* 直接跳转 */
            p = i.a;
            printstack(t, p, s);
            break;
        case jpc: /* 如果栈顶等于0条件跳转 */
            if (s[t] == 0)
                p = i.a;
            t = t - 1;
            printstack(t, p, s);
            break;
        case jpe: /* 如果栈顶等于1条件跳转 */
            if (s[t]) 
                p = i.a;
            t = t - 1;
            printstack(t, p, s);
            break;
        case ext:
            p = 0;
            printstack(t, p, s);
            break;
        case blo: //不改变p
            s[t + 1] = base(i.l, s, b);
            s[t + 2] = b;
            b = t + 1;
            printstack(t, p, s);
            break;
        case fre: //不改变p
            t = b - 1;
            b = s[t + 2];
            printstack(t, p, s);
            break;
        }
    } while (p != 0);
    printf("End CX interpret\n");
    fprintf(fresult, "End CX interpret\n");
}

/* 通过过程基址求上ｌ层过程的基址 */
int base(int l, int s[], int b) {
    int b1 = b;
    while (l > 0) {
        b1 = s[b1];
        l = l - 1;
    }
    return b1;
}

int main(int argc, char *argv[]) {
    int i;
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-c") == 0) {  /* 是否输出虚拟机代码 */
                listswitch = true;
            } else if (strcmp(argv[i], "-t") == 0) {  /* 是否输出符号表 */
                tableswitch = true;
            } else if (strcmp(argv[i], "-s") == 0) {  /* 是否输出栈信息 */
                stackswitch = true;
            } 
        }
    }
    if ((fin = fopen(argv[argc - 1], "r")) == NULL) {
        printf("Can't open the input file!\n");
        exit(1);
    }
    if ((foutput = fopen("foutput.txt", "w")) == NULL) {
        printf("Can't open the output file!\n");
        exit(1);
    }
    if ((ftable = fopen("ftable.txt", "w")) == NULL) {
        printf("Can't open ftable.txt file!\n");
        exit(1);
    }

    redirectInput(fin);
    init();
    yyparse();

    if (err == 0) {
        printf("\n===Parsing success!===\n\n");
        fprintf(foutput, "\n===Parsing success!===\n");
        if ((fcode = fopen("fcode.txt", "w")) == NULL) {
            printf("Can't open fcode.txt file!\n");
            exit(1);
        }
        if ((fresult = fopen("fresult.txt", "w")) == NULL) {
            printf("Can't open fresult.txt file!\n");
            exit(1);
        }
        if ((fstack = fopen("fstack.txt", "w")) == NULL) {
            printf("Can't open fresult.txt file!\n");
            exit(1);
        }

        listall();  /* 输出所有代码 */
        fclose(fcode);

        interpret();  /* 调用解释执行程序 */
        fclose(fresult);
        fclose(fstack);
    } else {
        printf("%d errors in CX program\n", err);
        fprintf(foutput, "%d errors in CX program\n", err);
    }

    fclose(ftable);
    fclose(foutput);
    fclose(fin);
    return 0;
}

