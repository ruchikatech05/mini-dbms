/********************************************************************
           PROGRAM TO IMPLEMENT DATABASE MANAGEMENT SYSTEM


FILE 4 :: select.h

DESCRIPTION :: 
contains all the functions for handling the actions performed by the parser on getting the command of selection
**********************************************************************/


/***************************************
    GLOBAL VARIABLES DECLARATION
****************************************/
int ct=0,m=0,p=0;
static int flg1,flg2,m1,m2;
char forkey[MAXN],extraattr[MAXN];

/*************************************************************
FUNCTION :: TO MAKE THE SELECTION FILE
**************************************************************/

make_sel_file(char *ta)
{
    int j=0,i=0;
   
    fp=fopen("output","w");
    fflush(fp);
    fclose(fp);   
    fp=fopen("output","a+");
    fprintf(fp,"\n--------------------------------------------\n");
    for(i=0;i<cntr;i++)
    {
        fprintf(fp,"     %s     ",selattr[i].name);
    }    
    fprintf(fp,"\n--------------------------------------------\n");
    fd=fopen(ta,"r");
    if(fd==NULL)
    {    
       printf("file could not be opened\n");
    }
    while(fread(&s,sizeof(struct attribute),1,fd))
    {
        
        if(j==cntr)
        {    fprintf(fp,"\n--------------------------------------------\n");
            j=0;
        }
        if(strcmp(s.name,selattr[j].name)==0)
        {
       
            if((strcmp(s.type,"number"))==0)
           {
                fprintf(fp,"    %d    ",atoi(s.values));
           }
           if((strcmp(s.type,"double"))==0)
           {
                fprintf(fp,"    %f    ",atof(s.values));
           }
            if((strcmp(s.type,"varchar2"))==0)
           {
                fprintf(fp,"    %s    ",s.values);
           }
        j++;
        } 
            
    } 
    fclose(fd); 
    fclose(fp);
    print_file();

 

}
/*************************************************************
FUNCTION :: TO CHECK WHETHER THERE IS AND/OR CONDITION IS PRESENT WITH JOIN OR NOT
**************************************************************/

