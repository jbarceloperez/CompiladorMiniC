/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "minic.y"

#include <stdio.h>
#include "listaSimbolos.h"
#include "listaCodigo.h"
#include <string.h>

Lista tablaSimb;
int contCadenas=0;
Tipo tipo;
int perteneceTablaS(char *lexema);
void anadeEntrada(char *lexema, Tipo tipo);
int esConstante(char *lexema);
void imprimirTablaS();
ListaC imprimirListaC(ListaC declarations, ListaC statements);

char* buscarReg();
ListaC crearLista(char* arg1, char* op);
ListaC crearLista2(ListaC lista, ListaC arg2, char* op);
ListaC crearLista3(ListaC lista, char* var, char* op);
ListaC crearListaNeg(ListaC lista, char* op);
ListaC listaIf(ListaC cond, ListaC st);
ListaC if_else(ListaC exp, ListaC stat1, ListaC stat2);
ListaC while_(ListaC exp, ListaC stat);
ListaC do_while(ListaC stat, ListaC exp);
ListaC listaPrintItem(int cadena);
ListaC listaPrintExpresion(ListaC arg);
ListaC concatena(ListaC l1, ListaC l2);
ListaC listaRead(char* cadena);
void debugLista(ListaC lista);
void liberarReg(char* registro);
char *obtenerEtiqueta();

int registros[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int tag_counter = 0;

void yyerror();
extern int yylex();
extern int yylineno;

#line 110 "minic.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_MINIC_TAB_H_INCLUDED
# define YY_YY_MINIC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VOID = 258,
    VAR = 259,
    CONST = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    PRINT = 264,
    READ = 265,
    SEMICOLON = 266,
    COMA = 267,
    IGUAL = 268,
    APAR = 269,
    CPAR = 270,
    ACOR = 271,
    CCOR = 272,
    DO = 273,
    CADENA = 274,
    ID = 275,
    NUM = 276,
    MAS = 277,
    MENOS = 278,
    POR = 279,
    DIV = 280,
    UMENOS = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 42 "minic.y"

char *cadena;
ListaC codigo;

#line 194 "minic.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MINIC_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   107

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  36
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  81

#define YYUNDEFTOK  2
#define YYMAXUTOK   281


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    58,    58,    58,    61,    61,    62,    62,    63,    66,
      67,    70,    71,    74,    75,    78,    79,    80,    81,    82,
      83,    84,    85,    88,    89,    92,    93,    96,    97,   100,
     101,   102,   103,   104,   105,   106,   107
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VOID", "VAR", "CONST", "IF", "ELSE",
  "WHILE", "PRINT", "READ", "SEMICOLON", "COMA", "IGUAL", "APAR", "CPAR",
  "ACOR", "CCOR", "DO", "CADENA", "ID", "NUM", "MAS", "MENOS", "POR",
  "DIV", "UMENOS", "$accept", "program", "$@1", "declarations", "$@2",
  "$@3", "identifier_list", "asig", "statement_list", "statement",
  "print_list", "print_item", "read_list", "expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281
};
# endif

