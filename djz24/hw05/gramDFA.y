/*******************************************************************************
*
* FILE:		gramDFA.y
*
* DESC:		EECS 337 Assignment 5
*
* AUTHOR:	caseid
*
* DATE:		October 1, 2013
*
* EDIT HISTORY:	
*
*******************************************************************************/
%{

#include	"yystype.h"

%}

%start line

%%

// DFA 
line		: A0 '\n'
		| line A0 '\n'
    | error '\n' { yysync(); yyerrok; }
		;
A0		: aletter A0
		| bletter A0
		| /* empty */ { printf( "DFA A0: accept\n"); }
		;
aletter		: 'a'
		;
bletter		: 'b'
		;

%%

void	yyerror( char *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", data.column, "^", data.column, s);
}