check_andor_with_join()
{
  static int g;
  int y=0,ct=0,f=0,p,q;
  int i=0,v=0,u=0;
  char ch;
  
   if(all==0)
   {
      
       u=cntr;
   }
   if(all==1)
   {
       fr=fopen("joino","r");
       cntr=m1+m2-1;
       for(i=0;i<cntr;i++)
       {    
           fread(&a[i],sizeof(struct attribute),1,fr);
               strcpy(selattr[i].name,a[i].name);
       }
       u=m1+m2-1;
       fclose(fr);
   } 

  
   fp=fopen("output","w");
   fflush(fp);
 
   fprintf(fp,"\n---------------------------------------------\n");
   
   for(i=0;i<cntr;i++)
   {    
      
       fprintf(fp,"    %s    ",selattr[i].name);
   }
   fprintf(fp,"\n---------------------------------------------\n");
  

   fr=fopen("joino","a");
   y=ftell(fr);
   ct=y/sizeof(struct attribute);
 
   fclose(fr);
  
   fr=fopen("joino","r");
   

   for(f=0;f<ct/(m1+m2-1);f++)
   {
       for(i=0;i<m1+m2-1;i++)
       {
            fread(&a[i],sizeof(struct attribute),1,fr);
       }
       for(v=0;v<cntr;v++)
       {
           for(i=0;i<m1+m2-1;i++)
           {   
               
               if(strcmp(a[i].name,selattr[v].name)==0)
               {
                  
                   fprintf(fp,"    %s    ",a[i].values);
               }
           }

       }             
    
       fprintf(fp,"\n---------------------------------------------\n");
          
   }

    fclose(fr);
    fclose(fp);
         
        //joined file is created   
   
   
         
   if(andflag==1)   
   {
     //there is andfflag set 
    
     //extracting the attribute name
     char *e5=&(*whereattr[2]);
     char *e6=&extraattr[0];
     while(*e5!='.')
     {
        e5++;
     }
     e5++;
     while(*e5!='\0')
     {
        *e6=*e5;
         e6++;
         e5++;

     }
     *e6='\0';
     
     
     
     fp=fopen("output","w");
     fflush(fp);
     fprintf(fp,"\n-----------------------------------------\n");
    
     for(i=0;i<cntr;i++)
     {    
              
                fprintf(fp,"    %s    ",selattr[i].name);
     }
     
     fprintf(fp,"\n-----------------------------------------\n");
     
     fr=fopen("joino","r");
   
     for(f=0;f<ct/(m1+m2-1);f++)
     {    
           for(i=0;i<(m1+m2-1);i++)
           {    
                  fread(&a[i],sizeof(struct attribute),1,fr);
           }
           for(i=0;i<(m1+m2-1);i++)
           {  
               if(strcmp(a[i].name,extraattr)==0)
               {   
                   //for = operator 
                   if(strcmp(whereoper[1],"=")==0)
                   { 
                      if(strcmp(a[i].values,wherevalue[0])==0)
                      {
                         
                      
                        //write the tuple to ouput1 file
                        for(p=0;p<(m1+m2-1);p++)
                        {
                            for(q=0;q<cntr;q++)
                            {
                                if(strcmp(a[p].name,selattr[q].name)==0)
                                {
                                     fprintf(fp,"    %s    ",a[p].values);
                                }
                            }
                        } 
                                   
          fprintf(fp,"\n-----------------------------------------------\n");

                       }
                       
                    }

                       //for <> operator
                    if(strcmp(whereoper[1],"<>")==0)
                    {
                       if(strcmp(a[i].values,wherevalue[0])!=0)
                       {
                           
                           //write the tuple to ouput1 file
                           for(p=0;p<(m1+m2-1);p++)
                           {
                             for(q=0;q<cntr;q++)
                             {
                                if(strcmp(a[p].name,selattr[q].name)==0)
                                {
                                     fprintf(fp,"    %s    ",a[p].values);
                                }
                            }
                           }             
          fprintf(fp,"\n-----------------------------------------------\n");

                        }
                     }
                         
          if(strcmp(a[i].type,"number")==0||strcmp(a[i].type,"double")==0)
          {     
               if(strcmp(whereoper[1],">")==0)
               {
                   if(strcmp(a[i].type,"number")==0)
                   {
                     if(atoi(a[i].values)>atoi(wherevalue[0]))
                     {
                         //write the tuple to ouput1 file
                         for(p=0;p<(m1+m2-1);p++)
                         {
                            for(q=0;q<cntr;q++)
                            {
                                if(strcmp(a[p].name,selattr[q].name)==0)
                                {
                                     fprintf(fp,"    %s    ",a[p].values);
                                }
                            }
                         }            
          fprintf(fp,"\n-----------------------------------------------\n");

                     }
                   }
                   if(strcmp(a[i].type,"double")==0)
                   { 
                    if(atof(a[i].values)>atof(wherevalue[0]))
                    {
                             //write the tuple to ouput1 file
                          for(p=0;p<(m1+m2-1);p++)
                          {
                            for(q=0;q<cntr;q++)
                            {
                                if(strcmp(a[p].name,selattr[q].name)==0)
                                {
                                     fprintf(fp,"    %s    ",a[p].values);
                                }
                            }
                          }          
          fprintf(fp,"\n-----------------------------------------------\n");

                     }
                   }


               }
               
          
            if(strcmp(whereoper[1],"<")==0)
            {

                 if(strcmp(a[i].type,"number")==0)
                 {
                    if(atoi(a[i].values)<atoi(wherevalue[0]))
                    {
                       //write the tuple to ouput1 file
                       for(p=0;p<(m1+m2-1);p++)
                        {
                            for(q=0;q<cntr;q++)
                            {
                                if(strcmp(a[p].name,selattr[q].name)==0)
                                {
                                     fprintf(fp,"    %s    ",a[p].values);
                                }
                            }
                        }          
          fprintf(fp,"\n-----------------------------------------------\n");

                    }
                 }
                 if(strcmp(a[i].type,"double")==0)
                 { 
                    if(atof(a[i].values)<atof(wherevalue[0]))
                    {
                             //write the tuple to ouput1 file
                        for(p=0;p<(m1+m2-1);p++)
                        {
                            for(q=0;q<cntr;q++)
                            {
                                if(strcmp(a[p].name,selattr[q].name)==0)
                                {
                                     fprintf(fp,"    %s    ",a[p].values);
                                }
                            }
                        }           
          fprintf(fp,"\n-----------------------------------------------\n");

                     }
                   }


              }
               
            
            if(strcmp(whereoper[1],">=")==0)
            {
               
                  if(strcmp(a[i].type,"number")==0)
                   { 
                     if(atoi(a[i].values)>=atoi(wherevalue[0]))
                     {   
                         //write the tuple to ouput1 file
                         for(p=0;p<(m1+m2-1);p++)
                         {
                            for(q=0;q<cntr;q++)
                            {
                                if(strcmp(a[p].name,selattr[q].name)==0)
                                {
                                     fprintf(fp,"    %s    ",a[p].values);
                                }
                            }
                         }             
          fprintf(fp,"\n-----------------------------------------------\n");

                     }
                   }
                   if(strcmp(a[i].type,"double")==0)
                   { 
                    if(atof(a[i].values)>=atof(wherevalue[0]))
                    {       
                             //write the tuple to ouput1 file
                             for(p=0;p<(m1+m2-1);p++)
                             { 
                              for(q=0;q<cntr;q++)
                              { 
                   
                                if(strcmp(a[p].name,selattr[q].name)==0)
                                {   
                                     fprintf(fp,"    %s    ",a[p].values);
                                }
                              }
                             }                
          fprintf(fp,"\n-----------------------------------------------\n");

                     }
                   }


                }
                                



            
            if(strcmp(whereoper[1],"<=")==0)
            {

                if(strcmp(a[i].type,"number")==0)
                {
                     if(atoi(a[i].values)<=atoi(wherevalue[0]))
                     {
                         //write the tuple to ouput1 file
                         for(p=0;p<(m1+m2-1);p++)
                        {
                            for(q=0;q<cntr;q++)
                            {
                                if(strcmp(a[p].name,selattr[q].name)==0)
                                {
                                     fprintf(fp,"    %s    ",a[p].values);
                                }
                            }
                        }         
          fprintf(fp,"\n-----------------------------------------------\n");

                     }
                   }
                   if(strcmp(a[i].type,"double")==0)
                   { 
                    if(atof(a[i].values)<=atof(wherevalue[0]))
                    {
                             //write the tuple to ouput1 file
                            for(p=0;p<(m1+m2-1);p++)
                            {
                                for(q=0;q<cntr;q++)
                                {
                                    if(strcmp(a[p].name,selattr[q].name)==0)
                                    {
                                     fprintf(fp,"    %s    ",a[p].values);
                                    }
                                }
                            }             
          fprintf(fp,"\n-----------------------------------------------\n");

                     }
                   }


                }
               }                
              

         }
      }
    }
   
    fclose(fp);
    fclose(fr);
    

   }
    //copy "output" file to "output1"
    
    print_file(); 
   
    
   
 
}

