%{
	#include "stdio.h"
	#include "cx.tab.h"

	int line = 1;
	int yywrap();
	void yyerror(char *);
	char msg[100];
	void comment();
%}

whitespace  ([ \t\n])+
ID          [A-Za-z][A-Za-z0-9]*
NUM         ([1-9][0-9]*)|0
CHA         '[A-za-z]'

%%

[ \t]	   {;}
[\n]	   {line++;}

"/*"       {comment();} 
"+"        {return PLUS;}
"-"        {return MINUS;}
"*"        {return TIMES;}
"/"        {return SLASH;}
"<"        {return LES;}
"<="       {return LEQ;}
">"        {return GTR;}
">="       {return GEQ;}
"=="       {return EQL;}
"!="       {return NEQ;}
"="        {return BECOMES;}
"||"       {return OR;}
"&&"       {return AND;}
"!"        {return NOT;}
";"        {return SEMICOLON;}
"("        {return LPAREN;}
")"        {return RPAREN;}
"["        {return LBRACKET;}
"]"        {return RBRACKET;}
"{"        {return LBRACE;}
"}"        {return RBRACE;}
","        {return COMMA;}
"++"	   {return SELFADD;}
"--"	   {return SELFMIUNS;}

"true"	   {return TRUE;}	
"false"	   {return FALSE;}
"if"       {return IF;}
"else"     {return ELSE;}
"while"    {return WHILE;}
"write"    {return WRITE;}
"read"     {return READ;}
"int"      {return INT;}
"bool"     {return BOOL;}
"const"    {return CONST;}
"repeat"   {return REPEAT;}
"until"    {return UNTIL;}
"^"        {return XOR;}
"%"        {return MOD;}
"odd"      {return ODD;}
"call"     {return CALL;}
"do"       {return DO;}
"func"     {return FUNC;}
"exit"     {return EXIT;}
"for"      {return FOR;}
"char"     {return CHAR;}

{ID}  	 	{
				yylval.ident = (char *)malloc(strlen(yytext) + 1);
				strcpy(yylval.ident, yytext);
				return IDENT;
			}

{NUM}   	{
				yylval.number = atoi(yytext);
				return NUMBER;
			}

{CHA} 		{
				yylval.ident = (char *)malloc(strlen(yytext) + 1);
				strcpy(yylval.ident, yytext);
				return CHARACTER;
			}


.       	{
				sprintf(msg, "yyerror: unexpected character %s", yytext);
				yyerror(msg);
			}

%%

void redirectInput(FILE *input) {
	yyin = input;
}

int yywrap() {
    return 1;
}

void comment() {
    char c, c1;
loop:
    while ((c = input()) != '*' && c != 0) {
        if (c == '\n') {line++;}
	}
    if ((c1 = input()) != '/' && c != 0) {
        unput(c1);
        goto loop;
    }
}
