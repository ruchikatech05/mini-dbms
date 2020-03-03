/********************************************************************
           PROGRAM TO IMPLEMENT DATABASE MANAGEMENT SYSTEM


FILE 6 :: update.h


DESCRIPTION :: 
It contains all the functions for handling the 
actions performed by the parser on getting the command of selection
******************************************************************/

/***************************************
    GLOBAL VARIABLES DECLARATION
****************************************/

char oldvalue[MAXN],newvalue[MAXN],delvalue[MAXN];
char updatetable[MAXN],delwhereattribute[MAXN],delattribute[MAXN];
char updateattribute[MAXN],updateoper[MAXN],deltable[MAXN],deloper[MAXN];
char extraoper[MAXN],updatewhereatt[MAXN];
int flagequal=0,extraflag=0,flagequal1=0,typeflag=0,y,ct,m;
static int ctr=1,k,j,flag1;

/***************************************************************
FUNCTION :: TO TAKE THE TABLE NAME AS INPUT AND STORE IT
****************************************************************/

void update(yytext)
{
  int i,j;
  char temp[MAXN];
  
  strcpy(temp,(char*)yytext);
  for(i=0,j=7;j<strlen(temp);i++,j++)
  {
      updatetable[i]=temp[j];
  } 
  
}
/*******************************************************************
FUNCTION :: TO SET THE FLAG WHEN UPDATE COMMAND IS PRESENT
********************************************************************/

void updateflag()
{
   updat=1;
}

/*******************************************************************
FUNCTION :: TO SET THE FLAG WHEN DELETE COMMAND IS PRESENT
********************************************************************/

void delete1()
{
  delet=1;
}

/*************************************************************
FUNCTION :: TO COPY THE NAME OF ATTRIBUTE TO BE UPDATED
**************************************************************/

void updateattr(yytext)
{
   
   if(updat==1)
   { 
      if(whereupdate==0)
          strcpy(updateattribute,(char*)yytext);
      else
          strcpy(updatewhereatt,(char*)yytext);
 
   }
  else 
  {
     
         strcpy(delattribute,(char*)yytext);
     
  }
}

/*************************************************************
FUNCTION :: TO CHECK WHETHER IT IS UPDATE COMMAND OR 
DELETE COMMAND
**************************************************************/
void updateq()
{
   if(updat==1)
   {   
        flagequal=1;
   }
  if(delet==1)
  {
       flagequal1=1;
 
  }
}

/*************************************************************
FUNCTION :: TO COPY THE OPERATOR IN UPDATE COMMAND TO UPDATEOPR ARRAY
**************************************************************/

void updateope(yytext)
{   
    if(updat==1)
    {
         extraflag=1;
         strcpy(updateoper,(char*)yytext);
         
    }
}

/******************************************************************
FUNCTION :: TO CHECK WHETHER THE VALUE WE ARE GETTING IS AFTER UPDATE COMMAND OR AFTER DELETE COMMAND & COPY IT
******************************************************************/
void value(yytext)
{
   if(updat==1)
   {
     if(ctr==1) 
     {
         strcpy(newvalue,(char*)yytext);
         
     }
     if(ctr==2)
     {
         strcpy(oldvalue,(char*)yytext);
        
     }
     ctr++;
   }
   if(delet==1)
   {
     strcpy(delvalue,(char*)yytext);
    
   }
} 

/*************************************************************
FUNCTION :: TO CHECK WHETHER WHERE CLAUSE IS PRESENT IN UPDATE COMMAND OR NOT
**************************************************************/

void updatwhere()
{
  
  if(delet==1)
  wheredelflag=1;
}

/****************************************************************
FUNCTION :: TO COPY THE OPERATOR IN EXTRAOPER OR DELOPER ACCORDING TO VALUE OF FLAGS.
****************************************************************/

