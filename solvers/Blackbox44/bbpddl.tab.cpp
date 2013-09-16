/*  A Bison parser, made from bbpddl.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	DEFINE	257
#define	DOMAIN	258
#define	REQUIREMENTS	259
#define	CONSTANTS	260
#define	TYPES	261
#define	PREDICATES	262
#define	PROBLEM	263
#define	OBJECTS	264
#define	INIT	265
#define	LENGTH	266
#define	PARALLEL	267
#define	SERIAL	268
#define	CONTROL	269
#define	DEFPREDICATE	270
#define	EXCLUDE	271
#define	WFFCTRL	272
#define	SCOPE	273
#define	BODY	274
#define	ACTION	275
#define	PARAMETERS	276
#define	PRECONDITION	277
#define	EFFECT	278
#define	AND	279
#define	FORALL	280
#define	EXISTS	281
#define	NOEXISTS	282
#define	NEXT	283
#define	EQ	284
#define	NOT	285
#define	GOAL	286
#define	EITHER	287
#define	FLUENT	288
#define	ID	289
#define	VAR	290

#line 1 "bbpddl.y"

  /******************************************************/
  /* Strict Strips PDDL parser for BlackBox 		*/
  /******************************************************/

#include <string.h>
#include "utilities.h"
#include "control.h"


int yylex (void);
int yyerror(char * s);

extern char* yytext;
extern int yylineno;
extern int max_time;
extern char *domain_name, *problem_name, *control_name;
extern op_list ops;
extern defpred_list dps;
extern fact_list initial_facts, the_goals, constants, predicates, the_types;
extern control_list controls;
extern wffctrl_list wffctrls;
extern int input_type;
extern token_list objects;

op_list make_action (char *, param_list, precond_list, effect_list);
defpred_list make_defpred (char *, param_list, fact_list);
control_list make_control (char *, fact_list);
wffctrl_list make_wffctrl (char *name, fact_list, fact_list, fact_list);
void check_requirement_flag (token_list flags);
void type_object (fact_list, token_list, int);
void add_object (fact_list object);
void add_action (op_list op);
void add_defpred (defpred_list);
void add_control (control_list);
void add_wffctrl (wffctrl_list);
int comp_precond_and_effect (wffctrl_list);


#line 41 "bbpddl.y"
typedef union {
  char *str;
  op_list oplist;
  defpred_list defpredlist;
  control_list ctrllist;
  wffctrl_list wffctrllist;
  fact_list flist;
  token_list tlist;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		213
#define	YYFLAG		-32768
#define	YYNTBASE	41

#define YYTRANSLATE(x) ((unsigned)(x) <= 290 ? yytranslate[x] : 82)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
    38,     2,     2,     2,    40,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    39,     2,     2,
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
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     6,    15,    17,    20,    22,    28,    34,
    40,    42,    48,    62,    64,    67,    69,    75,    81,    87,
    93,    95,    98,   104,   110,   124,   137,   139,   141,   143,
   146,   149,   152,   162,   167,   173,   178,   183,   187,   196,
   205,   209,   213,   216,   220,   223,   227,   230,   234,   236,
   239,   243,   245,   248,   252,   255,   257,   262,   264,   267,
   269,   272,   274,   277,   279,   282,   286,   291,   293,   298,
   302,   304,   306,   308,   315,   322,   329,   331,   334,   338,
   343,   348,   353,   356,   359,   363,   365,   367,   370,   373,
   375
};

