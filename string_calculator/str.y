%{
/* YACC source for calculator program */
# include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	 MAXSYM	100
#define	 MAXSYMLEN	20

extern char symtbl[MAXSYM][MAXSYMLEN];
extern int maxsym;

char result[MAXSYM][MAXSYMLEN];
int ch_num=0;

int add(int,int);
int sub(int,int);
int mul(int,int);
%}
%token NUM ID
%left '+' '-'
%left '*'  
%%
comm : comm '\n'
          | lambda
          | comm expr  '\n' {printf("°á°ú: %s\n",result[$2]);}
          | comm error '\n' {yyerrok; printf(" Try again \n");}
          ;
expr : expr '+' expr {$$ = add($1,$3);}
          | expr '-' expr {$$ = sub($1,$3);}
          | expr '*' expr {$$ = mul($1,$3);}          
          | NUM
          | ID
           ;
lambda: /* empty */
             ;
%%
yyerror(s)
char *s;
{
  printf("%s\n",s);
}

main()
{
  return yyparse();
}
int add(int num1,int num2){
	
	char temp[100]="";
	strcpy(temp,symtbl[num1]);
	strcat(temp,symtbl[num2]);
	strcat(temp,"\0");
	if(ch_num==0)
	{
	     strcpy(result[0],temp);
	     ch_num++;
	     return ch_num-1;	
	}
	strcpy(result[ch_num],temp);
	ch_num++;
	return ch_num-1;
}
int sub(int num1,int num2){
	char temp[100]="";
	int j,k;
	 for (j = 0; j < strlen(symtbl[num1]); j++)
            {
               if (symtbl[num1][j] == symtbl[num2][0]){
		 for(k=j;k<strlen(symtbl[num1])-1;k++){
		    symtbl[num1][k]=symtbl[num1][k+1];
		 }
		j--;
		symtbl[num1][k] = '\0';
		}
                  
            }
	strcpy(temp,symtbl[num1]);
	strcat(temp,"\0");
	if(ch_num==0)
	{
	     strcpy(result[0],temp);
	     ch_num++;
	     return ch_num-1;	
	}
	strcpy(result[ch_num],temp);
	ch_num++;
	return ch_num-1;
}
int mul(int num1,int num2){
	char temp[100]="";
	int i;
	for(i=0;i<num2;i++)
	{
	    strcat(temp,symtbl[num1]);	
	}
	strcat(temp,"\0");
	if(ch_num==0)
	{
	     strcpy(result[0],temp);
	     ch_num++;
	     return ch_num-1;	
	}
	strcpy(result[ch_num],temp);
	ch_num++;
	return ch_num-1;
}