/*************************************************************
FUNCTION :: TO JOIN 2 TABLES
**************************************************************/

void do_the_join()
{
    static ctr=0,ctr1=1;
    int ct1,ct2,y1,y2,i=0,j=0,k=0,l=0,n=0,p=0;
    FILE *fd1,*fd2;
    char temp1[MAXN],temp2[MAXN];
    fd1=fopen(jointab1,"r");
    fseek(fd1,0,SEEK_END); 
    y1=ftell(fd1);
    ct1=y1/sizeof(struct attribute);
  
    fclose(fd1);
   
    fd2=fopen(jointab2,"r");
    fseek(fd2,0,SEEK_END); 
    y2=ftell(fd2);
    ct2=y2/sizeof(struct attribute);
   
    fclose(fd2);
    
    strcpy(temp1,jointab1);
    
    strcpy(temp2,jointab2);
    strcat(temp1,"schema");
    strcat(temp2,"schema");
   
    strcpy(schema_file_name,temp1);
    m1=count_no_of_structs_in_schema();
    strcpy(schema_file_name,temp2);
    m2=count_no_of_structs_in_schema();
    fr=fopen("joino","w");
    fflush(fr);
    fp=fopen("output","w");
    fflush(fp);
    
    for(i=0;i<cntr;i++)
        fprintf(fp,"    %s    ",selattr[i].name);
    fprintf(fp,"\n--------------------------------------------------\n");
    fclose(fp); 
    
    //read the tuple from first table
    fd1=fopen(jointab1,"r");
    if(fd1==NULL)
        printf("not open\n");
    fd2=fopen(jointab2,"r");
   
    for(l=0;l<ct1/m1;l++)
    {
    
        for(i=0;i<m1;i++)
        { 
            fread(&a[i],sizeof(struct attribute),1,fd1);
        }
        for(i=0;i<m1;i++)
        {
           if(strcmp(a[i].name,forkey)==0)
               break;
             
        }  
        for(j=0;j<ct2/m2;j++)
        {
            for(k=0;k<m2;k++)
            {
                fread(&b[k],sizeof(struct attribute),1,fd2);
            
            }
            for(k=0;k<m2;k++)
            {
                if(strcmp(b[k].name,forkey)==0)
                 {
                      if(strcmp(a[i].values,b[k].values)==0)
                      {
                          for(n=0;n<m1;n++)
                          {   
                              fwrite(&a[n],sizeof(struct attribute),1,fr);
                          }
                          for(p=0;p<m2;p++)
                          {  if(strcmp(b[p].name,forkey)!=0)
                             {
                                 
                                 fwrite(&b[p],sizeof(struct attribute),1,fr);
                             }
                          }
                      }
          
                 }
        
             }
              
     }   
        rewind(fd2);
   }
     
   
   fclose(fr); 
  
   check_andor_with_join();
        
    
 


fclose(fd1);
fclose(fd2);

   
}
/*************************************************************
FUNCTION :: TO CHECK WHETHER THE CONSTRAINTS ARE SATISFYING OR NOT FOR JOIN CONDITION
**************************************************************/