static const short yyrhs[] = {    42,
     0,    46,     0,    51,     0,    37,     3,    37,     4,    81,
    38,    43,    38,     0,    44,     0,    43,    44,     0,    45,
     0,    37,    39,     6,    63,    38,     0,    37,    39,     7,
    63,    38,     0,    37,    39,     8,    70,    38,     0,    55,
     0,    37,    39,     5,    78,    38,     0,    37,     3,    37,
     9,    81,    38,    37,    39,     4,    81,    38,    47,    38,
     0,    48,     0,    47,    48,     0,    45,     0,    37,    39,
    10,    63,    38,     0,    37,    39,    11,    72,    38,     0,
    37,    39,    32,    72,    38,     0,    37,    39,    12,    49,
    38,     0,    50,     0,    50,    49,     0,    37,    39,    14,
    81,    38,     0,    37,    39,    13,    81,    38,     0,    37,
     3,    37,    15,    81,    38,    37,    39,     4,    81,    38,
    52,    38,     0,    37,     3,    37,    15,    81,    38,    37,
    39,     4,    81,    38,    38,     0,    56,     0,    57,     0,
    53,     0,    56,    52,     0,    57,    52,     0,    53,    52,
     0,    37,    39,    16,    81,    59,    39,    20,    72,    38,
     0,    37,    39,    21,    81,     0,    54,    59,    60,    61,
    38,     0,    54,    59,    61,    38,     0,    54,    60,    61,
    38,     0,    54,    61,    38,     0,    37,    39,    21,    81,
    39,    17,    72,    38,     0,    37,    39,    18,    81,    58,
    60,    61,    38,     0,    39,    19,    72,     0,    39,    22,
    62,     0,    39,    22,     0,    39,    23,    72,     0,    39,
    23,     0,    39,    24,    72,     0,    37,    38,     0,    37,
    64,    38,     0,    68,     0,    68,    65,     0,    68,    65,
    63,     0,    69,     0,    69,    65,     0,    69,    65,    64,
     0,    40,    66,     0,    81,     0,    37,    33,    67,    38,
     0,    81,     0,    81,    67,     0,    81,     0,    81,    68,
     0,    80,     0,    80,    69,     0,    71,     0,    71,    70,
     0,    37,    81,    38,     0,    37,    81,    64,    38,     0,
    76,     0,    37,    25,    76,    38,     0,    37,    25,    38,
     0,    73,     0,    75,     0,    74,     0,    37,    27,    62,
    77,    72,    38,     0,    37,    28,    62,    77,    72,    38,
     0,    37,    26,    62,    77,    72,    38,     0,    77,     0,
    77,    76,     0,    37,    79,    38,     0,    37,    31,    77,
    38,     0,    37,    29,    77,    38,     0,    37,    32,    77,
    38,     0,    37,    38,     0,    39,    81,     0,    39,    81,
    78,     0,    80,     0,    81,     0,    80,    79,     0,    81,
    79,     0,    36,     0,    35,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    65,    66,    67,    70,    73,    74,    77,    78,    79,    81,
    82,    84,    87,    94,    95,    97,    98,    99,   100,   101,
   103,   104,   106,   107,   111,   113,   115,   116,   117,   118,
   119,   120,   122,   126,   128,   131,   133,   135,   139,   143,
   148,   150,   151,   153,   154,   156,   159,   160,   162,   163,
   165,   171,   172,   174,   179,   181,   182,   185,   186,   190,
   191,   195,   196,   200,   201,   205,   206,   211,   212,   213,
   214,   215,   216,   219,   228,   237,   246,   247,   251,   252,
   256,   260,   264,   266,   267,   270,   271,   272,   274,   277,
   279
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","DEFINE",
"DOMAIN","REQUIREMENTS","CONSTANTS","TYPES","PREDICATES","PROBLEM","OBJECTS",
"INIT","LENGTH","PARALLEL","SERIAL","CONTROL","DEFPREDICATE","EXCLUDE","WFFCTRL",
"SCOPE","BODY","ACTION","PARAMETERS","PRECONDITION","EFFECT","AND","FORALL",
"EXISTS","NOEXISTS","NEXT","EQ","NOT","GOAL","EITHER","FLUENT","ID","VAR","'('",
"')'","':'","'-'","pddl","domain","domain_body","domain_structure","require_def",
"problem","problem_body","problem_structure","length_spec","length","control",
"control_body","defpred","actionhead","action","ctrl","wffctrl","scope","parameter",
"precondition","effect","parameters","typedlist","typedparamlist","type_def",
"type","types","idlist","paramlist","predlist","predicate","factlist","exists",
"noexists","forall","termlist","term","requires","tokenlist","variable","id", NULL
};
#endif