#define YYPACT_NINF (-28)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -28,     6,    14,   -28,    10,    -5,    19,    20,   -28,     0,
     -28,   -28,     2,    18,    18,    28,    36,    68,    38,   -28,
     -28,    31,    70,   -28,    77,    57,   -28,    61,    72,    72,
      72,   -28,   -28,   -28,    72,    73,   -28,    74,   -28,    89,
      15,    62,    72,    72,   -28,    18,   -28,    30,    41,    52,
     -28,   -28,    68,    72,    72,    72,    72,   -28,    82,   -28,
      80,    37,    74,   -28,    31,    31,   -28,   -28,   -11,   -11,
     -28,   -28,   -28,    72,   -28,    96,   -28,    56,    31,   -28,
     -28
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     0,     8,    14,
       4,     6,     0,     0,     0,     0,     0,     0,     0,    14,
       3,     0,     0,    13,    11,     0,     9,     0,     0,     0,
       0,    26,    35,    36,     0,     0,    23,    25,    27,     0,
       0,     0,     0,     0,     5,     0,     7,     0,     0,     0,
      33,    21,     0,     0,     0,     0,     0,    22,     0,    16,
       0,     0,    12,    10,     0,     0,    34,    24,    29,    30,
      31,    32,    28,     0,    15,    18,    19,     0,     0,    20,
      17
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -28,   -28,   -28,   -28,   -28,   -28,    90,    60,    87,   -21,
     -28,    55,   -28,   -27
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     9,    13,    14,    25,    26,    12,    23,
      35,    36,    39,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      41,    47,    48,    49,    10,    11,     3,    50,    15,     6,
      16,    17,    18,    55,    56,    61,    62,     4,    19,    20,
      21,    15,    22,    16,    17,    18,    68,    69,    70,    71,
       5,    19,    59,    21,     7,    22,     8,    15,    24,    16,
      17,    18,    28,    75,    76,    64,    77,    19,    74,    21,
      29,    22,    53,    54,    55,    56,    65,    80,    38,    53,
      54,    55,    56,    53,    54,    55,    56,    66,    44,    45,
      60,    79,    46,    45,    53,    54,    55,    56,    53,    54,
      55,    56,    30,    42,    51,    52,    30,    31,    32,    33,
      43,    34,    32,    33,    73,    34,    53,    54,    55,    56,
      57,    58,    72,    78,    27,    63,    40,    67
};