void handler2()
{
    
    int i=0;
    char temp1[MAXN];
    char temp2[MAXN];
    
    
   
        
    char *tp1=&(*whereattr[0]);
    char *tp2=&(*whereattr[1]);
    char *e1=&jointab1[0];
    char *e2=&jointab2[0];
    char *e3=&joinattr1[0];
    char *e4=&joinattr2[0];
    while(*tp1!='.')
    {
        *e1=*tp1;
         e1++;
         tp1++;
    } 
    tp1++;
 
    strcpy(temp1,jointab1);
    while(*tp2!='.')
    {
        *e2=*tp2;
         e2++;
         tp2++;
    } 
    tp2++;
    
    while(*tp1!='\0')
    {
        *e3=*tp1;
        e3++;
        tp1++;
    }
    while(*tp2!='\0')
    {
        *e4=*tp2;
        e4++;
        tp2++;
    }
    
   
    
    strcpy(temp2,jointab2);
    strcat(temp1,"constraints");
    strcat(temp2,"constraints");
    fk=fopen(temp1,"r");
    if(fk==NULL)
    {
        printf("\ncannot join since table 1 has no primary constraint\n");
        exit(0);
        
        
    }
    fread(&c,sizeof(struct constraints),1,fk);
    if(strcmp(c.ftable,jointab2)==0)
    {
       
        strcpy(forkey,c.f_key);
        if(strcmp(joinattr2,c.f_key)==0)
        {
            fref=1;
            
        }
    }
    fclose(fk);
    fk=fopen(temp2,"r");
    if(fk==NULL)
    {    printf("cannot open file10\n");
   printf("\ncannot join ,table 2 does not have foreign key constraint\n\n");
        exit(0);
    }
    fread(&c,sizeof(struct constraints),1,fk);
    if(strcmp(c.ftable,jointab1)==0)
    {
       
        strcpy(forkey,c.f_key);
        if(strcmp(joinattr1,c.f_key)==0)
        {
            fref=2;
           
        }
        else
        {
            printf("foreign key referenced is wrong\n");
            exit(0);
        }
        printf("op");
    }
    else
    {
        printf("table referenced is worng\n");
        exit(0);
    }
    
    fclose(fk);
    
    //now do the join
   
  
    if(all==1)
    {
        
        fd1=fopen(jointab1,"r");
        if(fd1==NULL)
        {
            printf("file not opened");
        } 
        for(i=0;i<m1;i++)
        {
            fread(&s1,sizeof(struct attribute),1,fd1);
            strcpy(selattr[i].name,s1.name);
        }
               
        fclose(fd1);
        
        fd2=fopen(jointab2,"r");
        if(fd==NULL)
        {
            printf("file not opened");
        }
        for(i=m1;i<m1+m2;i++)
        { 
            fread(&s2,sizeof(struct attribute),1,fd2);
            strcpy(selattr[i].name,s2.name);
        }
        fclose(fd2);
        cntr=m1+m2;


    }
    
     


    do_the_join();
    
}