static const short yyr1[] = {     0,
    41,    41,    41,    42,    43,    43,    44,    44,    44,    44,
    44,    45,    46,    47,    47,    48,    48,    48,    48,    48,
    49,    49,    50,    50,    51,    51,    52,    52,    52,    52,
    52,    52,    53,    54,    55,    55,    55,    55,    56,    57,
    58,    59,    59,    60,    60,    61,    62,    62,    63,    63,
    63,    64,    64,    64,    65,    66,    66,    67,    67,    68,
    68,    69,    69,    70,    70,    71,    71,    72,    72,    72,
    72,    72,    72,    73,    74,    75,    76,    76,    77,    77,
    77,    77,    77,    78,    78,    79,    79,    79,    79,    80,
    81
};

static const short yyr2[] = {     0,
     1,     1,     1,     8,     1,     2,     1,     5,     5,     5,
     1,     5,    13,     1,     2,     1,     5,     5,     5,     5,
     1,     2,     5,     5,    13,    12,     1,     1,     1,     2,
     2,     2,     9,     4,     5,     4,     4,     3,     8,     8,
     3,     3,     2,     3,     2,     3,     2,     3,     1,     2,
     3,     1,     2,     3,     2,     1,     4,     1,     2,     1,
     2,     1,     2,     1,     2,     3,     4,     1,     4,     3,
     1,     1,     1,     6,     6,     6,     1,     2,     3,     4,
     4,     4,     2,     2,     3,     1,     1,     2,     2,     1,
     1
};

static const short yydefact[] = {     0,
     0,     1,     2,     3,     0,     0,     0,     0,     0,    91,
     0,     0,     0,     0,     0,     0,     0,     0,     5,     7,
     0,    11,     0,     0,     0,     4,     6,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    43,    45,
     0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
     0,     0,    49,    60,     0,     0,     0,    64,    34,     0,
    42,     0,    44,    71,    73,    72,    68,    77,    46,     0,
    36,    37,     0,     0,    84,    12,     8,     0,    50,    61,
     9,     0,    10,    65,    90,    47,     0,    52,    62,     0,
     0,     0,     0,     0,     0,     0,    83,     0,    86,    87,
     0,    78,    35,     0,     0,    85,     0,    55,    56,    51,
    66,     0,    48,    53,    63,    70,     0,     0,     0,     0,
     0,     0,     0,    79,    88,    89,     0,    16,     0,    14,
     0,    26,     0,    29,    27,    28,     0,    67,    54,    69,
     0,     0,     0,    81,    80,    82,     0,    13,    15,     0,
    25,    32,    30,    31,     0,    58,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    57,    59,    76,    74,
    75,     0,     0,     0,     0,    21,     0,     0,     0,     0,
    17,    18,     0,    20,    22,    19,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    41,     0,     0,    24,    23,     0,    40,    39,    33,
     0,     0,     0
};

static const short yydefgoto[] = {   211,
     2,    18,    19,    20,     3,   129,   130,   175,   176,     4,
   133,   134,    21,    22,   135,   136,   190,    29,    30,    31,
    61,    52,    87,    79,   108,   155,    53,    88,    57,    58,
    63,    64,    65,    66,    67,    68,    51,    98,    89,    54
};

static const short yypact[] = {   -22,
    21,-32768,-32768,-32768,    -9,    12,    -2,    -2,    -2,-32768,
    -1,     7,    53,    31,    69,    77,    11,    41,-32768,-32768,
    62,-32768,    76,    78,    51,-32768,-32768,    30,    79,    80,
    82,    85,   112,    83,    -2,    -2,    84,    -2,    86,    87,
    87,    72,    80,    88,   101,    90,-32768,    -2,    -2,    -2,
    93,    95,    94,    -2,    98,    -2,    99,    84,-32768,    48,
-32768,    38,-32768,-32768,-32768,-32768,-32768,   102,-32768,   100,
-32768,-32768,   103,   104,    83,-32768,-32768,    50,    -2,-32768,
-32768,    52,-32768,-32768,-32768,-32768,   105,    94,   108,    60,
    86,    86,    86,   102,   102,   102,-32768,   107,    64,    64,
    -6,-32768,-32768,   109,    65,-32768,   114,-32768,-32768,-32768,
-32768,   110,-32768,   108,-32768,-32768,   113,   102,   102,   102,
   115,   116,   117,-32768,-32768,-32768,    96,-32768,    67,-32768,
   111,-32768,   118,   123,   123,   123,    -2,-32768,-32768,-32768,
    87,    87,    87,-32768,-32768,-32768,     8,-32768,-32768,    59,
-32768,-32768,-32768,-32768,   124,    -2,   125,   127,   130,    -2,
    87,   132,    87,    -2,    -2,    -2,-32768,-32768,-32768,-32768,
-32768,   134,   135,   131,   136,   132,   137,   138,   139,   140,
-32768,-32768,    97,-32768,-32768,-32768,   154,   141,   121,   142,
   165,    -2,    -2,   163,    87,   129,    80,    87,   146,   149,
    87,-32768,   150,   151,-32768,-32768,   152,-32768,-32768,-32768,
   191,   192,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,   175,   -90,-32768,-32768,    66,    18,-32768,-32768,
   -74,-32768,-32768,-32768,-32768,-32768,-32768,    19,   -24,   -26,
   -10,   -28,   -76,   119,-32768,    40,   144,   120,   143,-32768,
   -34,-32768,-32768,-32768,   -46,   -84,   128,    13,   -53,    -7
};