static const yytype_int8 yycheck[] =
{
      21,    28,    29,    30,     4,     5,     0,    34,     6,    14,
       8,     9,    10,    24,    25,    42,    43,     3,    16,    17,
      18,     6,    20,     8,     9,    10,    53,    54,    55,    56,
      20,    16,    17,    18,    15,    20,    16,     6,    20,     8,
       9,    10,    14,    64,    65,    15,    73,    16,    11,    18,
      14,    20,    22,    23,    24,    25,    15,    78,    20,    22,
      23,    24,    25,    22,    23,    24,    25,    15,    11,    12,
       8,    15,    11,    12,    22,    23,    24,    25,    22,    23,
      24,    25,    14,    13,    11,    12,    14,    19,    20,    21,
      13,    23,    20,    21,    14,    23,    22,    23,    24,    25,
      11,    12,    20,     7,    14,    45,    19,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    29,     0,     3,    20,    14,    15,    16,    30,
       4,     5,    35,    31,    32,     6,     8,     9,    10,    16,
      17,    18,    20,    36,    20,    33,    34,    33,    14,    14,
      14,    19,    20,    21,    23,    37,    38,    40,    20,    39,
      35,    36,    13,    13,    11,    12,    11,    40,    40,    40,
      40,    11,    12,    22,    23,    24,    25,    11,    12,    17,
       8,    40,    40,    34,    15,    15,    15,    38,    40,    40,
      40,    40,    20,    14,    11,    36,    36,    40,     7,    15,
      36
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    29,    28,    31,    30,    32,    30,    30,    33,
      33,    34,    34,    35,    35,    36,    36,    36,    36,    36,
      36,    36,    36,    37,    37,    38,    38,    39,    39,    40,
      40,    40,    40,    40,    40,    40,    40
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     0,     5,     0,     5,     0,     1,
       3,     1,     3,     2,     0,     4,     3,     7,     5,     5,
       6,     3,     3,     1,     3,     1,     1,     1,     3,     3,
       3,     3,     3,     2,     3,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 58 "minic.y"
          {tablaSimb=creaLS();}
#line 1420 "minic.tab.c"
    break;

  case 3:
#line 58 "minic.y"
                                                                                        {imprimirTablaS(); liberaLS(tablaSimb); imprimirListaC((yyvsp[-2].codigo), (yyvsp[-1].codigo));}
#line 1426 "minic.tab.c"
    break;

  case 4:
#line 61 "minic.y"
                                {tipo=VARIABLE;}
#line 1432 "minic.tab.c"
    break;

  case 5:
#line 61 "minic.y"
                                                                                                {(yyval.codigo)=concatena((yyvsp[-4].codigo), (yyvsp[-1].codigo));}
#line 1438 "minic.tab.c"
    break;

  case 6:
#line 62 "minic.y"
                                  {tipo=CONSTANTE;}
#line 1444 "minic.tab.c"
    break;

  case 7:
#line 62 "minic.y"
                                                                                        {(yyval.codigo)=concatena((yyvsp[-4].codigo), (yyvsp[-1].codigo));}
#line 1450 "minic.tab.c"
    break;

  case 8:
#line 63 "minic.y"
                                                {(yyval.codigo)=creaLC();}
#line 1456 "minic.tab.c"
    break;

  case 9:
#line 66 "minic.y"
                                                                        {(yyval.codigo) = (yyvsp[0].codigo);}
#line 1462 "minic.tab.c"
    break;

  case 10:
#line 67 "minic.y"
                                                        {(yyval.codigo) = concatena((yyvsp[-2].codigo), (yyvsp[0].codigo));}
#line 1468 "minic.tab.c"
    break;

  case 11:
#line 70 "minic.y"
                                                        {if (!perteneceTablaS((yyvsp[0].cadena))) anadeEntrada((yyvsp[0].cadena),tipo); else printf("Error en línea %d: variable %s ya declarada\n",yylineno,(yyvsp[0].cadena)); (yyval.codigo) = creaLC();}
#line 1474 "minic.tab.c"
    break;

  case 12:
#line 71 "minic.y"
                                                {if (!perteneceTablaS((yyvsp[-2].cadena))) anadeEntrada((yyvsp[-2].cadena),tipo); else printf("Error en línea %d: variable %s ya declarada\n",yylineno,(yyvsp[-2].cadena)); (yyval.codigo) = crearLista3((yyvsp[0].codigo), (yyvsp[-2].cadena), "sw");}
#line 1480 "minic.tab.c"
    break;

  case 13:
#line 74 "minic.y"
                                                        {(yyval.codigo) = concatena((yyvsp[-1].codigo), (yyvsp[0].codigo));}
#line 1486 "minic.tab.c"
    break;

  case 14:
#line 75 "minic.y"
                                                                        {(yyval.codigo) = creaLC();}
#line 1492 "minic.tab.c"
    break;

  case 15:
#line 78 "minic.y"
                                                                        {if (!perteneceTablaS((yyvsp[-3].cadena))) printf("Error en línea %d: variable %s no declarada\n",yylineno,(yyvsp[-3].cadena)); else if (esConstante((yyvsp[-3].cadena))) printf("Error en línea %d: asignación a constante %s\n",yylineno,(yyvsp[-3].cadena)); (yyval.codigo) = crearLista3((yyvsp[-1].codigo), (yyvsp[-3].cadena), "sw");}
#line 1498 "minic.tab.c"
    break;

  case 16:
#line 79 "minic.y"
                                                                        {(yyval.codigo) = (yyvsp[-1].codigo);}
#line 1504 "minic.tab.c"
    break;

  case 17:
#line 80 "minic.y"
                                                                {(yyval.codigo) = if_else((yyvsp[-4].codigo), (yyvsp[-2].codigo), (yyvsp[0].codigo));}
#line 1510 "minic.tab.c"
    break;

  case 18:
#line 81 "minic.y"
                                                                {(yyval.codigo) = listaIf((yyvsp[-2].codigo), (yyvsp[0].codigo));}
#line 1516 "minic.tab.c"
    break;

  case 19:
#line 82 "minic.y"
                                                                {(yyval.codigo) = while_((yyvsp[-2].codigo),(yyvsp[0].codigo));}
#line 1522 "minic.tab.c"
    break;

  case 20:
#line 83 "minic.y"
                                                                {(yyval.codigo) = do_while((yyvsp[-4].codigo),(yyvsp[-1].codigo));}
#line 1528 "minic.tab.c"
    break;

  case 21:
#line 84 "minic.y"
                                                                {(yyval.codigo) = (yyvsp[-1].codigo);}
#line 1534 "minic.tab.c"
    break;

  case 22:
#line 85 "minic.y"
                                                                {(yyval.codigo) = (yyvsp[-1].codigo);}
#line 1540 "minic.tab.c"
    break;

  case 23:
#line 88 "minic.y"
                                                {(yyval.codigo) = (yyvsp[0].codigo);}
#line 1546 "minic.tab.c"
    break;

  case 24:
#line 89 "minic.y"
                                                {(yyval.codigo) = concatena((yyvsp[-2].codigo), (yyvsp[0].codigo));}
#line 1552 "minic.tab.c"
    break;

  case 25:
#line 92 "minic.y"
                                                {(yyval.codigo) = listaPrintExpresion((yyvsp[0].codigo));}
#line 1558 "minic.tab.c"
    break;

  case 26:
#line 93 "minic.y"
                                                        {anadeEntrada((yyvsp[0].cadena),STRING); (yyval.codigo) = listaPrintItem(contCadenas); contCadenas++;}
#line 1564 "minic.tab.c"
    break;

  case 27:
#line 96 "minic.y"
                                                        {if (!perteneceTablaS((yyvsp[0].cadena))) printf("Error en línea %d: variable %s no declarada\n",yylineno,(yyvsp[0].cadena)); else if (esConstante((yyvsp[0].cadena))) printf("Error en línea %d: asignación a constante %s\n",yylineno,(yyvsp[0].cadena)); (yyval.codigo) = listaRead((yyvsp[0].cadena));}
#line 1570 "minic.tab.c"
    break;

  case 28:
#line 97 "minic.y"
                                                {if (!perteneceTablaS((yyvsp[0].cadena))) printf("Error en línea %d: variable %s no declarada\n",yylineno,(yyvsp[0].cadena)); else if (esConstante((yyvsp[0].cadena))) printf("Error en línea %d: asignación a constante %s\n",yylineno,(yyvsp[0].cadena)); (yyval.codigo) = concatena((yyvsp[-2].codigo), listaRead((yyvsp[0].cadena)));}
#line 1576 "minic.tab.c"
    break;

  case 29:
#line 100 "minic.y"
                                                  {(yyval.codigo) = crearLista2((yyvsp[-2].codigo), (yyvsp[0].codigo), "add");}
#line 1582 "minic.tab.c"
    break;

  case 30:
#line 101 "minic.y"
                                                  {(yyval.codigo) = crearLista2((yyvsp[-2].codigo), (yyvsp[0].codigo), "sub");}
#line 1588 "minic.tab.c"
    break;

  case 31:
#line 102 "minic.y"
                                                  {(yyval.codigo) = crearLista2((yyvsp[-2].codigo), (yyvsp[0].codigo), "mul");}
#line 1594 "minic.tab.c"
    break;

  case 32:
#line 103 "minic.y"
                                                  {(yyval.codigo) = crearLista2((yyvsp[-2].codigo), (yyvsp[0].codigo), "div");}
#line 1600 "minic.tab.c"
    break;

  case 33:
#line 104 "minic.y"
                                                  {(yyval.codigo) = crearListaNeg((yyvsp[0].codigo), "neg");}
#line 1606 "minic.tab.c"
    break;

  case 34:
#line 105 "minic.y"
                                                            {(yyval.codigo) = (yyvsp[-1].codigo);}
#line 1612 "minic.tab.c"
    break;

  case 35:
#line 106 "minic.y"
                                                                            {if (!perteneceTablaS((yyvsp[0].cadena))) printf("Error en línea %d: variable %s no declarada\n",yylineno,(yyvsp[0].cadena));(yyval.codigo) = crearLista((yyvsp[0].cadena), "lw");}
#line 1618 "minic.tab.c"
    break;

  case 36:
#line 107 "minic.y"
                                                                            {(yyval.codigo) = crearLista((yyvsp[0].cadena), "li");}
#line 1624 "minic.tab.c"
    break;


#line 1628 "minic.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 111 "minic.y"


void yyerror()
{
  	printf("Se ha producido un error en esta expresion\n");
}

ListaC crearLista(char* arg1, char* op){	// esto vale para id y num, solo cambia el tipo de op (li o lw)
	ListaC lista = creaLC();
	char* registro = buscarReg();
	PosicionListaC inicio = inicioLC(lista);
	//Creamos la operación
	Operacion operacion;
	operacion.op = op;
	operacion.res = registro;
	if (op=="lw"){    // si es un id, se le coloca el '_' delante del nombre
		char arg[16];
		sprintf(arg, "_%s", arg1);
		operacion.arg1 = strdup(arg);
	}
	else {operacion.arg1 = arg1;}
	operacion.arg2 = NULL;
	//Insertamos la operación en la lista
	insertaLC(lista, inicio, operacion);
	guardaResLC(lista, registro);
	return lista;
}

ListaC crearLista2(ListaC lista, ListaC arg2, char* op) {
	//recuperamos los registros de las expresiones para la operacion
	char* regArg1 = recuperaResLC(lista);
	char* regArg2 = recuperaResLC(arg2);
	//concatena listas
	concatenaLC(lista, arg2);
	liberaLC(arg2);
	//buscamos registros libres
	char* registro = buscarReg();
	PosicionListaC final = finalLC(lista);
	//crea la operacion
	Operacion operacion;
	operacion.op = op;
	operacion.res = registro;
	operacion.arg1 = regArg1;
	operacion.arg2 = regArg2;
	//liberamos registros
	liberarReg(regArg1);
	liberarReg(regArg2);
	//insertar la op al final de la lista
	insertaLC(lista, final, operacion);
	guardaResLC(lista, registro);
	return lista;
}

ListaC crearLista3(ListaC lista, char* var, char* op) {
	//recuperamos los registros de las expresiones para la operacion
	char* regArg = recuperaResLC(lista);
	PosicionListaC final = finalLC(lista);
	char arg[16];
	sprintf(arg, "_%s", var);
	//crear op
	Operacion operacion;
	operacion.op = op;
	operacion.res = regArg;
	operacion.arg1 = strdup(arg);
	operacion.arg2 = NULL;  
	//liberamos registros
	liberarReg(regArg);
	// insertar op
	insertaLC(lista, final, operacion);
	return lista;    
}

ListaC crearListaNeg(ListaC lista, char* op){
	char* regArg = recuperaResLC(lista);
	PosicionListaC final = finalLC(lista);
	Operacion operacion;
	operacion.op = op;
	operacion.res = buscarReg();
	operacion.arg1 = regArg;
	operacion.arg2 = NULL;  
	//liberamos registros
	liberarReg(regArg);
	insertaLC(lista, final, operacion);
	guardaResLC(lista, regArg);
	return lista;
}

ListaC listaIf(ListaC cond, ListaC st) {
		//recuperamos los registros de las expresiones
	char* regCond = recuperaResLC(cond);
	char* regSt = recuperaResLC(st);
		//creamos la etiqueta del salto
	char* tag = obtenerEtiqueta();
		//añade beqz
	PosicionListaC final = finalLC(cond);
	Operacion operacion;
	operacion.op = "beqz";
	operacion.res = regCond;
	operacion.arg1 = tag;
	operacion.arg2 = NULL;
	//liberamos registros *¿qué hacemos con el registro res de la lista cond?
	liberarReg(regCond);
		// insertar la op
	insertaLC(cond, final, operacion);
		//concatena listas
	concatenaLC(cond, st);
	liberaLC(st);
	guardaResLC(cond, regSt);
		//insertar etiqueta
	final = finalLC(cond);
	char etq[10];
	sprintf(etq, "%s:", tag);
	Operacion etiqueta;
	etiqueta.op = strdup(etq);
	etiqueta.res = NULL;
	etiqueta.arg1 = NULL;
	etiqueta.arg2 = NULL;
	insertaLC(cond, final, etiqueta);
	return cond;
}

ListaC if_else(ListaC exp, ListaC stat1, ListaC stat2) {	
	//Obtenemos el registro reg de exp para utilizarlo en el beqz
	char* reg1 = recuperaResLC(exp);
	//Creamos la operación beqz y la insertamos en la posición final
	char* et1 = obtenerEtiqueta();
	Operacion beqz;
	beqz.op = "beqz";
	beqz.res = reg1;
	beqz.arg1 = et1;
	beqz.arg2 = NULL;
	insertaLC(exp, finalLC(exp), beqz);
	//Concatenamos exp y stat1 (y la liberamos)
	concatenaLC(exp, stat1);
	liberaLC(stat1);
	//Creamos la operación b y la insertamos en la posición final
	char* et2 = obtenerEtiqueta();
	Operacion b;
	b.op = "b";
	b.res = strdup(et2);
	b.arg1 = NULL;
	b.arg2 = NULL;
	insertaLC(exp, finalLC(exp), b);
	//Insertamos et1
	char etq1[10];
	sprintf(etq1, "%s:", et1);
	Operacion etiq1;
	etiq1.op = strdup(etq1);
	etiq1.res = NULL;
	etiq1.arg1 = NULL;
	etiq1.arg2 = NULL;
	insertaLC(exp, finalLC(exp), etiq1);
	//Concatenamos exp y stat2 (y la liberamos)
	concatenaLC(exp, stat2);
	liberaLC(stat2);
	//Insertamos et2
	char etq2[10];
	sprintf(etq2, "%s:", et2);
	Operacion etiq2;
	etiq2.op = strdup(etq2);
	etiq2.res = NULL;
	etiq2.arg1 = NULL;
	etiq2.arg2 = NULL;
	insertaLC(exp, finalLC(exp), etiq2);
	//Liberamos registros
	liberarReg(reg1);
	//Devolvemos la lista
	return exp;
}

ListaC do_while(ListaC stat, ListaC exp){
	//Insertamos et1 al principio de stat
	char* et1 = obtenerEtiqueta();
	char etq1[10];
	sprintf(etq1, "%s:", et1);
	Operacion etiq1;
	etiq1.op = strdup(etq1);
	etiq1.res = NULL;
	etiq1.arg1 = NULL;
	etiq1.arg2 = NULL;
	insertaLC(stat, inicioLC(stat), etiq1);
	//Recuperamos reg de exp
	char* reg = recuperaResLC(exp);
	//Concatenamos exp y stat (y liberamos stat)
	concatenaLC(stat, exp);
	liberaLC(exp);
	//Insertamos bnez al final de la lista
	Operacion bnez;
	bnez.op = "bnez";
	bnez.res = reg;
	bnez.arg1 = strdup(etq1);
	bnez.arg2 = NULL;
	insertaLC(exp, finalLC(stat), bnez);
	//Devolvemos la lista
	return stat;
}

ListaC while_(ListaC exp, ListaC stat){
	//Insertamos et1 al principio de exp
	char* et1 = obtenerEtiqueta();
	char etq1[10];
	sprintf(etq1, "%s:", et1);
	Operacion etiq1;
	etiq1.op = strdup(etq1);
	etiq1.res = NULL;
	etiq1.arg1 = NULL;
	etiq1.arg2 = NULL;
	insertaLC(exp, inicioLC(exp), etiq1);
	//Obtenemos el registro resultado de exp
	char* reg = recuperaResLC(exp);
	//Creamos la operación beqz y la insertamos en la posición final
	char* et2 = obtenerEtiqueta();
	Operacion beqz;
	beqz.op = "beqz";
	beqz.res = reg;
	beqz.arg1 = et2;
	beqz.arg2 = NULL;
	insertaLC(exp, finalLC(exp), beqz);
	//Liberamos el registro
	liberarReg(reg);
	//Concatenamos exp y stat (y liberamos stat)
	concatenaLC(exp, stat);
	liberaLC(stat);
	//Creamos la operación b y la insertamos en la posición final
	Operacion b;
	b.op = "b";
	b.res = et1;
	b.arg1 = NULL;
	b.arg2 = NULL;
	insertaLC(exp, finalLC(exp), b);
	//Insertamos et2 al final de exp
	char etq2[10];
	sprintf(etq2, "%s:", et2);
	Operacion etiq2;
	etiq2.op = strdup(etq2);
	etiq2.res = NULL;
	etiq2.arg1 = NULL;
	etiq2.arg2 = NULL;
	insertaLC(exp, finalLC(exp), etiq2);
	//Devolvemos la lista
	return exp;
}

ListaC listaPrintItem(int cadena) {
	ListaC lista = creaLC();
	char str[10];
	sprintf(str, "$str%d", cadena);
	// añadir el la $a0, $strX
	Operacion op_la;
	op_la.op = "la";
	op_la.res = "$a0";
	op_la.arg1 = strdup(str);
	op_la.arg2 = NULL;
	PosicionListaC final = finalLC(lista);
	insertaLC(lista, final, op_la);
	// añadir el li $v0, 4
	Operacion op_li;
	op_li.op = "li";
	op_li.res = "$v0";
	op_li.arg1 = "4";
	op_li.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, op_li);
	Operacion syscall;
	syscall.op = "syscall";
	syscall.res = NULL;
	syscall.arg1 = NULL;
	syscall.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, syscall);
	return lista; 
}

