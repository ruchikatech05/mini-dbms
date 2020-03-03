%{
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
%}
%token 	CREATE OPENPAREN TNAME PRIMARY_KEY CLOSEPAREN SEMICOLON 
%token	FOREIGN_KEY REFERENCES ATRNAME TYPE COMMA INSERT VALUES  
%token	NAME NUMBER CHECK GT LT NE FROM SELECT STAR WHERE TBL EQ 
%token	COMPARISON OR AND UPDATE SET OPERATOR DELET EXIT NET
 
%%


start_sql : { printf ("\nmydbms>"); } 
	      begin;
begin 	  : command { printf("\n");exit(0);}
	  




command   : create_statement
	  | insert_statement
	  | select_statement
	  | update_statement
 	  | delete_statement
	  ;


//grammar for create statement.

create_statement : CREATE TNAME next;
next    	 : OPENPAREN k2 k1;
k2		 : ATRNAME TYPE k1;
k1		 : COMMA k2
		 | CLOSEPAREN SEMICOLON { exit (0);}
		 | COMMA PRIMARY_KEY ATRNAME k1
		 | COMMA CHECK op k1
		 | COMMA FOREIGN_KEY ATRNAME REFERENCES TNAME k1
		 ;

op 		 : GT CLOSEPAREN 
		 | LT CLOSEPAREN 
		 | NE CLOSEPAREN 
		 ;


insert_statement : INSERT VALUES n com2;
n		 : NUMBER
		 | NAME
		 ;

com2		 : COMMA n com2
		 | com3
		 ;

com3		 : CLOSEPAREN {checker();} SEMICOLON {exit(0);} ; 

 
select_statement : SELECT opr;
opr		 : STAR FROM TNAME opr3
		 | ATRNAME {count1();} opr1
		 ;

opr1		 : opr2
		 | COMMA ATRNAME {count1();} opr1
		 ;

opr2		 : FROM {end1();} TNAME opr3;

opr3		 : COMMA {joinsignal();} TNAME  opr4
		 | opr5
		 ;

opr4		 : WHERE TBL EQ TBL opr6
		 | WHERE TBL aop n opr6 
		 | opr7
		 ;

opr7		 : SEMICOLON {nowhere();};

opr5		 : WHERE TBL aop n opr6
		 | opr7
		 ;

opr6		 : SEMICOLON {selectend();}
		 | ao TBL aop n SEMICOLON {selectend();}
		 ;

aop		 :EQ
		 |COMPARISON
		 ;

ao		 : AND
		 | OR
		 ;


update_statement : UPDATE SET ATRNAME up2 up1
		 | UPDATE SET ATRNAME EQ ATRNAME up2 up1
		 ;

up2		 : EQ n
		 | OPERATOR NUMBER
		 | COMPARISON NUMBER
		 | STAR NUMBER
		 ;

up1		 : OPENPAREN WHERE ATRNAME up2 CLOSEPAREN SEMICOLON {do_the_update();}
		 |SEMICOLON{do_the_update();}
		 ;

delete_statement : DELET FROM TNAME del1;

del1		 : WHERE ATRNAME del2 SEMICOLON{do_the_delete();};

del2		 : EQ n
		 | COMPARISON NUMBER
		 ;
%%