#define	YYLAST		209


static const short yytable[] = {    11,
    12,    13,    44,    46,    43,   112,    69,    55,    99,   121,
   122,   123,    34,   128,     1,     7,    70,   160,   161,   162,
     8,   102,    94,     5,    95,    96,     9,     6,    10,    85,
    59,    97,    10,   141,   142,   143,    14,   139,   128,   163,
    73,    74,    75,   117,    15,    99,    99,    99,    82,    25,
   110,    39,    40,    41,   100,    34,    35,    36,    37,   152,
   153,   154,    90,    91,    92,    93,    94,    17,    95,    96,
   109,    38,    10,    85,   164,    97,   165,    17,    26,   166,
   118,   119,   120,    85,    10,    86,   107,    85,    48,   111,
    16,   100,   100,   100,    40,    41,   101,   116,    10,    85,
    28,   131,   132,   127,   148,    23,   157,   158,   159,   192,
   193,   125,   126,    24,    32,    49,    33,    42,    45,    47,
    56,    50,    60,    62,    41,    71,   173,    72,   177,   156,
    76,   172,    77,    78,   147,    81,    83,   103,   101,   195,
   104,   105,   113,    85,   124,   127,   137,   138,   156,   150,
   140,    40,   144,   145,   146,   151,   178,   179,   180,   131,
   202,   167,   169,   204,   170,   197,   207,   171,   174,   183,
   203,   181,   182,   184,   186,    39,   187,   189,   191,   194,
   196,   198,   201,   205,   199,   200,   206,   208,   209,   210,
   212,   213,    27,   185,   149,   168,   188,    80,     0,     0,
    84,     0,   106,     0,     0,     0,   114,     0,   115
};