void updatope(yytext)
{ 
   if(updat==1)
    {   
        strcpy(extraoper,(char*)yytext);
        
    }
   
   if(delet==1)
   {
        strcpy(deloper,(char*)yytext);
       
   }

}
/*************************************************************
FUNCTION :: TO COPY THE TABLE NAME TO DELTABLE WHICH HAS TO BE DELETED
**************************************************************/

void tabldel(yytext)
{

  if(delet==1)
  {
      
      strcpy(deltable,(char*)yytext);
  }
}

/***************************************************************
FUNCTION :: TO SET THE NEWVALUE FOR OLDVALUE ACCORDING
 TO OPERATORS
****************************************************************/

void setthevalue()
{
    int tp=0;
   
    if(strcmp(updateoper,"+")==0)
    {
        
       if(strcmp(a[k].type,"number")==0) 
           tp=atoi(a[k].values)+atoi(newvalue);
       if(strcmp(a[k].type,"double")==0) 
           tp=atof(a[k].values)+atof(newvalue);
              
       snprintf(a[k].values,MAXN,"%d",tp);                
       
    }
    //when to set operator is -
    else if(strcmp(updateoper,"-")==0)
    {
        
       if(strcmp(a[k].type,"number")==0) 
           tp=atoi(a[k].values)-atoi(newvalue);
       if(strcmp(a[k].type,"double")==0) 
           tp=atof(a[k].values)-atof(newvalue);
       
       snprintf(a[k].values,MAXN,"%d",tp);                
       
    }

    //when to set operator is *
    else if(strcmp(updateoper,"*")==0)
    {  
       if(strcmp(a[k].type,"number")==0) 
           tp=atoi(a[k].values)*atoi(newvalue);
       if(strcmp(a[k].type,"double")==0) 
           tp=atof(a[k].values)*atof(newvalue);
        
       snprintf(a[k].values,MAXN,"%d",tp);                

    }

    //when to set operator is /
    else if(strcmp(updateoper,"/")==0)
    {
        
       if(strcmp(a[k].type,"number")==0) 
           tp=atoi(a[k].values)/atoi(newvalue);
       if(strcmp(a[k].type,"double")==0) 
           tp=atof(a[k].values)/atof(newvalue);
       
       snprintf(a[k].values,MAXN,"%d",tp);                

    }



    //when to set operator is %
    else if(strcmp(updateoper,"%")==0)
    {
       if(strcmp(a[k].type,"double")==0)
       {    
           printf("ERROR : DOUBLE CANNOT BE USED WITH % OPERATION\n");
           exit(0);
       }
  
       tp=atoi(a[k].values)%atoi(newvalue);
       snprintf(a[k].values,MAXN,"%d",tp);                

    }

    //when to set operator is =
    else
    {
         
       
        snprintf(a[k].values,MAXN,"%d",atoi(newvalue));
    }
    




}

/*************************************************************
FUNCTION :: TO UPDATE THE VALUE WHEN THERE IS NO WHERE CONDITION
**************************************************************/

void do_update_without_where()
{
     
    int i;
    fd=fopen(updatetable,"r+w");
    fseek(fd,0,SEEK_SET);
    
    for(k=0;k<ct;k++)
    {
        fread(&a[k],sizeof(struct attribute),1,fd);
        
         if(strcmp(a[k].name,updateattribute)==0)
                 setthevalue();   

        
        fseek(fd,-(sizeof(struct attribute)),SEEK_CUR);
        
            fwrite(&a[k],sizeof(struct attribute),1,fd);
     

    }
    

  fclose(fd);

}

/*******************************************************************
FUNCTION :: TO CHECK WHETHER WE ARE GETTING STRING OR NOT
 *******************************************************************/