ListaC listaPrintExpresion(ListaC lista) {
	char* regLista = recuperaResLC(lista);
	//move $a0, $tX
	Operacion op_move;
	op_move.op = "move";
	op_move.res = "$a0";
	op_move.arg1 = regLista;
	op_move.arg2 = NULL;
	// se libera el registro
	liberarReg(regLista);
	PosicionListaC final = finalLC(lista);
	insertaLC(lista, final, op_move);
	// li $v0, 1
	Operacion op_li;
	op_li.op = "li";
	op_li.res = "$v0";
	op_li.arg1 = "1";
	op_li.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, op_li);
	Operacion syscall;
	syscall.op = "syscall";
	syscall.res = NULL;
	syscall.arg1 = NULL;
	syscall.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, syscall);
	return lista;
}

ListaC concatena(ListaC l1, ListaC l2){
	// debugLista(l1);
	// debugLista(l2);
	concatenaLC(l1, l2);
	liberaLC(l2);
	return l1;
}

ListaC listaRead(char* cadena){
	ListaC lista = creaLC();
	// li $v0, 5
	Operacion op_li;
	op_li.op = "li";
	op_li.res = "$v0";
	op_li.arg1 = "5";
	op_li.arg2 = NULL;
	PosicionListaC final = finalLC(lista);
	insertaLC(lista, final, op_li);
	Operacion syscall;
	syscall.op = "syscall";
	syscall.res = NULL;
	syscall.arg1 = NULL;
	syscall.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, syscall);
	// sw $v0, _X
	char arg[16];
	sprintf(arg, "_%s", cadena);
	Operacion op_sw;
	op_sw.op = "sw";
	op_sw.res = "$v0";
	op_sw.arg1 = strdup(arg);
	op_sw.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, op_sw);
	return lista;
}

