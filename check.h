/******************************************************************
           PROGRAM TO IMPLEMENT DATABASE MANAGEMENT SYSTEM


FILE 5 :: check.h


DESCRIPTION :: 
It contains all the functions for handling the 
actions performed by the parser on getting the command of selection
********************************************************************/

/***************************************
    GLOBAL VARIABLES DECLARATION
****************************************/
char num[MAXN];
char oper[MAXN];
char att[MAXN];

/*******************************************************************
FUNCTION :: TO TAKE THE ATTRIBUTE NAME AS INPUT AND STORE IT.
**********************************************************/

getcheck(yytext)
{
     int i,j;
     char *tmp;
     tmp=malloc(MAXN);
     
    
     strcpy(tmp,(char*)yytext);
    
     for(i=6,j=0;i<strlen(tmp);i++,j++)
     {
         att[j]=tmp[i];
     } 
     att[j]='\0';
         
     
     strcpy(c.chk_attr,att);
}

/*************************************************************
FUNCTION :: TO CHECK THE OPERATOR IN CONSTRAINT FILE. **********************************************************/

operator(yytext)
{   if(updat==0&&delet==0)
  {
    int len=0,m=0;
    char *p1,*p2, *tmp1;
    tmp1=malloc(MAXN);
    int i,j,k,l=0;
    strcpy(tmp1,(char*)yytext);
    

    len=strlen(tmp1);
   
    for(i=0;i<len;i++)
    {
        if(isdigit(tmp1[i]))
        {
           l=i;
           for(j=i,k=0;j<len;j++,k++)
           {
               num[k]=tmp1[j];
           }
            break;  
        } 
    } 
    
    strcpy(c.chk_num,num);
    for(m=0;m<l;m++)
    {
        oper[m]=tmp1[m];
    }
    oper[m]='\0';
   
    strcpy(c.chk_oper,oper); 
    
    fk=fopen(constraints_file,"w");
    fwrite(&c,sizeof(struct constraints),1,fk);
    fclose(fk);
  }
}

