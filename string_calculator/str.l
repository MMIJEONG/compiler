%{
/* LEX source for calculator program */
#include <string.h>
#include "str.h"
#define MAXSYM	100
#define	MAXSYMLEN	20
char symtbl[MAXSYM][MAXSYMLEN];
int insertsym();
int maxsym=0;
char s[30];
int yywrap() {return(0);}
%}
letter	   [A-Za-z]  
id         {letter}({letter}|{digit})*
digit      [0-9] 
%%
[ \t]      ; /* ignore blanks and tabs */
{digit}+   {yylval = atoi(yytext); return(NUM);}
{id}       {strncpy(s, yytext, yyleng); s[yyleng]='\0'; yylval=insertsym(s); return(ID);}
\n|.       return yytext[0];  /* return everything else */
%%

int insertsym(s)
char *s;
{
int i;

	for(i=0;i<maxsym; i++) {
		if(strcmp(s, symtbl[i])==0) return(i);
		}
	if (i<MAXSYM-1) {
		strcpy(symtbl[maxsym],s);
		maxsym++;
		return(maxsym-1);
		}
	else
		{printf("symbol table overflow\n");}
	return(0);
}