static const short yycheck[] = {     7,
     8,     9,    29,    30,    29,    82,    41,    36,    62,    94,
    95,    96,     5,   104,    37,     4,    43,    10,    11,    12,
     9,    68,    29,     3,    31,    32,    15,    37,    35,    36,
    38,    38,    35,   118,   119,   120,    38,   114,   129,    32,
    48,    49,    50,    90,    38,    99,   100,   101,    56,    39,
    79,    22,    23,    24,    62,     5,     6,     7,     8,   134,
   135,   136,    25,    26,    27,    28,    29,    37,    31,    32,
    78,    21,    35,    36,    16,    38,    18,    37,    38,    21,
    91,    92,    93,    36,    35,    38,    37,    36,     4,    38,
    38,    99,   100,   101,    23,    24,    37,    38,    35,    36,
    39,    37,    38,    37,    38,    37,   141,   142,   143,    13,
    14,    99,   100,    37,    39,     4,    39,    39,    39,    38,
    37,    39,    37,    37,    24,    38,   161,    38,   163,   137,
    38,   160,    38,    40,    39,    38,    38,    38,    37,    19,
    38,    38,    38,    36,    38,    37,    33,    38,   156,    39,
    38,    23,    38,    38,    38,    38,   164,   165,   166,    37,
   195,    38,    38,   198,    38,   190,   201,    38,    37,    39,
   197,    38,    38,    38,    38,    22,    39,    39,    39,    39,
    39,    17,    20,    38,   192,   193,    38,    38,    38,    38,
     0,     0,    18,   176,   129,   156,   178,    54,    -1,    -1,
    58,    -1,    75,    -1,    -1,    -1,    88,    -1,    89
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/gnu/bison-1.28/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */



#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif



/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/local/gnu/bison-1.28/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 4:
#line 70 "bbpddl.y"
{ 
         domain_name = yyvsp[-3].str; ;
    break;}
case 8:
#line 78 "bbpddl.y"
{ constants = yyvsp[-1].flist; ;
    break;}
case 9:
#line 79 "bbpddl.y"
{
	 completely_free_fact_list(yyvsp[-1].flist); ;
    break;}
case 10:
#line 81 "bbpddl.y"
{ predicates = yyvsp[-1].flist; ;
    break;}
case 11:
#line 82 "bbpddl.y"
{ add_action(yyvsp[0].oplist); ;
    break;}
case 12:
#line 84 "bbpddl.y"
{
       check_requirement_flag(yyvsp[-1].tlist); free_token_list(yyvsp[-1].tlist); ;
    break;}
case 13:
#line 88 "bbpddl.y"
{ problem_name = yyvsp[-8].str; 
         if (strcmp(domain_name, yyvsp[-3].str) != 0)
	   do_error("domain doesn't match");
	 free(yyvsp[-3].str);
       ;
    break;}
case 17:
#line 98 "bbpddl.y"
{ the_types = yyvsp[-1].flist; ;
    break;}
case 18:
#line 99 "bbpddl.y"
{ initial_facts = yyvsp[-1].flist; ;
    break;}
case 19:
#line 100 "bbpddl.y"
{ the_goals = yyvsp[-1].flist; ;
    break;}
case 23:
#line 106 "bbpddl.y"
{ free(yyvsp[-1].str); ;
    break;}
case 24:
#line 107 "bbpddl.y"
{ max_time = atoi(yyvsp[-1].str);
	 free(yyvsp[-1].str);
       ;
    break;}
case 25:
#line 112 "bbpddl.y"
{ control_name = yyvsp[-8].str; free(yyvsp[-3].str); ;
    break;}
case 27:
#line 115 "bbpddl.y"
{ add_control(yyvsp[0].ctrllist); ;
    break;}
case 28:
#line 116 "bbpddl.y"
{ add_wffctrl (yyvsp[0].wffctrllist); ;
    break;}
case 29:
#line 117 "bbpddl.y"
{ add_defpred (yyvsp[0].defpredlist); ;
    break;}
case 30:
#line 118 "bbpddl.y"
{ add_control(yyvsp[-1].ctrllist); ;
    break;}
case 31:
#line 119 "bbpddl.y"
{ add_wffctrl (yyvsp[-1].wffctrllist); ;
    break;}
case 32:
#line 120 "bbpddl.y"
{ add_defpred (yyvsp[-1].defpredlist); ;
    break;}
case 33:
#line 122 "bbpddl.y"
{
          yyval.defpredlist = make_defpred(yyvsp[-5].str, yyvsp[-4].flist, yyvsp[-1].flist); 
         ;
    break;}
case 34:
#line 126 "bbpddl.y"
{ yyval.str = yyvsp[0].str; ;
    break;}
case 35:
#line 128 "bbpddl.y"
{ 
           yyval.oplist = make_action(yyvsp[-4].str, yyvsp[-3].flist, yyvsp[-2].flist, yyvsp[-1].flist);
         ;
    break;}
case 36:
#line 131 "bbpddl.y"
{
           yyval.oplist = make_action(yyvsp[-3].str, yyvsp[-2].flist, NULL, yyvsp[-1].flist); ;
    break;}
case 37:
#line 133 "bbpddl.y"
{ 
           yyval.oplist = make_action(yyvsp[-3].str, NULL, yyvsp[-2].flist, yyvsp[-1].flist); ;
    break;}
case 38:
#line 135 "bbpddl.y"
{
           yyval.oplist = make_action(yyvsp[-2].str, NULL, NULL, yyvsp[-1].flist);
         ;
    break;}
case 39:
#line 139 "bbpddl.y"
{
          yyval.ctrllist = make_control(yyvsp[-4].str, yyvsp[-1].flist);
        ;
    break;}
case 40:
#line 143 "bbpddl.y"
{
           yyval.wffctrllist = make_wffctrl(yyvsp[-4].str, yyvsp[-3].flist, yyvsp[-2].flist, 
					  yyvsp[-1].flist);
        ;
    break;}
case 41:
#line 148 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; ;
    break;}
