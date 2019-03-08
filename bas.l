/*Mohammed-ELKHAIRA*/

%{
	#include <stdlib.h>
	#include <string.h>
	#include "while-lang-types.h"
	void yyerror(char *);
	#include "y.tab.h"
%}


%%


"true" {
	yylval.bval = true;
	return BOOLEANN;
}

"false" {
	yylval.bval = false;
	return BOOLEANN;
}

[-/+*()<=>;\n] {
	return *yytext;
}

"<="	{ 
	return LE; 
}

">="	{ 
	return GE; 
}

"not"	{ 
	return N; 
}

"and"	{ 
	return A; 
}

"or"	{ 
	return O; 
}

"implies"	{ 
	return I; 
}

"skip"	{
	return SKP;
}

":="	{
	return AFF;
}

"if"	{
	return IF;
}

"then"	{
	return THEN;
}

"else"	{
	return ELSE;
}

"while"	{
	return WHL;
}

"do"	{
	return DO;
}

[a-z]+ {
	strcpy(yylval.vname, yytext);
 	return VARIABLE;
}

[0-9]+ {
	yylval.ival = atoi(yytext);
 	return INTEGER;
}


 /* skip whitespace */
[ \t]+		;

 /* anything else is an error */
. yyerror("invalid character");


%%


int yywrap(void) {
	return 1;
}