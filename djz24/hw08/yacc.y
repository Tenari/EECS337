/*******************************************************************************
*
* FILE:		yacc.y 
*
* DESC:		EECS 337 Assignment 6
*      		yacc program for the Calculator page 295-296
*
* AUTHOR:	djz24
*
* DATE:		October 8, 2013
*
* EDIT HISTORY:	
   Oct 28 - name change to yacc.y
*
*******************************************************************************/
%{
#include <ctype.h>
#include <stdio.h>
#include "yystype.h"
#include "y.tab.h"
%}

%start lines

%token CONSTANT
%token IDENTIFIER

%left '|'
%left '^'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%right UMINUS '~'/* supplies precedence for unary minus */

%% 	/* beginning of rules section */

lines : lines stmts '\n' 
    {
      /*
      * print the quad list
      */
      print_quad_list( $2.quad);
      /*
      * free the quad list
      */
      free_quad_list( $2.quad);
    }
  | lines error '\n' { yyerror(" reenter previous line: "); yyerrok; }
  | /* empty */
;
stmts : expr 
  | ident '=' expr 
    {
      $$.quad = new_quad3( '=', $1.index, $3.quad);
    }
;
expr	: expr '+' expr	    { $$.quad = new_quad1( '+', $1.quad, $3.quad); }
	| expr '-' expr	        { $$.quad = new_quad1( '-', $1.quad, $3.quad); }
	| expr '*' expr	        { $$.quad = new_quad1( '*', $1.quad, $3.quad); }
	| expr '/' expr	        { $$.quad = new_quad1( '/', $1.quad, $3.quad); }
	| expr '^' expr	        { $$.quad = new_quad1( '^', $1.quad, $3.quad); }
	| expr '&' expr	        { $$.quad = new_quad1( '&', $1.quad, $3.quad); }
	| expr '%' expr	        { $$.quad = new_quad1( '%', $1.quad, $3.quad); }
	| '~' expr	            { $$.quad = new_quad2( '~', $2.quad); }
	| expr '|' expr	        { $$.quad = new_quad1( '|', $1.quad, $3.quad); }
	| '(' expr ')'	        { $$.quad = new_quad3( '=', $1.index, $3.quad); }
	| '-' expr %prec UMINUS { $$.quad = new_quad2( UMINUS, $2.quad); }
	| number                { $$.quad = new_quad3( '=', $1.index, $3.quad); }
  | ident                 { $$.quad = new_quad3( '=', $1.index, $3.quad); }
	;

number	: CONSTANT;

ident   : IDENTIFIER;
%%

void	yyerror( char *s)
{
	printf( "%s\n", s);
}