case 42:
#line 150 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; ;
    break;}
case 43:
#line 151 "bbpddl.y"
{ yyval.flist = NULL; ;
    break;}
case 44:
#line 153 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; ;
    break;}
case 45:
#line 154 "bbpddl.y"
{ yyval.flist = NULL; ;
    break;}
case 46:
#line 156 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; ;
    break;}
case 47:
#line 159 "bbpddl.y"
{ yyval.flist = NULL; ;
    break;}
case 48:
#line 160 "bbpddl.y"
{ yyval.flist = yyvsp[-1].flist; ;
    break;}
case 49:
#line 162 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; add_object(yyvsp[0].flist); ;
    break;}
case 50:
#line 163 "bbpddl.y"
{ yyval.flist = yyvsp[-1].flist; add_object(yyvsp[-1].flist);
          type_object (yyvsp[-1].flist, yyvsp[0].tlist, 1); ;
    break;}
case 51:
#line 165 "bbpddl.y"
{ yyval.flist = yyvsp[-2].flist;
	  add_object(yyvsp[-2].flist);
	  type_object (yyvsp[-2].flist, yyvsp[-1].tlist, 1);
	  fact_list_append(yyval.flist, yyvsp[0].flist);
	;
    break;}
case 52:
#line 171 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; ;
    break;}
case 53:
#line 172 "bbpddl.y"
{ yyval.flist = yyvsp[-1].flist;
         type_object (yyvsp[-1].flist, yyvsp[0].tlist, 0); ;
    break;}
case 54:
#line 174 "bbpddl.y"
{ yyval.flist = yyvsp[-2].flist;
         type_object (yyvsp[-2].flist, yyvsp[-1].tlist, 0);
         fact_list_append(yyval.flist, yyvsp[0].flist);
       ;
    break;}
case 55:
#line 179 "bbpddl.y"
{ yyval.tlist = yyvsp[0].tlist; ;
    break;}
case 56:
#line 181 "bbpddl.y"
{ yyval.tlist = str2token(yyvsp[0].str); ;
    break;}
case 57:
#line 182 "bbpddl.y"
{ yyval.tlist = yyvsp[-1].tlist; ;
    break;}
case 58:
#line 185 "bbpddl.y"
{ yyval.tlist = str2token(yyvsp[0].str); ;
    break;}
case 59:
#line 186 "bbpddl.y"
{ yyval.tlist = str2token(yyvsp[-1].str);
	  yyval.tlist->next = yyvsp[0].tlist;
	;
    break;}
case 60:
#line 190 "bbpddl.y"
{ yyval.flist = token2fact(str2token(yyvsp[0].str)); ;
    break;}
case 61:
#line 191 "bbpddl.y"
{ yyval.flist = token2fact(str2token(yyvsp[-1].str));
           yyval.flist->next = yyvsp[0].flist;
         ;
    break;}
case 62:
#line 195 "bbpddl.y"
{ yyval.flist = token2fact(str2token(yyvsp[0].str)); ;
    break;}
case 63:
#line 196 "bbpddl.y"
{ yyval.flist = token2fact(str2token(yyvsp[-1].str));
	 yyval.flist->next = yyvsp[0].flist;
       ;
    break;}
case 64:
#line 200 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; ;
    break;}
case 65:
#line 201 "bbpddl.y"
{ yyval.flist = yyvsp[-1].flist;
	 fact_list_append(yyval.flist, yyvsp[0].flist); 
       ;
    break;}
case 66:
#line 205 "bbpddl.y"
{ yyval.flist = token2fact(str2token(yyvsp[-1].str)); ;
    break;}
case 67:
#line 206 "bbpddl.y"
{ 
	 yyval.flist = token2fact(str2token(yyvsp[-2].str));
	 yyval.flist->body = yyvsp[-1].flist;
       ;
    break;}
case 68:
#line 211 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; ;
    break;}