void debugLista(ListaC lista){
	PosicionListaC aux = inicioLC(lista);
	int n = longitudLC(lista);
	printf("Info de lista:\n Longitud:%d\n",n);
	if (inicioLC(lista)==finalLC(lista)) printf("algo va mal...\n");
	int cont=0;
	while(aux!=finalLC(lista)){
		printf("[%d]\t%s", cont, recuperaLC(lista, aux).op);
		if (recuperaLC(lista, aux).res!=NULL) printf("\t%s",recuperaLC(lista, aux).res);
		if (recuperaLC(lista, aux).arg1!=NULL) printf(",%s",recuperaLC(lista, aux).arg1);
		if (recuperaLC(lista, aux).arg2!=NULL) printf(",%s\n",recuperaLC(lista, aux).arg2);
		else printf("\n");
		cont++; 
		aux = siguienteLC(lista, aux);
	}
	printf("Valor res de la lista: %s\n", recuperaResLC(lista));
}

char* buscarReg()
{
	int i = 0;
	while (registros[i] != 0) i++;

	registros[i] = 1;
	char registro[4];
	sprintf(registro, "$t%d", i);
	return strdup(registro);
}

//Método para liberar registro
void liberarReg(char* registro) {
  char r = registro[2];
  int reg = r - '0';
  registros[reg] = 0;
}