/*************************************************************
FUNCTION :: TO PRINT THE VALUE IN OUTPUT FILE WHEN THERE IS WHERE CONDITION WITH AND & OR 
**************************************************************/
void handler1with_and_or()
{
    int b=0;
    int i,z=0;
    
    fflush(fp);
    
    fd=fopen(seltab1,"r");
    if(fd==NULL)
    printf(" file cannot be opened");
    for(q=0;q<(ct/m);q++)
    {      
        for(p=0;p<m;p++)
        {
             fread(&a[p],sizeof(struct attribute),1,fd);
        }
        for(p=0;p<m;p++)
        {
           
           if(strcmp(a[p].name,whereattr[0])==0)
           {    
                 if(strcmp(whereoper[0],"=")==0)
                 {
                    if(strcmp(wherevalue[0],a[p].values)==0)
                         flg1=1;    
                  
                 }

                 if(strcmp(whereoper[0],"<>")==0)
                 {
                          
                           if(strcmp(wherevalue[0],a[p].values)!=0)
                               flg1=1;    
                     }
            if(strcmp(a[p].type,"number")==0 ||strcmp(a[p].type,"double")==0)
            {
                     if(strcmp(whereoper[0],">")==0)
                     {
                          
                           if(strcmp(a[p].type,"number")==0)
                           {    if(atoi(a[p].values)>atoi(wherevalue[0]))
                                   flg1=1;
                           }
                           else
                           {    if(atof(a[p].values)>atof(wherevalue[0]))
                                   flg1=1;
                           }
                     }
                     if(strcmp(whereoper[0],"<")==0)
                     {
                           if(strcmp(a[p].type,"number")==0)
                           {    if(atoi(a[p].values)<atoi(wherevalue[0]))
                                   flg1=1;
                           }
                           else
                           {    if(atof(a[p].values)<atof(wherevalue[0]))
                                   flg1=1;
                           }
                     }
                     if(strcmp(whereoper[0],"<=")==0)
                     {
                           if(strcmp(a[p].type,"number")==0)
                               if(atoi(a[p].values)<=atoi(wherevalue[0]))
                                   flg1=1;
                           else
                               if(atof(a[p].values)<=atof(wherevalue[0]))
                                   flg1=1;    
                     }
                     if(strcmp(whereoper[0],">=")==0)
                     {
                           if(strcmp(a[p].type,"number")==0)
                               if(atoi(a[p].values)>=atoi(wherevalue[0]))
                                   flg1=1;
                           else
                               if(atof(a[p].values)>=atof(wherevalue[0]))
                                   flg1=1;    
                     }
                  }

             }
             //second condition
             if(strcmp(a[p].name,whereattr[1])==0)
             {
                 if(strcmp(whereoper[1],"=")==0)
                 {
                    if(strcmp(wherevalue[1],a[p].values)==0)
                         flg2=1;

                 }
                 if(strcmp(whereoper[1],"<>")==0)
                     {
                         
                           if(strcmp(wherevalue[1],a[p].values)!=0)
                               flg2=1;    
                     }
            if(strcmp(a[p].type,"number")==0 ||strcmp(a[p].type,"double")==0)
                 {
                     if(strcmp(whereoper[1],">")==0)
                     {
                           
                           if(strcmp(a[p].type,"number")==0)
                           {    if(atoi(a[p].values)>atoi(wherevalue[1]))
                                   flg2=1;
                           }
                           else
                           {    if(atof(a[p].values)>atof(wherevalue[1]))
                                   flg2=1;
                           }
                     }
                     if(strcmp(whereoper[1],"<")==0)
                     {
                           if(strcmp(a[p].type,"number")==0)
                           {    if(atoi(a[p].values)<atoi(wherevalue[1]))
                                   flg2=1;
                           }
                           else
                           {    if(atof(a[p].values)<atof(wherevalue[1]))
                                   flg2=1;
                           }
                     }
                     if(strcmp(whereoper[1],"<=")==0)
                     {
                           if(strcmp(a[p].type,"number")==0)
                               if(atoi(a[p].values)<=atoi(wherevalue[1]))
                                   flg2=1;
                           else
                               if(atof(a[p].values)<=atof(wherevalue[1]))
                                   flg2=1;    
                     }
                     if(strcmp(whereoper[1],">=")==0)
                     {
                           if(strcmp(a[p].type,"number")==0)
                               if(atoi(a[p].values)>=atoi(wherevalue[1]))
                                   flg2=1;
                           else
                               if(atof(a[p].values)>=atof(wherevalue[1]))
                                   flg2=1;    
                     }
                  }
           
             }

        }
            
        if(andflag==1)
        { 
              
              if(flg1==1&&flg2==1)
              {
                  
                  for(z=0;z<cntr;z++)
                  {   
                     
                      
                      for(b=0;b<m;b++)
                      {
                         if(strcmp(a[b].name,selattr[z].name)==0)
                         {
                              fprintf(fp,"    %s    ",a[b].values);
                         }
                     }
                  }
             fprintf(fp,"\n--------------------------------------------\n");
                  flg1=0;
                  flg2=0; 
               }
               flg1=0;
               flg2=0;
         }
         if(orflag==1)
         {
              if(flg1==1||flg2==1)
              {
                  
                  for(z=0;z<cntr;z++)
                  {   
                     
                     for(b=0;b<m;b++)
                     {
                         if(strcmp(a[b].name,selattr[z].name)==0)
                         {
                              fprintf(fp,"    %s    ",a[b].values);
                         }
                     }
                 }
              fprintf(fp,"\n--------------------------------------------\n");
                  flg1=0;
                  flg2=0; 
               }
               flg1=0;
               flg2=0;
          }
          flg1=0;
          flg2=0;
      }
}       
/*************************************************************
FUNCTION :: TO PRINT THE NAMES OF ATTRIBUTES ,OPERATORS, VALUES IN OUTPUT FILE
**************************************************************/
   