case 69:
#line 212 "bbpddl.y"
{ yyval.flist = yyvsp[-1].flist; ;
    break;}
case 70:
#line 213 "bbpddl.y"
{ yyval.flist = NULL; ;
    break;}
case 71:
#line 214 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; ;
    break;}
case 72:
#line 215 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; ;
    break;}
case 73:
#line 216 "bbpddl.y"
{ yyval.flist = yyvsp[0].flist; ;
    break;}
case 74:
#line 219 "bbpddl.y"
{
            token_list t;
	    t = strdup2token("exists");
	    t->next = yyvsp[-2].tlist;
	    yyval.flist = token2fact(t);
	    yyval.flist->next = yyvsp[-3].flist;  /* parameter */
	    yyval.flist->body = yyvsp[-1].flist;
          ;
    break;}
case 75:
#line 228 "bbpddl.y"
{
            token_list t;
	    t = strdup2token("noexists");
	    t->next = yyvsp[-2].tlist;
	    yyval.flist = token2fact(t);
	    yyval.flist->next = yyvsp[-3].flist;  /* parameter */
	    yyval.flist->body = yyvsp[-1].flist;
          ;
    break;}
case 76:
#line 237 "bbpddl.y"
{
            token_list t;
	    t = strdup2token("forall");
	    t->next = yyvsp[-2].tlist;
	    yyval.flist = token2fact(t);
	    yyval.flist->next = yyvsp[-3].flist;  /* parameter */
	    yyval.flist->body = yyvsp[-1].flist;
          ;
    break;}
case 77:
#line 246 "bbpddl.y"
{ yyval.flist = token2fact(yyvsp[0].tlist); ;
    break;}
case 78:
#line 247 "bbpddl.y"
{ yyval.flist = token2fact(yyvsp[-1].tlist);
         yyval.flist->next = yyvsp[0].flist;
       ;
    break;}
case 79:
#line 251 "bbpddl.y"
{ yyval.tlist = yyvsp[-1].tlist; ;
    break;}
case 80:
#line 252 "bbpddl.y"
{
	 yyval.tlist = strdup2token(DELETE);
	 yyval.tlist->next = yyvsp[-1].tlist;
       ;
    break;}
case 81:
#line 256 "bbpddl.y"
{
	 yyval.tlist = strdup2token("next");
	 yyval.tlist->next = yyvsp[-1].tlist;
       ;
    break;}
case 82:
#line 260 "bbpddl.y"
{
	 yyval.tlist = strdup2token("goal");
	 yyval.tlist->next = yyvsp[-1].tlist;
       ;
    break;}
case 83:
#line 264 "bbpddl.y"
{ yyval.tlist = NULL; ;
    break;}
case 84:
#line 266 "bbpddl.y"
{ yyval.tlist = str2token(yyvsp[0].str); ;
    break;}
case 85:
#line 267 "bbpddl.y"
{ yyval.tlist = str2token(yyvsp[-1].str);
         yyval.tlist->next = yyvsp[0].tlist; ;
    break;}
case 86:
#line 270 "bbpddl.y"
{ yyval.tlist = str2token(yyvsp[0].str); ;
    break;}
case 87:
#line 271 "bbpddl.y"
{ yyval.tlist = str2token(yyvsp[0].str); ;
    break;}
case 88:
#line 272 "bbpddl.y"
{ yyval.tlist = str2token(yyvsp[-1].str); 
         yyval.tlist->next = yyvsp[0].tlist; ;
    break;}
case 89:
#line 274 "bbpddl.y"
{ yyval.tlist = str2token(yyvsp[-1].str); 
	 yyval.tlist->next = yyvsp[0].tlist; ;
    break;}
case 90:
#line 277 "bbpddl.y"
{ yyval.str = bbstrdup(yytext); ;
    break;}
