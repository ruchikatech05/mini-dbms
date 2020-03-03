/***************************************************************************
           PROGRAM TO IMPLEMENT DATABASE MANAGEMENT SYSTEM


FILE 3 :: sql.h


DESCRIPTION :: 
contains all the functions for handling the 
actions performed by the parser on getting the command 
****************************************************************************/

/************************
    HEADER FILES
************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<strings.h>
#include<math.h>

#define MAXN 100

/***************************************
    GLOBAL VARIABLES DECLARATION
****************************************/
char schema_file_name[MAXN];
char data_file_name[MAXN];
char constraints_file[MAXN];
char tmp1[MAXN],tmp2[MAXN];
char tab4[MAXN];
char output[MAXN];
char tname[MAXN];
char kkey[MAXN];
char *tempname;
char tempname2[MAXN];
char *temp;
char tmp[MAXN];
char tablename[MAXN];
char tab1[MAXN];
char tab2[MAXN];
char tab3[MAXN];
char seltab1[MAXN],seltab2[MAXN];
char whereattr[8][MAXN];
char whereoper[8][MAXN];
char wherevalue[8][MAXN];
char jointab1[MAXN],jointab2[MAXN],joinattr1[MAXN],joinattr2[MAXN];
static int cntr1;
static int all,cntr,joinn,nowhr,endsel,flagsel,wflag,andflag,orflag;
FILE *ftable,*ff,*fd,*fd1,*fd2,*fp,*fk,*fp1,*fr;
static int h,l,q;
static int fref,flagp=0,flag=0,flg=0,m1=0,m2=0,updat=0,delet=0,wheredelflag=0,whereupdate=0;
static int ctrattr=0;
static int count=0;

/******************************************
ENUMERATION TYPE TO DEFINE BOOL DATA TYPE 
FALSE=0
TRUE=1
*******************************************/
enum bool{false,true};

/***********************************************
STRUCTURE TO HOLD THE ATTRIBUTE OF A SCHEMA
************************************************/
struct att
{
    char n[MAXN];
    char t[MAXN];
}d;

/*****************************************************
STRUCTURE TO HOLD THE CONSTRAINTS
*****************************************************/

struct constraints
{
    char p_key[MAXN];
    char f_key[MAXN];
    char ftable[MAXN];
    char chk_attr[MAXN];
    char chk_oper[MAXN];
    char chk_num[MAXN];

}c;

/*******************************************************
STRUCTURE TO HOLD THE DATA OF THE RELATION
********************************************************/
struct attribute
{
        
        char name[MAXN];
        char type[MAXN];
        char values[MAXN];
}a[8],b[8],s,s1,s2,selattr[8],put[20][8],joins[20];

/**********************************************************************
FUNCTION:: TO SIGNIFY THAT FOREIGN KEY IS REFERENCED IN CURRENT QUERY
IT IS CALLED BY YACC(PARSER)
**********************************************************************/
void foreign()
{
     flag=1;
}

/**********************************************************************
FUNCTION:: TO SIGNIFY THAT PRIMARY KEY IS DEFINED IN CURRENT QUERY
IT IS CALLED BY YACC(PARSER)
**********************************************************************/

void primary()
{
    flagp=1;
}

/**********************************************************************
FUNCTION::TO CHECK IF THE TABLE BEING CREATED BY CURRENT QUERY ALREADY EXIST
INPUT ::TABLE NAME TO BE CHECKED
**********************************************************************/

void check_if_table_already_exist(char *r)
{
    char *ttable;
    ttable=malloc(MAXN);
    ftable=fopen("table.txt","r");

    if(ftable==NULL)
    {
         return;
    }

    while(fscanf(ftable,"%s",ttable)!=EOF)
    {
        if(strcmp(ttable,r)==0)
        {
             printf("error :: table already exist \n");
             exit(0);
         }
    }

    fclose(ftable);
}    

/**********************************************************************
FUNCTION::TO CHECK IF THE TABLE BEING INSERTED OR DESCRIBED
          DOES NOT EXIST
INPUT ::TABLE NAME TO BE CHECKED
**********************************************************************/