void handler1()
{
    
    double val1,val2;
    int q=0,d=0,r=0,y=0,x=0,z=0,n,c=0,i=0;
    char tmp[MAXN];
    char *tp=&tmp[0];
    fp=fopen("output","w");
    fflush(fp);
    fclose(fp);   
    fp=fopen("output","a+");
    fprintf(fp,"\n--------------------------------------------\n");
    
    
    strcpy(tmp2,seltab1);
    strcat(tmp2,"schema\0");
    strcpy(schema_file_name,tmp2);
 
    m=count_no_of_structs_in_schema();
    
    
    
        
    fclose(fp);
    if(all==1)
    {
        
        fd=fopen(seltab1,"r");
        if(fd==NULL)
        {
            printf("file no topened");
        } 
        for(i=0;i<m;i++)
        {
            fread(&s,sizeof(struct attribute),1,fd);
            strcpy(selattr[i].name,s.name);
        }
         
         
        cntr=m;
        fclose(fd);
       

    }
    fp=fopen("output","a+");
    for(p=0;p<cntr;p++)
    {
           fprintf(fp,"     %s     ",selattr[p].name);
    }     
    
    fprintf(fp,"\n--------------------------------------------\n");
    
    
    for(p=0;p<h;p++)
    {
        
        char *tp=&tmp[0];
        char *e;  
        
        e=strchr(whereattr[p],'.');
        
        e++;
        while(*e!='\0')
        {
            *tp=*e;
             tp++;
             e++;
        } 
        *tp='\0';
        strcpy(whereattr[p],tmp);
       
        e=NULL;
        strcpy(tmp,"\0");;
   }
    
    
    fd=fopen(seltab1,"r");
    fseek(fd,0,SEEK_END); 
    y=ftell(fd);
    ct=y/sizeof(struct attribute);
   
    fclose(fd);
    
    fd=fopen(seltab1,"r");
    for(q=0;q<(ct/m);q++)
    {    
        
        for(p=0;p<m;p++)
        {
             
             fread(&s,sizeof(struct attribute),1,fd);
             
             for(d=0;d<cntr;d++)
             {
                 if(strcmp(s.name,selattr[d].name)==0)
                 {
                     strcpy(put[q][p].values,s.values);
                
                 }
              
             }            
        }
             
    } 
    fclose(fd);

   
   if(andflag==1||orflag==1)
         handler1with_and_or();
   if(andflag==0&&orflag==0)
   { 

    
        fd=fopen(seltab1,"r");
        if(fd==NULL)
            printf("file could not be opened\n");
       
        rewind(fd);
        for(q=0;q<(ct/m);q++)
        {     
         
          for(p=0;p<m;p++)
          {
              

            fread(&s,sizeof(struct attribute),1,fd);              
          
              if(strcmp(s.name,whereattr[c])==0)
              {
                 
                         //when operator is '='
                         if(strcmp(whereoper[c],"=")==0)
                         {    
                             if(strcmp(s.values,wherevalue[c])==0)
                             {      
                                
                                for(d=0;d<m;d++)
                                {   
                              
                                 fprintf(fp,"    %s    ",put[q][d].values);
                                } 
                                
             fprintf(fp,"\n--------------------------------------------\n");
                                       
                             }
                         }
                         //when operator is '<>'
                         if(strcmp(whereoper[c],"<>")==0)
                         {    
                             if(strcmp(s.values,wherevalue[c])!=0)
                             {      
                                for(d=0;d<m;d++)
                                {   
                                 fprintf(fp,"    %s    ",put[q][d].values);
                                } 
                                
             fprintf(fp,"\n--------------------------------------------\n");
                                       
                             }
                         }

                  if(strcmp(s.type,"number")==0||strcmp(s.type,"double")==0)
                  {
                         
                        if(strcmp(s.type,"number")==0)
                        {    val1=atoi(s.values);
                             val2=atoi(wherevalue[c]);
                        } 
                        if(strcmp(s.type,"double")==0)
                        {    val1=atof(s.values);
                             val2=atof(wherevalue[c]);
                        }

                        //when operator is >
                        if(strcmp(whereoper[c],">")==0)
                         {    
                             
                             if(val1>val2)
                             {      
                                for(d=0;d<m;d++)
                                {   
                                 fprintf(fp,"    %s    ",put[q][d].values);
                                } 
                                
             fprintf(fp,"\n--------------------------------------------\n");
                                       
                             }
                         }
                          //when operator is <
                          if(strcmp(whereoper[c],"<")==0)
                         {    
                             if(val1<val2)
                             {      
                                for(d=0;d<m;d++)
                                {   
                                 fprintf(fp,"    %s    ",put[q][d].values);
                                } 
                                
             fprintf(fp,"\n--------------------------------------------\n");
                                       
                             }
                         }
                         //when operator is '>='
                         if(strcmp(whereoper[c],">=")==0)
                         {    
                             if(val1>=val2)
                             {      
                                for(d=0;d<m;d++)
                                {   
                                 fprintf(fp,"    %s    ",put[q][d].values);
                                } 
                                
             fprintf(fp,"\n--------------------------------------------\n");
                                       
                             }
                         }
                         //when operator is '<='
                         if(strcmp(whereoper[c],"<=")==0)
                         {    
                             if(val1<=val2)
                             {      
                                for(d=0;d<m;d++)
                                {   
                                 fprintf(fp,"    %s    ",put[q][d].values);
                                } 
                                
             fprintf(fp,"\n--------------------------------------------\n");
                                       
                             }
                         }
 
                  }
   
              }

            
   
           }

        
        
    }
    fclose(fd);  
   }  
  
   fclose(fp);
   print_file();
   
}