case 91:
#line 279 "bbpddl.y"
{ yyval.str = bbstrdup(yytext); ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/gnu/bison-1.28/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 281 "bbpddl.y"


/* check only allowed requirements are used */
void check_requirement_flag (token_list flags)
{
  char s[50];

  for (; flags; flags = flags->next) {
    if (strcmp("strips", flags->item) != 0 &&
	strcmp("typing", flags->item) != 0 &&
	strcmp("equality", flags->item) != 0) {
      sprintf(s, "requirement: %s is not supported\n", flags->item);
      do_error (s);
    } 
  }
}

/* form an action(operator) */
op_list make_action (char *name, param_list params, 
		     precond_list preconds, effect_list effects)
{
  op_list op;
  op = (op_list)malloc(sizeof(op_s));
  op->name = name;
  op->params = params;
  op->preconds = preconds;
  op->effects = effects;
  set_insts(op);
  op->next = NULL;
  return op;
}

/* make a defpredicate */
defpred_list make_defpred (char *name, param_list params, fact_list formula)
{
  defpred_list dp;
  dp = (defpred_list)malloc(sizeof(defpred_s));
  dp->name = name;
  dp->params = params;
  dp->formula = formula;
  dp->next = NULL;
  return dp;
}

control_list make_control (char *name, fact_list excludes)
{
  control_list ctrl;
  
  ctrl = (control_list)calloc(1, sizeof(control_s));
  ctrl->name = name;
  ctrl->excludes = excludes;
  // ctrl->next = NULL;
  return ctrl;
}

/* form an wffcontrol */
wffctrl_list make_wffctrl (char *name, fact_list scope, 
			   fact_list preconds, fact_list effects)
{
  wffctrl_list ctrl;
  ctrl = (wffctrl_list)calloc(1, sizeof(wffctrl_s));
  ctrl->name = name;
  ctrl->scope = scope;
  ctrl->preconds = preconds;
  ctrl->effects = effects;
  // ctrl->next = NULL;
  return ctrl;
}

/* add objects */
void add_object (fact_list object)
{	
  token_list prev;

  if (input_type == PROBLEM_INPUT) {
    if (objects == 0) {
      prev = objects = strdup2token(object->item->item);
      object = object->next;
    }
    else {
      prev = objects;
      while (prev->next) prev = prev->next;
    }	 
    for (; object; object = object->next) {
      prev = prev->next = strdup2token(object->item->item);
    }
  }
}

/* type object */
void type_object (fact_list objects, token_list types, int retain)
{
  char *oname;
  token_list t;
  fact_list obj, next;

  for (obj = objects; obj; obj = next) {
    next = obj->next;
    oname = obj->item->item;
    if (retain) {	   	/* retain the original *no* type object */
      obj = obj->next = token2fact(strdup2token(oname));      
    }
    obj->item->next = strdup2token(types->item);
    for (t = types->next; t; t = t->next) {
      obj = obj->next = token2fact(strdup2token(oname));
      obj->item->next = strdup2token(t->item);
    }
    obj->next = next;
  }
}

void add_action (op_list op)
{
  op_list prev;

  if (ops == NULL) 
    ops = op;
  else {
    prev = ops;
    while (prev->next) prev = prev->next;
    prev->next = op;
  }
}

void add_defpred (defpred_list dp)
{
  if (dps == NULL) 
    dps = dp;
  else {
    dp->next = dps;
    dps = dp;
  } 
}

void add_control (control_list ctrl)
{
  control_list prev;

  if (controls == NULL) 
    controls = ctrl;
  else {
    prev = controls;
    while (prev->next) 
      prev = prev->next;
    prev->next = ctrl;
  } 
}

/* return: 1: NORMAL_MODE; 0:FORCE_MODE */
int comp_precond_and_effect (wffctrl_list ctrl)
{
  token_list tlist;
        
  tlist = ctrl->effects->item;
  if (strcmp(tlist->item, "next") == 0) {
    if (equal_facts(tlist, ctrl->preconds->item) &&
	ctrl->preconds->next == NULL) {
      return WFF_FORCE_MODE;
    }
  } 
  return WFF_NORMAL_MODE;
}

void add_wffctrl (wffctrl_list ctrl)
{
  wffctrl_list prev;

  
  ctrl->condflag = comp_precond_and_effect(ctrl);

  if (wffctrls == NULL) 
    wffctrls = ctrl;
  else {
    prev = wffctrls;
    while (prev->next) 
      prev = prev->next;
    prev->next = ctrl;
  } 
}

int yyerror(char * s)
{
  fprintf(stderr,"%s\n",s);
  fprintf(stderr,"Error occurred at or near line %d\n", yylineno);
  exit(1);
}