void check_if_table_does_not_exist(char *w)
{
     int flag=0;
     char *tt;
     tt=malloc(MAXN);
     ftable=fopen("table.txt","r");
     if(ftable==NULL)
     {
          printf("table does not exist\n");
          exit(0);
     }

     while(fscanf(ftable,"%s",tt)!=EOF)
     {
        if(strcmp(tt,w)==0)
        {
            flag=1;
	    break;     
        }
    }
    if(flag==0)
    {
        printf("\ntable %s does not exist",w);
        exit(0);
    } 

   fclose(ftable);    
}

/**********************************************************************
FUNCTION:: TO CHECK IF THE TABLE BEING REFERENCED BY FOREIGN KEY EXIST OR NOT
INPUT :: TABLE NAME TO BE CHECKED
**********************************************************************/

void check_if_table_referenced_exist(char *w1)
{
     int wflag=0;
     char *ttt;
     ttt=malloc(MAXN);
     ftable=fopen("table.txt","r");
     if(ftable==NULL)
     {
          printf("table does not exist\n");
          exit(0);
     }

     while(fscanf(ftable,"%s",ttt)!=EOF)
     {
        if(strcmp(ttt,w1)==0)
        {
            wflag=1;     
        }
     }

     if(wflag==0)
     {
          printf("\ntable %s does not exist\n",w1);
          exit(0);
     } 

     fclose(ftable);    
}

/*****************************************************************
FUNCTION::TO CREATE THE TABLE TO INSERT INTO BY GETTING THE TOKEN FROM 
          THE YACC(parser)
IT IS CALLED BY YACC(parser)
*******************************************************************/
void checktab(yytext)
{
    int cflag=0,f=0, i, j, k;
    int flag3=0;
    char *t;

    t=malloc(MAXN);
    ftable=fopen("table.txt","r");
    tempname=malloc(MAXN);
    strcpy(tempname,(char*)yytext);

    for(i=0;i<12;i++)
        ++tempname;
    
    check_if_table_does_not_exist(tempname);
    strcpy(data_file_name,tempname);
    strcpy(tempname2,tempname);
    strcat(tempname2,"constraints");
    strcpy(constraints_file,tempname2);
    strcat(tempname,"schema");
    strcpy(schema_file_name,tempname);
}

/************************************************************************
FUNCTION :: TO COUNT THE NO OF STRUCTURES IN A DATAFILE 
1 STRUCTURE IS HOLDING 1 ATTRIBUTE (NAME,TYPE,VALUE)
**************************************************************************/
int count_no_of_structs_in_datafile()
{
    int rt1=0,ct1=0,qt=0;
    fd=fopen(data_file_name,"r");
    if(fd==NULL)
    {    
       printf("No tuple has been inserted in the relation\n"); 
       exit(0);
    }
    fseek(fd,0,SEEK_END);
    rt1=ftell(fd);
    ct1=rt1/sizeof(struct attribute);
    fclose(fd);
    return(ct1);  
}

/************************************************************************
FUNCTION :: TO COUNT THE NO OF STRUCTURES IN A SCHEMA FILE 
1 STRUCTURE IS HOLDING 1 ATTRIBUTE (NAME,TYPE)
**************************************************************************/

int count_no_of_structs_in_schema()
{
    int yt=0,cnt=0;
    
    ff=fopen(schema_file_name,"r");

    if(ff==NULL)
        printf("file could not be opened\n");

    fseek(ff,0,SEEK_END); 
    yt=ftell(ff);
    cnt=yt/sizeof(struct att);
    fclose(ff);
    return(cnt);  
}