/*************************************************************
FUNCTION :: TO DO COMPUTATIONS WHEN SELECT HAS ALREADY BEEN ENCOUNTERED
**************************************************************/

void work_after_select()
{
    char tempf[MAXN];
    int i,j;
    
    if(nowhr==1)
    {
        
        strcpy(tempf,seltab1);
        
        if(all==0)
        {
            
            make_sel_file(seltab1);

        }
        else
        {
            describe_table1(seltab1);
            
        }
    
        
        
    }
    else
    {
        
        
        if(joinn==0)
        {
           handler1();
        }
        else
        {
             handler2();
           
         }
        
        
    }

}

/*************************************************************
FUNCTION :: TO SET THE FLAG & EXECUTE WHEN THERE IS NO WHERE CONDITION 
**************************************************************/
void nowhere()
{//if no where this will be set
    nowhr=1;
    work_after_select();
}

/*************************************************************
FUNCTION :: TO INDICATE THAT SELECT CONDITION HAS BEEN FINISHED
**************************************************************/

void selectend()
{// end of select in case of where
    endsel=1;
    work_after_select();
}

/*************************************************************
FUNCTION :: TO SET THE FLAG & EXECUTE WHEN THERE IS WHERE CONDITION
**************************************************************/

void whereclause()
{  if(flagsel==1)
  {
    wflag=1;   
  }
  if(updat==1)
  {
    whereupdate=1;
  }
  if(delet==1)
  {
    wheredelflag=1;
  }
}

