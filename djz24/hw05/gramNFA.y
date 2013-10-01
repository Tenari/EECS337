/*******************************************************************************
*
* FILE:		gramNFA.y
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

%start lines

%%

// NFA 
lines  : line
       | lines line
       | error '\n' { yysync(); yyerrok; }
       ;
line   : A0 end '\n'{ printf( "NFA line: accept\n"); }
       | end '\n' { printf( "NFA line: accept\n"); }
       ;
end: aletter bletter aletter
   | bletter bletter aletter
   | aletter bletter bletter
   | bletter bletter bletter
   ;
A0		: aletter A0 
		|  bletter A0	 
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