//Métodos para traducir sentencias
char *obtenerEtiqueta() {
  char aux[32];
  sprintf(aux, "ET%d", tag_counter++);
  return strdup(aux);
}

int perteneceTablaS(char *lexema)
{
	PosicionLista posicion = buscaLS(tablaSimb, lexema);
	return posicion != finalLS(tablaSimb);
}

void anadeEntrada(char *lexema, Tipo tipo)
{
	PosicionLista final = finalLS(tablaSimb);
	Simbolo simbolo;
	simbolo.nombre = lexema;
	simbolo.tipo = tipo;
	if (tipo == STRING) simbolo.valor = contCadenas;
	else simbolo.valor = 0;
	insertaLS(tablaSimb, final, simbolo);
}

int esConstante(char *lexema)
{
	PosicionLista posicion = buscaLS(tablaSimb, lexema);
	Simbolo simbolo = recuperaLS(tablaSimb, posicion);
	return simbolo.tipo == CONSTANTE;
}

void imprimirTablaS()
{
	PosicionLista posicion = inicioLS(tablaSimb);
	printf("############################\n");
	printf(".data\n\n");
	printf("# STRINGS ##################\n");
	while (posicion != finalLS(tablaSimb))
	{
		Simbolo simbolo = recuperaLS(tablaSimb, posicion);
		if (simbolo.tipo == STRING) printf("$str%d:\t.asciiz %s\n",simbolo.valor,simbolo.nombre);
		posicion = siguienteLS(tablaSimb, posicion);
	}
	printf("\n# IDENTIFIERS ##############\n");
	posicion = inicioLS(tablaSimb);
	while (posicion != finalLS(tablaSimb))
	{
		Simbolo simbolo = recuperaLS(tablaSimb, posicion);
		if (simbolo.tipo != STRING) printf("_%s:\t.word %d\n",simbolo.nombre,simbolo.valor);
		posicion = siguienteLS(tablaSimb, posicion);
	}
}