void check_if_string()
{
   
    int x,f,y;
    
    char hj[MAXN],sd[MAXN],hj1[MAXN],sd1[MAXN];
    strcpy(sd1,oldvalue);
    strcpy(sd,delvalue);
  
    if(oldvalue[0]=='\''||delvalue[0]=='\'')
    { 
        
  
         flag1=1;
         
         y=strlen(oldvalue);
         x=strlen(delvalue);
         strcpy(sd,delvalue);
         strcpy(sd1,oldvalue);
         for(f=1;f<x;f++)
         {
             hj[f-1]=sd[f];
         }
         hj[x-2]='\0';
         for(f=1;f<y;f++)
         {
             hj1[f-1]=sd1[f];
         }
         hj1[y-2]='\0';
         strcpy(delvalue,hj);
         strcpy(oldvalue,hj1);
      

    }


}

/*************************************************************
FUNCTION :: TO UPDATE THE VALUE WHEN WHERE CLAUSE IS PRESENT
**************************************************************/

void do_the_update()
{
    
    int i=0,tmp,tp=0,flag2=0;
    char temp[MAXN];
    
    check_if_string();
    
   
    
    if((strcmp(extraoper,"<>")==0)||(strcmp(extraoper,">")==0)||
       (strcmp(extraoper,"<")==0)||(strcmp(extraoper,">=")==0)||
       (strcmp(extraoper,"<=")==0))
    {
        flagequal=0;
    }
    strcpy(temp,updatetable);
    strcat(temp,"schema");
    strcpy(schema_file_name,temp);
    m=count_no_of_structs_in_schema();
    
    fd=fopen(updatetable,"a");
    if(fd==NULL)
        printf("file not opened\n");
    
    y=ftell(fd);
   
    ct=y/sizeof(struct attribute);
   
    fclose(fd);
    
    if(whereupdate==0)
    {    do_update_without_where();
         exit(0);
    }
    

    fd=fopen(updatetable,"r+w");
    fseek(fd,0,SEEK_SET);
    
    for(i=0;i<(ct/m);i++)
    {
       
        for(j=0;j<m;j++)
        {   
            fread(&a[j],sizeof(struct attribute),1,fd);
           
        }
    
        for(j=0;j<m;j++)
        {
            if(strcmp(a[j].name,updatewhereatt)==0)
            {
               //when where operator is =
               
               if(strcmp(extraoper,"=")==0)
               {   
                
                   
                   if(strcmp(a[j].values,oldvalue)==0)
                   {   for(k=0;k<m;k++)
                       {  
                         if(strcmp(a[k].name,updateattribute)==0)
                         {    
                               setthevalue();       
                               continue;
                                
                         }
                         
                      }
                    }
                   
               }
               //when where operator is <>
               if(strcmp(extraoper,"<>")==0)
               {   
                   //check_if_string();
                   if(strcmp(a[j].values,oldvalue)!=0)
                      for(k=0;k<m;k++)
                      {  
                         if(strcmp(a[k].name,updateattribute)==0)
                         {    setthevalue();
                                //break;
                         }
                      }
               }
               //when where operator is >
               if(strcmp(extraoper,">")==0)
               {   //if number
                   
                   if(flag1==1)
                   {
                       printf("ERROR::STRING CANNOT BE USED WITH >\n");
                       exit(0);
                   }
                   if(strcmp(a[j].type,"number")==0)
                   {
                      if(atoi(a[j].values)>atoi(oldvalue))
                      {   
                          for(k=0;k<m;k++)
                          {  
                             if(strcmp(a[k].name,updateattribute)==0)
                             {  
                                setthevalue();
                               
                             }
                          }
                      }
                   }
                   //if double
                   if(strcmp(a[j].type,"double")==0)
                   {
                      if(atof(a[j].values)>atof(oldvalue))
                      {
                          for(k=0;k<m;k++)
                          {  
                             if(strcmp(a[k].name,updateattribute)==0)
                             {    
                                setthevalue();
                                 
                             }
                          }
                      }
                   }

               }
               //when where operator is <
               if(strcmp(extraoper,"<")==0)
               {   //if number
                   
                   if(flag1==1)
                   {
                       printf("ERROR::STRING CANNOT BE USED WITH <\n");
                       exit(0);
                   }
                   if(strcmp(a[j].type,"number")==0)
                   {
                      if(atoi(a[j].values)<atoi(oldvalue))
                      {
                          for(k=0;k<m;k++)
                          {  
                             if(strcmp(a[k].name,updateattribute)==0)
                             {    
                                setthevalue();
                                 
                             }
                          }
                      }
                   }
                   //if double
                   if(strcmp(a[j].type,"double")==0)
                   {
                      if(atof(a[j].values)<atof(oldvalue))
                      {
                          for(k=0;k<m;k++)
                          {  
                             if(strcmp(a[k].name,updateattribute)==0)
                             {    
                                setthevalue();
                                 
                             }
                          }
                      }
                   }

               }
                  //when where operator is >=
                 
                   if(strcmp(extraoper,">=")==0)
                   {   //if number
                       if(flag1==1)
                       {
                           printf("ERROR::STRING CANNOT BE USED WITH >=\n");
                           exit(0);
                       }
                       if(strcmp(a[j].type,"number")==0)
                       {
                          if(atoi(a[j].values)>=atoi(oldvalue))
                          {
                              for(k=0;k<m;k++)
                              {   
                                 if(strcmp(a[k].name,updateattribute)==0)
                                 {    
                                    setthevalue();
                               
                                 }
                              }
                          }
                       }
                   //if double
                   if(strcmp(a[j].type,"double")==0)
                   {  
                      if(atof(a[j].values)>=atof(oldvalue))
                      {
                          for(k=0;k<m;k++)
                          {  

                             if(strcmp(a[k].name,updateattribute)==0)
                             {  
                                setthevalue();
                                 
                             }
                          }
                      }
                   }

               }
                //when where operator is <=
 
               if(strcmp(extraoper,"<=")==0)
               {   //if number
                   
                   if(flag1==1)
                   {
                       printf("ERROR::STRING CANNOT BE USED WITH <=\n");
                       exit(0);
                   }
                   if(strcmp(a[j].type,"number")==0)
                   {
                      if(atoi(a[j].values)<=atoi(oldvalue))
                      {
                          for(k=0;k<m;k++)
                          {  
                             if(strcmp(a[k].name,updateattribute)==0)
                             {   
                                setthevalue();
                                
                             }
                          }
                      }
                   }
                   //if double
                   if(strcmp(a[j].type,"double")==0)
                   {  
                      if(atof(a[j].values)<=atof(oldvalue))
                      {
                          for(k=0;k<m;k++)
                          {  
                             if(strcmp(a[k].name,updateattribute)==0)
                             {  
                                setthevalue();
                                
                             }
                          }
                      }
                   }

               }
                
           }
                 

        }
        
        fseek(fd,-(sizeof(struct attribute)*m),SEEK_CUR);
        
        for(k=0;k<m;k++)
        {    
            fwrite(&a[k],sizeof(struct attribute),1,fd);
        }

    }
    


    fclose(fd);
}

