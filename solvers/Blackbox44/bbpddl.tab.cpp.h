typedef union {
  char *str;
  op_list oplist;
  defpred_list defpredlist;
  control_list ctrllist;
  wffctrl_list wffctrllist;
  fact_list flist;
  token_list tlist;
} YYSTYPE;
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


extern YYSTYPE yylval;