ListaC imprimirListaC(ListaC declarations, ListaC statements){
	printf("\n############################\n# Seccion de codigo\n.text\n.globl main\n\nmain:\n");
	//recorrer declarations
	PosicionListaC aux = inicioLC(declarations);
	int n = longitudLC(declarations);
	printf("##LongDeclarations=%d\n",n);
	// if (inicioLC(lista)==finalLC(lista)) printf("algo va mal...\n");
	int cont=0;
	while(aux!=finalLC(declarations)){
		// printf("[%d]\t", cont);		// DEBUG
		printf("%s\t%s,%s", recuperaLC(declarations, aux).op, recuperaLC(declarations, aux).res, recuperaLC(declarations, aux).arg1);
		if (recuperaLC(declarations, aux).arg2!=NULL) printf(",%s\n",recuperaLC(declarations, aux).arg2);
		else printf("\n");
		cont++; 
		aux = siguienteLC(declarations, aux);
	}
	//recorrer statements
	aux = inicioLC(statements);
	n = longitudLC(statements);
	printf("##LongStatements=%d\n",n);
	// if (inicioLC(lista)==finalLC(lista)) printf("algo va mal...\n");
	while(aux!=finalLC(statements)){
		// printf("[%d]\t", cont);		// DEBUG
		printf("%s", recuperaLC(statements, aux).op);
		if (recuperaLC(statements, aux).res!=NULL) printf("\t%s",recuperaLC(statements, aux).res);
		if (recuperaLC(statements, aux).arg1!=NULL) printf(",%s",recuperaLC(statements, aux).arg1);
		if (recuperaLC(statements, aux).arg2!=NULL) printf(",%s\n",recuperaLC(statements, aux).arg2);
		else printf("\n");
		cont++; 
		aux = siguienteLC(statements, aux);
	}
	printf("li\t$v0, 10\nsyscall\n############################\n# Fin de la ejecución ######\n############################\n\n##Regs:");
	int i;for (i=0;i<10;i++) printf("[%d]", registros[i]); printf("\n");	//debug
}