/************************************************************************
FUNCTION :: TO CHECK BEFORE INSERTING IF THE NO. OF ATTRIBUTES IN SCHEMA
            MATCH WITH THE NO. OF VALUES BEING INSERTED
*************************************************************************/
void checker()
{
    int n=0,i;
    int qt=count_no_of_structs_in_schema();
    if(qt==count)
    {
          fd=fopen(data_file_name,"a+");
          if(fd==NULL)
              printf("\ncould not open file in checker\n");
     
          for(i=0;i<count;i++)
          {
              fwrite(&a[i],sizeof(struct attribute),1,fd);
          }
          printf("\n1 ROW INSERTED IN TABLE \n");
          fclose(fd);
     } 

     if(qt!=count)
     {
          printf("no of entries entered do not match with schema\n");
          exit(0);
          /*DO NOTHING*/
     }
}
   
/***************************************************************************
FUNCTION :: TO CHECK ALL THE CONSTRAINTS IMPOSED ON ATTRIBUTES
INPUT :: VALUE TO BE INSERTED IN A TUPLE,NAME OF THE CORRESPONDING ATTRIBUTE
****************************************************************************/

void check_constraints(char *value,char *attname)
{
   int fflag=0;
   if((fk=fopen(constraints_file,"r"))==NULL)
   { 
       return;
   }
          
   if((fread(&c,sizeof(struct constraints),1,fk))==1)
   {           
      //CHECKING FOR PRIMARY KEY CONSTRAINT
      if((strcmp(attname,c.p_key)==0))
      {
          fd=fopen(data_file_name,"r");
          if(fd==NULL)
          {
              return; 
          } 
          while(fread(&s,sizeof(struct attribute),1,fd))
          {
              if(strcmp(s.name,attname)==0)
              {
                  if(strcmp(s.values,value)==0)
                  {
                      printf("primarykey constraint violated by ");
                      printf("value %s\n",value);
                      exit(0);
                   }
               }
            } 
            fclose(fd);  
       } 
       // CHECKING FOR FOREIGN KEY CONSTRAINT            
       if((strcmp(attname,c.f_key)==0))
       {     
            fd=fopen(c.ftable,"r");
            while(fread(&s,sizeof(struct attribute),1,fd))
            {
                if((strcmp(s.values,value))==0)
                {
                    fflag=1;
                } 
             }
             if(fflag==0)
             {
                printf("fkey constraint violation by "); 
                printf("value %s\n",value);  
                printf("referencing table %s\n", c.ftable);
                exit(0);
              }
              fclose(fd);
         
        }
        //CHECKING FOR CHECK CONSTRAINT
        if((strcmp(attname,c.chk_attr)==0))
        {
            if(strcmp(c.chk_oper,"<")==0)
            {
                if(atoi(c.chk_num)<atoi(value))
                {
                    printf("check constraint violated\n");
                    exit(0);
                }
            } 
            if(strcmp(c.chk_oper,">")==0)
            {
                if(atoi(c.chk_num)>atoi(value))
                {
                    printf("check constraint violated\n");
                    exit(0);
                }

            } 
            if(strcmp(c.chk_oper,"!=")==0)
            {
                if(atoi(c.chk_num)!=atoi(value))
                {
                    printf("check constraint violated\n");
                    exit(0);
                }
            } 
             
          
        }
        
       fclose(fk);
    }
        
}
/****************************************************************************
FUNCTION::IT GETS THE VALUE FROM THE YACC(parser) TO BE INSERTED IN THE TABLE
****************************************************************************/
void insert(yytext)
{ if (flagsel==1||updat==1||delet==1)
  {
      printf("\n");
   }
 else
{   char *va;
    int l,n=0,s=0;
    enum bool c,x,z;

    va=malloc(MAXN);
    ff=fopen(schema_file_name,"r+w");
     
    //printf("in insert value in constraints_file is %s\n",constraints_file);
    if(ff==NULL)
     printf("file could not be open\n");
    fseek(ff,sizeof(struct att)*count,SEEK_SET);
    fread(&d,sizeof(struct att),1,ff);
    fclose(ff); 
    
       
    if((strcmp(d.t,"number"))==0)
    {
         c=checkifnumber(yytext);
         strcpy(va,(char*)yytext); 

         if(c==false)
         {
           printf("value %s to be inserted is of wrong data type\n",yytext);
           exit(0);
         }
         if(c==true)
         {
                          
         
           check_constraints(va,d.n);//CALLING FUNCTION TO CHECK CONSTRAINTS
         
           strcpy(a[count].name,d.n);
           strcpy(a[count].type,d.t);
           strcpy(a[count].values,(char*)yytext);
                
          }
    }

    if((strcmp(d.t,"double")==0))
    {           
            x=checkifdouble(yytext);
            strcpy(va,(char*)yytext);
            
            
            check_constraints(va,d.n);//CALLING FUNCTION TO CHECK CONSTRAINTS
            if(x==false)
            {
              printf("value %s  is not of type double\n",yytext);
            }
            else
            {
              strcpy(a[count].name,d.n);
              strcpy(a[count].type,d.t);
              strcpy(a[count].values,(char*)yytext);
            }
    } 

    if((strcmp(d.t,"varchar2"))==0)
    {
        char hj[MAXN],sd[MAXN];  
        int f;
        int x=strlen((char*)yytext);
        strcpy(sd,(char*)yytext);

        for(f=1;f<x;f++)
        {
            hj[f-1]=sd[f];
        }
        hj[x-2]='\0';
        
        strcpy((char*)yytext,hj);
        
        strcpy(va,(char*)yytext);
       
        check_constraints(va,d.n);//CALLING FUNCTION TO CHECK CONSTRAINTS
        z=checkifstring(yytext);

        if(z==false)
        {
            printf("the value %s is not a string\n",yytext);
        }
        else
        {
           strcpy(a[count].name,d.n);
           strcpy(a[count].type,d.t);
           strcpy(a[count].values,(char*)yytext); 
        
         }
   }
    
  
  count++;  
  }
}
/***********************************************************************
FUNCTION :: TO DO TYPE CHECKING WHETHER VALUE IS NUMBER OR NOT
************************************************************************/
int checkifnumber(char *y)
{
    int i,flag=0;
    int n=strlen(y);
    for(i=0;i<n;i++)
    {
        if(!isdigit(y[i]))
        {
            flag=1;
            break;
         }
    }

    if(flag==1)
       return(false);
    else
       return(true);
}