/*******************************************************************
FUNCTION :: TO CHECK WHETHER GIVEN NUMBER IS DOUBLE OR NOT
********************************************************************/

check_if_double_or_number()
{
    if(strcmp(a[j].type,"number")==0)
        typeflag=1;
    else
        typeflag=2;



}

/*************************************************************
FUNCTION :: TO PERFORM DELETION OPERATION
**************************************************************/

void do_the_delete()
{
      
        
    int y=0,ct=0,i,k,l,flag=0,p,x,f=0,y1,ct1,y2,ct2;
    char temp[MAXN] ;
   
    check_if_string();
    
    strcpy(temp,deltable);
    strcat(temp,"schema");
    strcpy(schema_file_name,temp);
    
    m=count_no_of_structs_in_schema();
    

    fd=fopen(deltable,"a");
    y=ftell(fd);
    ct=y/sizeof(struct attribute);
   
    fclose(fd);
    
    
    fd=fopen(deltable,"r");
    fd1=fopen("temp","w");
    
    if(fd==NULL)
    printf("file could not open\n");
    
    for(i=0;i<ct/m;i++)
    {   
        for(j=0;j<m;j++)
        {
          fread(&a[j],sizeof(struct attribute),1,fd);  
          
        }
        for(j=0;j<m;j++)
        {   
            if(strcmp(a[j].name,delattribute)==0)
            {
                //when operator is =
                if(strcmp(deloper,"=")==0)
                {  
                    
                    
                    if(strcmp(a[j].values,delvalue)==0)
                    {
                        flag=1;  
                        
	 	    }
                } 
                //when operator is >
                if(strcmp(deloper,">")==0)
                {   
                    if(flag1==1)
                    { flag1=0;
                      printf("ERROR :: STRING CANNOT BE USED WITH > OPER\n");
                      exit(0);
                    }
                    
                   
                    check_if_double_or_number();
                    if(typeflag==1)
                    {
                       if(atoi(a[j].values)>atoi(delvalue))
                           flag=1;

                    }
                    if(typeflag==2)
                    {
                        if(atof(a[j].values)>atof(delvalue))
                           flag=1;
                    }
                    
                }
                //when operator is <
                if(strcmp(deloper,"<")==0)
                {   
                    if(flag1==1)
                    { flag1=0;
                      printf("ERROR :: STRING CANNOT BE USED WITH > OPER\n");
                      exit(0);
                    }
                    
                  
                    check_if_double_or_number();
                    if(typeflag==1)
                    {
                       if(atoi(a[j].values)<atoi(delvalue))
                           flag=1;

                    }
                    if(typeflag==2)
                    {
                        if(atof(a[j].values)<atof(delvalue))
                           flag=1;
                    }
                    
                }
                //when operator is >=
                if(strcmp(deloper,">=")==0)
                {   //check_if_string();
                    if(flag1==1)
                    { flag1=0;
                      printf("ERROR :: STRING CANNOT BE USED WITH > OPER\n");
                      exit(0);
                    }
                    
                   
                    check_if_double_or_number();
                    if(typeflag==1)
                    {
                       if(atoi(a[j].values)>=atoi(delvalue))
                           flag=1;

                    }
                    if(typeflag==2)
                    {
                        if(atof(a[j].values)>=atof(delvalue))
                           flag=1;
                    }
                }
              
             
           //when operator is <=
             if(strcmp(deloper,"<=")==0)
             {   
                 if(flag1==1)
                 {    flag1=0;
                      printf("ERROR :: STRING CANNOT BE USED WITH > OPER\n");
                      exit(0);
                 }
                    
               
                 check_if_double_or_number();
                 if(typeflag==1)
                 {
                    if(atoi(a[j].values)<=atoi(delvalue))
                        flag=1;
                 }
                 if(typeflag==2)
                 {
                    if(atof(a[j].values)<=atof(delvalue))
                        flag=1;
                 }
                    
             }

             //when operator is <>
             if(strcmp(deloper,"<>")==0)
             {   
                 if(strcmp(a[j].values,delvalue)!=0)
                 {
                      flag=1;  
                   
	 			 }
             }

        
          }
        }
              


        
        if(flag==0)
        {   
            for(j=0;j<m;j++)
               fwrite(&a[j],sizeof(struct attribute),1,fd1);
        }
        if(flag==1)
        {  
           
          
           flag=0; 
        }
        
        
    }
    
    fclose(fd);
    fclose(fd1);
    //copy file back to tablename from temp
    fd=fopen(deltable,"w");
    fflush(fd);
    fd1=fopen("temp","r");
    fseek(fd1,0,SEEK_END);
    y1=ftell(fd1);
    ct1=y1/sizeof(struct attribute);
    
    fseek(fd1,0,SEEK_SET);
    for(k=0;k<ct1;k++)
    {
       fread(&s,sizeof(struct attribute),1,fd1);
       fwrite(&s,sizeof(struct attribute),1,fd);
       
   }
 
    
    fclose(fd);
    fclose(fd1);
    //copy file
    

}      
            

