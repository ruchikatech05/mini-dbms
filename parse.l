%{
#include <stdio.h>
#include "y.tab.h"
#include "sql.h"
#include "check.h"
#include "select.h"
#include "update.h"


%}
%%
"update "[a-zA-Z][a-zA-z]* update( yytext);return UPDATE;
"set"          updateflag();return SET;
"select"      selectflag();return SELECT;
"delete"      delete1();return DELET;
"+"|"-"|"/"|"%"   updateope(yytext);return OPERATOR;
"*"           updateope(yytext);selectstar();return STAR;
"from"        return FROM;
"and"          and();return AND;
"or"           or();return OR;
"where"        whereclause();return WHERE;
[a-zA-Z][a-zA-Z]*"."[a-z]* wheretable(yytext);return TBL;
"create table"	return CREATE;
"insert into "[A-Za-z_][a-zA-Z]*  checktab(yytext);return INSERT;
"'"[a-z]+"'"     value(yytext);selectcond(yytext);insert(yytext);return NAME;
[0-9]+"."?[0-9]*  value(yytext);selectcond(yytext);insert(yytext);return NUMBER;
"values ("       return VALUES;
"("   		return OPENPAREN;
[A-Z][a-zA-Z]* tabldel(yytext);fromtable(yytext);tablefunc(yytext);return TNAME;
")"		return CLOSEPAREN;
";"	        return SEMICOLON;
"primary key"	primary();return PRIMARY_KEY;
","             return COMMA;
"foreign key" 	foreign();return FOREIGN_KEY;
"references"	ref();return REFERENCES;
"varchar2"|"number"|"double" attrtype(yytext);return TYPE;
"check("[a-z]*   getcheck(yytext);return CHECK;
">"[0-9]+         operator(yytext);return GT;
"<"[0-9]+         operator(yytext);return LT;
"!="[0-9]+        operator(yytext);return NE;
"="              updatope(yytext);ope(yytext);return EQ;
"<>"             updatope(yytext);ope(yytext);return NET;          
">"|"<"|">="|"<=" updatope(yytext);ope(yytext);return COMPARISON;
[a-z]+          updateattr(yytext);select1(yytext);attr(yytext);return ATRNAME;
[ \n]+ 		/*   */;
[ \t]+		/*ignore end of file*/;
%%