/***********************************************************************
FUNCTION :: TO DO TYPE CHECKING WHETHER VALUE IS DOUBLE OR NOT
************************************************************************/

checkifdouble(char *y)
{
    int g; 
    int flag=0;
    int n=strlen(y);

    for(g=0;g<n;g++)
    {
       
      if(y[g]=='.')
      { 
           continue;    /* do nothing*/
      }

      if(!isdigit(y[g]))
       {
           flag=1;
       } 
    }

    if(flag==0)
      return(true);
    else
      return(false);
}

/***********************************************************************
FUNCTION :: TO DO TYPE CHECKING WHETHER VALUE IS STRING OR NOT
************************************************************************/

checkifstring(char *y)
{
    int d,flag=0;
    int n=strlen(y);
    for(d=0;d<n;d++)
    {
       if(!isalpha(y[d]))
       {
          flag=1;
          break;
       }
     }
    if(flag==1)
    {   return(false);
    }
    else
    {   return(true);
    } 
}

/*************************************************************************
FUNCTION :: IT GETS THE TABLE NAME TO BE CREATED FROM THE YACC(parser)
            AND CREATES THE TABLE
**************************************************************************/
void tablefunc(yytext)
{   
  
  if(flagsel==0&&delet==0)
 {
  int e=0,flagd=0;
  char *rt,*tab;
  rt=malloc(MAXN);
  tab=malloc(MAXN);
  strcpy(tname,(char*)yytext);  
   
      
       
    if(flg==0)
    {
        
        check_if_table_already_exist(tname);
        ftable=fopen("table.txt","a+");
        if(ftable==NULL)
            printf("file not opening\n");    
   
        strcpy(tablename,(char*)yytext);
        strcpy(schema_file_name,tablename);
        strcpy(data_file_name,tablename);
        strcat(schema_file_name,"schema");
        fprintf(ftable,"%s\n",tablename);
        
    }
    if(flg==1)
    { 
         flg=0;
                
         strcpy(tab,(char*)yytext);
         strcpy(tab1,(char*)yytext);
         strcat(tab,"schema");
         ff=fopen(tab,"r");
         if(ff==NULL)
             printf("file cannot be opened\n");
         
         while(fread(&d,sizeof(struct att),1,ff))
         { 
	     if(strcmp(d.n,c.f_key)==0)
             {
	 	flagd=1;
             } 
            
         }
	 fclose(ff);
         if(flagd==0)
         {
             printf("foreign key constraint violated \n");
             exit(0);      
         }
         ftable=fopen("table.txt","r");
         while(fscanf(ftable,"%s",rt)!=EOF)
         {
             if(strcmp(rt,tab1)==0)
             {
                  e=1;
              }
         }
         if(e==0)
         {
              printf("\n\ntable refrenced %s does not exist\n",tname);
              exit(0);   
         }
         if(e==1)
         {
             strcpy(c.ftable,tname);
             fk=fopen(constraints_file,"w");
	     fwrite(&c,sizeof(struct constraints),1,fk);
             fclose(fk);
         } 
         
         
     }
      
   fclose(ftable);
 }
}
/***************************************************************************
FUNCTION :: IT GETS THE TYPE OF THE CURRENT ATTRIBUTE TYPE BEING PARSED BY
             YACC ,IT WRITES IT INTO THE SCHEMA FILE
****************************************************************************/
void attrtype(yytext)
{
    ff = fopen(schema_file_name,"a");
    strcpy(d.t,(char*)yytext);
    fwrite(&d,sizeof(struct att),1,ff);
    ctrattr++;
    fclose(ff);
     
}