/******************************************************************
FUNCTION :: TO SET THE FLAG WHEN SELECTION CONDITION STARTS
*******************************************************************/
void selectflag()
{
    flagsel=1;
}

/*************************************************************
FUNCTION :: TO SET THE FLAG THAT ALL ATTRIBUTES ARE TO BE PRINTED
**************************************************************/

void selectstar()
{  if(flagsel==1)
     all=1;
    
}

/*************************************************************
FUNCTION :: TO COUNT THE NUMBER OF ATTRIBUTES AFTER SELECTION CONDITION
**************************************************************/
void count1()
{
    cntr++;
   
    //these many attributes to be selected

}

void end1()
{
//signals all attributes for selection have been entered
//store cntr
//cntr1=cntr;
}

/********************************************************************
FUNCTION :: TO COPY THE ATTRIBUTE NAME IN ARRAY IF FLAG IS SET
********************************************************************/

void select1(yytext)
{ 
   if(flagsel==1)
   { 
       //printf("value of cntr1 in select1 is %d\n",cntr1);
     
       if(all==0)
       {    
            strcpy(selattr[cntr].name,(char*)yytext);
           
       }
       
      
   } 
}

/***************************************************************
FUNCTION :: TO COPY THE TABLE NAME IN ARRAY IF FLAG IS SET
****************************************************************/

void fromtable(yytext)
{
    if(flagsel==1)
    {
       
       if(joinn==0)
       {
         strcpy(seltab1,(char*)yytext);
         
       }
       else
       {
           
           strcpy(seltab2,(char*)yytext);
           
       }

     
      
       
    }
    
}

/*************************************************************
FUNCTION :: TO CHECK THE FLAG & SEE WHETHER THERE IS JOIN CONDITION OR NOT
**************************************************************/

void joinsignal()
{
    joinn=1;
}
void join(yytext)
{ 
    if(joinn==1)
   {
   //the table in fromtable(yytext) and this table has to be joined
   }

}

/*************************************************************
FUNCTION :: TO COPY THE JOIN ATTRIBUTES IN ARRAY
**************************************************************/

void wheretable(yytext)
{
   
  
   strcpy(whereattr[h],(char*)yytext);
  
   h++;
    //in this we are geting either join attribues if join is called
   //or it can be condition in selection in form tablename.attribute

}

/*******************************************************************
FUNCTION :: TO CHECK WHETHER WE HAVE AND CONDITION OR NOT
********************************************************************/

void and()
{
    
    andflag=1;
    //anding between conditions
}

/******************************************************************
FUNCTION :: TO CHECK WHETHER WE HAVE OR CONDITION OR NOT
*******************************************************************/

void or()
{
   
    orflag=1;
    // oring has to be done
}

/****************************************************************
FUNCTION :: TO COPY THE NUMBER OR STRING  IN ARRAY IF FLAG IS SET
*******************************************************************/

void selectcond(yytext)
{  if(flagsel==1)
  {
   int n=0,f;
   char hj[MAXN],sd[MAXN];
   if(flagsel==1)
   { 
      
       strcpy(wherevalue[q],(char*)yytext);
       if(wherevalue[q][0]=='\'')
       {    
            strcpy(sd,wherevalue[q]);
            n=strlen(sd);
         
            for(f=1;f<n;f++)
            {
                hj[f-1]=sd[f];
            }
            hj[n-2]='\0';
            strcpy(wherevalue[q],hj); 
            
        }
      
       q++; 
   
    // gives number or string after operator in where condition
   // number in numerical form
   // string in '  '
   }
 }
}

/*************************************************************
FUNCTION :: TO COPY THE OPERATOR IN ARRAY IF FLAG IS SET
**************************************************************/

void ope(yytext)
{  if(flagsel==1)
   {
    
    strcpy(whereoper[l],(char*)yytext);
    
    l++;
    //gives operator in where condition
    //it is either < or > or <= or >= or <> or =
   }
}

