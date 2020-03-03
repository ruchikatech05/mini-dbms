#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 2 "sql.y"
#include<stdio.h>
#include <string.h>


void yyerror(const char *str)
{
    printf("error:%s\n",str);
}
int yywrap()
{
    return 1;
}
extern int yydebug;
main()
{
    yydebug=1;
    yyparse();
}
#line 36 "y.tab.c"
#define YYERRCODE 256
#define CREATE 257
#define OPENPAREN 258
#define TNAME 259
#define PRIMARY_KEY 260
#define CLOSEPAREN 261
#define SEMICOLON 262
#define FOREIGN_KEY 263
#define REFERENCES 264
#define ATRNAME 265
#define TYPE 266
#define COMMA 267
#define INSERT 268
#define VALUES 269
#define NAME 270
#define NUMBER 271
#define CHECK 272
#define GT 273
#define LT 274
#define NE 275
#define FROM 276
#define SELECT 277
#define STAR 278
#define WHERE 279
#define TBL 280
#define EQ 281
#define COMPARISON 282
#define OR 283
#define AND 284
#define UPDATE 285
#define SET 286
#define OPERATOR 287
#define DELET 288
#define EXIT 289
#define NET 290
const short yylhs[] = {                                        -1,
    2,    0,    1,    3,    3,    3,    3,    3,    4,    9,
   10,   11,   11,   11,   11,   11,   12,   12,   12,    5,
   13,   13,   14,   14,   16,   15,    6,   17,   20,   17,
   19,   22,   19,   23,   21,   24,   18,   18,   25,   25,
   25,   29,   26,   26,   27,   27,   28,   28,   30,   30,
    7,    7,   31,   31,   31,   31,   32,   32,    8,   33,
   34,   34,
};
const short yylen[] = {                                         2,
    0,    2,    1,    1,    1,    1,    1,    1,    3,    3,
    3,    2,    2,    4,    4,    6,    2,    2,    2,    4,
    1,    1,    3,    1,    0,    3,    2,    4,    0,    3,
    1,    0,    4,    0,    4,    0,    4,    1,    5,    5,
    1,    1,    5,    1,    1,    5,    1,    1,    1,    1,
    5,    7,    2,    2,    2,    2,    6,    1,    4,    4,
    2,    2,
};
const short yydefred[] = {                                      1,
    0,    0,    0,    0,    0,    0,    0,    2,    3,    4,
    5,    6,    7,    8,    0,    0,   29,    0,   27,    0,
    0,    0,    9,   22,   21,    0,    0,    0,    0,    0,
    0,    0,   25,    0,   20,   24,    0,   34,   30,   31,
    0,    0,    0,    0,    0,    0,    0,   59,    0,    0,
    0,   10,    0,    0,   32,    0,   42,   36,    0,   28,
   38,   44,   56,    0,   53,   55,   54,    0,   58,   51,
    0,   11,   13,    0,    0,    0,   12,   26,   23,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   33,   35,    0,   47,   48,
    0,   52,    0,   61,   62,   60,   14,    0,   17,   18,
   19,   15,    0,   37,   41,    0,    0,    0,    0,   45,
   50,   49,   43,    0,    0,   16,    0,    0,    0,   57,
    0,    0,    0,   39,   40,    0,   46,
};
const short yydgoto[] = {                                       1,
    8,    2,    9,   10,   11,   12,   13,   14,   23,   32,
   52,   95,   65,   35,   36,   53,   19,   60,   39,   27,
   40,   80,   56,   82,  114,   61,  123,  101,   62,  124,
   46,   70,   48,   89,
};
const short yysindex[] = {                                      0,
    0, -254, -250, -226, -259, -220, -212,    0,    0,    0,
    0,    0,    0,    0, -193, -218,    0, -209,    0, -197,
 -190, -192,    0,    0,    0, -222, -239, -187, -266, -205,
 -191, -221,    0, -218,    0,    0, -189,    0,    0,    0,
 -257, -194, -235, -188, -185, -214, -186,    0, -221, -184,
 -252,    0, -182, -222,    0, -178,    0,    0, -198,    0,
    0,    0,    0, -249,    0,    0,    0, -195,    0,    0,
 -227,    0,    0, -177, -176, -224,    0,    0,    0, -239,
 -257, -172, -225, -218, -214, -175, -218, -180, -170, -221,
 -171, -167, -166, -165, -221,    0,    0, -255,    0,    0,
 -218,    0, -249,    0,    0,    0,    0, -162,    0,    0,
    0,    0, -181,    0,    0, -258, -163, -221, -223,    0,
    0,    0,    0, -179, -160,    0, -174, -218, -225,    0,
 -258, -258, -218,    0,    0, -159,    0,
};
const short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -210,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
const short yygindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   49,
  -48,    0,  -16,   50,    0,    0,    0,   24,   27,    0,
    0,    0,    0,    0,    0,    0,  -69, -102,   10,    0,
  -62,   25,    0,    0,
};
#define YYTABLESIZE 117
const short yytable[] = {                                      26,
   72,   85,    3,  120,   57,   17,   57,   74,   15,   58,
   75,   42,   31,    4,   43,   44,  128,   54,   18,   76,
   45,   59,    5,  113,  121,  122,  133,   37,   42,   64,
    6,   84,   44,    7,   24,   25,   38,   45,   33,   50,
  117,  107,   16,   68,   34,   51,  112,   69,   92,   93,
   94,   24,   25,   87,   88,   99,  100,  127,  100,   47,
   47,  134,  135,   21,   22,   20,   28,   29,   30,  126,
  104,   41,   31,   47,   49,   55,   63,   73,   71,   78,
   81,   83,   66,   86,  116,   67,   98,   90,   91,  103,
  105,  106,  108,  109,  110,  111,  118,  125,  119,   77,
  129,  130,  137,   79,   97,  131,   96,  115,    0,  102,
    0,  132,    0,    0,    0,    0,  136,
};
const short yycheck[] = {                                      16,
   49,   64,  257,  262,  262,  265,  262,  260,  259,  267,
  263,  278,  265,  268,  281,  282,  119,   34,  278,  272,
  287,  279,  277,  279,  283,  284,  129,  267,  278,  265,
  285,  281,  282,  288,  270,  271,  276,  287,  261,  261,
  103,   90,  269,  258,  267,  267,   95,  262,  273,  274,
  275,  270,  271,  281,  282,  281,  282,  281,  282,  270,
  271,  131,  132,  276,  258,  286,  276,  265,  259,  118,
   87,  259,  265,  279,  266,  265,  271,  262,  265,  262,
  259,  280,  271,  279,  101,  271,  259,  265,  265,  265,
  271,  262,  264,  261,  261,  261,  259,  261,  280,   51,
  280,  262,  262,   54,   81,  280,   80,   98,   -1,   85,
   -1,  128,   -1,   -1,   -1,   -1,  133,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"CREATE","OPENPAREN","TNAME",
"PRIMARY_KEY","CLOSEPAREN","SEMICOLON","FOREIGN_KEY","REFERENCES","ATRNAME",
"TYPE","COMMA","INSERT","VALUES","NAME","NUMBER","CHECK","GT","LT","NE","FROM",
"SELECT","STAR","WHERE","TBL","EQ","COMPARISON","OR","AND","UPDATE","SET",
"OPERATOR","DELET","EXIT","NET",
};
const char * const yyrule[] = {
"$accept : start_sql",
"$$1 :",
"start_sql : $$1 begin",
"begin : command",
"command : create_statement",
"command : insert_statement",
"command : select_statement",
"command : update_statement",
"command : delete_statement",
"create_statement : CREATE TNAME next",
"next : OPENPAREN k2 k1",
"k2 : ATRNAME TYPE k1",
"k1 : COMMA k2",
"k1 : CLOSEPAREN SEMICOLON",
"k1 : COMMA PRIMARY_KEY ATRNAME k1",
"k1 : COMMA CHECK op k1",
"k1 : COMMA FOREIGN_KEY ATRNAME REFERENCES TNAME k1",
"op : GT CLOSEPAREN",
"op : LT CLOSEPAREN",
"op : NE CLOSEPAREN",
"insert_statement : INSERT VALUES n com2",
"n : NUMBER",
"n : NAME",
"com2 : COMMA n com2",
"com2 : com3",
"$$2 :",
"com3 : CLOSEPAREN $$2 SEMICOLON",
"select_statement : SELECT opr",
"opr : STAR FROM TNAME opr3",
"$$3 :",
"opr : ATRNAME $$3 opr1",
"opr1 : opr2",
"$$4 :",
"opr1 : COMMA ATRNAME $$4 opr1",
"$$5 :",
"opr2 : FROM $$5 TNAME opr3",
"$$6 :",
"opr3 : COMMA $$6 TNAME opr4",
"opr3 : opr5",
"opr4 : WHERE TBL EQ TBL opr6",
"opr4 : WHERE TBL aop n opr6",
"opr4 : opr7",
"opr7 : SEMICOLON",
"opr5 : WHERE TBL aop n opr6",
"opr5 : opr7",
"opr6 : SEMICOLON",
"opr6 : ao TBL aop n SEMICOLON",
"aop : EQ",
"aop : COMPARISON",
"ao : AND",
"ao : OR",
"update_statement : UPDATE SET ATRNAME up2 up1",
"update_statement : UPDATE SET ATRNAME EQ ATRNAME up2 up1",
"up2 : EQ n",
"up2 : OPERATOR NUMBER",
"up2 : COMPARISON NUMBER",
"up2 : STAR NUMBER",
"up1 : OPENPAREN WHERE ATRNAME up2 CLOSEPAREN SEMICOLON",
"up1 : SEMICOLON",
"delete_statement : DELET FROM TNAME del1",
"del1 : WHERE ATRNAME del2 SEMICOLON",
"del2 : EQ n",
"del2 : COMPARISON NUMBER",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 29 "sql.y"
{ printf ("\nmydbms>"); }
break;
case 3:
#line 31 "sql.y"
{ printf("\n");exit(0);}
break;
case 13:
#line 51 "sql.y"
{ exit (0);}
break;
case 25:
#line 72 "sql.y"
{checker();}
break;
case 26:
#line 72 "sql.y"
{exit(0);}
break;
case 29:
#line 77 "sql.y"
{count1();}
break;
case 32:
#line 81 "sql.y"
{count1();}
break;
case 34:
#line 84 "sql.y"
{end1();}
break;
case 36:
#line 86 "sql.y"
{joinsignal();}
break;
case 42:
#line 95 "sql.y"
{nowhere();}
break;
case 45:
#line 101 "sql.y"
{selectend();}
break;
case 46:
#line 102 "sql.y"
{selectend();}
break;
case 57:
#line 124 "sql.y"
{do_the_update();}
break;
case 58:
#line 125 "sql.y"
{do_the_update();}
break;
case 60:
#line 130 "sql.y"
{do_the_delete();}
break;
#line 548 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