/***************************************************************************
FUNCTION :: IT GETS THE TYPE OF THE CURRENT ATTRIBUTE NAME BEING PARSED BY
             YACC ,IT WRITES IT INTO THE SCHEMA FILE              
****************************************************************************/

void attr(yytext)
{  
      if(flagsel==0||updat==0||delet==0)
     {
     char *key,*tn;
     key=malloc(MAXN);    
     tn=malloc(MAXN);
     strcpy(tn,tname);
     strcat(tn,"constraints");
     strcpy(constraints_file,tn);
        
     if(flagp==0&&flag==0)
     {
        strcpy(d.n,(char*)yytext);
     }
    
     if(flagp==1&&flag==0)
     {
        int j,f=0;
        strcpy(c.p_key,(char*)yytext);
         strcpy(tab2,tname);
         strcat(tab2,"schema");
         ff=fopen(tab2,"r");
         if(ff==NULL)
             printf("file cannot be opened \n");
              
         
         while(fread(&d,sizeof(struct att),1,ff))
         { 
	        if(strcmp(d.n,c.p_key)==0)
                {
	 	    f=1;
                } 
            
         }
	 fclose(ff);
         if(f==0)
         {
             printf("primary key constraint violated \n");
             exit(0);      
         }     
         if(f==1)
         {
                     
             fk=fopen(constraints_file,"w");
             fwrite(&c,sizeof(struct constraints),1,fk);
             fclose(fk);
         
         }
       flagp=0;
    }  

    if(flagp==0&&flag==1)
    {  
         int j,k,f=0;
         strcpy(c.f_key,(char*)yytext);
         flag=0;
    }
  }
}
/***************************************************************************
FUNCTION :: TO SIGNIFY THAT THE FOREIGN TABLE IS BEING REFERENCED IN CURRENT
            QUERY
***************************************************************************/
void ref()
{
    flg=1;
}

/***************************************************************************
FUNCTION :: TO PRINT THE DATA FILE
****************************************************************************/
void print_file()
{
    char ch; 
    fd=fopen("output","r");
    while(!feof(fd))
    {  
         ch=getc(fd);
         putchar(ch);
    }

}

/**************************************************************************
FUNCTION ::IT GETS THE RELATION NAME FROM THE PARSER TO BE DESCRIBED ON THE 
          SCREEN AND WRITES THE FORMATTED DATA ONTO THE SCREEN BY EXRACTING 
           DATA FROM THE RELATION DATA FILE 
***************************************************************************/
void describe_table(yytext)
{
    int n=0,m=0,i,j;
    char *p1,*p2;
    strcpy(tmp1,(char*)yytext);
    p1=&tmp1[0];
    p2=&tmp2[0];
    for(i=0;i<9;i++)
        p1++;
    while(*p1!='\0')
    {
        *p2=*p1;
        p2++;
        p1++;
    }
    *p2='\0';
        
    check_if_table_does_not_exist(tmp2);
    strcpy(data_file_name,tmp2);
    n=count_no_of_structs_in_datafile();
    
    strcat(tmp2,"schema\0");
    strcpy(schema_file_name,tmp2);
    
    m=count_no_of_structs_in_schema();
    fp=fopen("output","w");
    fflush(fp);
    fclose(fp);   
    fp=fopen("output","a+");
    fprintf(fp,"\n--------------------------------------------\n");
    ff=fopen(schema_file_name,"r");
    for(i=0;i<m;i++)
    {
        fread(&d,sizeof(struct att),1,ff);
        fprintf(fp,"     %s      ",&d.n);
    } 
   fclose(ff);
   fprintf(fp,"\n--------------------------------------------\n");
  
   fclose(fp);
   fp=fopen("output","a+");
   fd=fopen(data_file_name,"r");
   if(fd==NULL)
   {    
       printf("file could not be opened\n");
   }
   for(i=0;i<(n/m);i++)
   {
       for(j=0;j<m;j++)
       {
           fread(&a[j],sizeof(struct attribute),1,fd);
           if((strcmp(a[j].type,"number"))==0)
           {
                fprintf(fp,"    %d    ",atoi(a[j].values));
           }
           if((strcmp(a[j].type,"double"))==0)
           {
                fprintf(fp,"    %f    ",atof(a[j].values));
           }
            if((strcmp(a[j].type,"varchar2"))==0)
           {
                fprintf(fp,"    %s    ",a[j].values);
           }
           
       }
     fprintf(fp,"\n-------------------------------------------------\n");
   }   
   fclose(fd);
   fclose(fp);
   print_file();

   
}


void describe_table1(yytext)
{
    //check_if_table_does_not_exist(yytext);
    int n=0,m=0,i,j;
    char tempf[MAXN];
    strcpy(data_file_name,(char*)yytext);
    strcpy(tempf,data_file_name);
    n=count_no_of_structs_in_datafile();
    
    strcat(tempf,"schema\0");
    strcpy(schema_file_name,tempf);
    
    m=count_no_of_structs_in_schema();
    fp=fopen("output","w");
    fflush(fp);
    fclose(fp);   
    fp=fopen("output","a+");
    fprintf(fp,"\n--------------------------------------------\n");
    ff=fopen(schema_file_name,"r");
    for(i=0;i<m;i++)
    {
        fread(&d,sizeof(struct att),1,ff);
        fprintf(fp,"     %s      ",&d.n);
    } 
   fclose(ff);
   fprintf(fp,"\n--------------------------------------------\n");
  
   fclose(fp);
   fp=fopen("output","a+");
   fd=fopen(data_file_name,"r");
   if(fd==NULL)
   {    
       printf("file could not be opened\n");
   }
   for(i=0;i<(n/m);i++)
   {
       for(j=0;j<m;j++)
       {
           fread(&a[j],sizeof(struct attribute),1,fd);
           if((strcmp(a[j].type,"number"))==0)
           {
                fprintf(fp,"    %d    ",atoi(a[j].values));
           }
           if((strcmp(a[j].type,"double"))==0)
           {
                fprintf(fp,"    %f    ",atof(a[j].values));
           }
            if((strcmp(a[j].type,"varchar2"))==0)
           {
                fprintf(fp,"    %s    ",a[j].values);
           }
           
       }
     fprintf(fp,"\n-------------------------------------------------\n");
   }   
   fclose(fd);
   fclose(fp);
   print_file();

   
}
