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
%token IF
%token ELSE
%token LE
%token GE
%token EQ
%token NE
/* quads operators */
%token LABEL
%token GOTO
%token IFTRUE
%token IFFALSE

%left '|'
%left '^'
%left '&'
%left EQ NE
%left '<' '>' GE LE
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
stmts : IF '(' expr ')' stmts
    {
      $$.quad = new_quad5( IFTRUE, $3.quad, $5.quad, 0);
    }
  | IF '(' expr ')' stmts ELSE stmts
    {
      $$.quad = new_quad5( IFTRUE, $3.quad, $5.quad, $7.quad);
    }
  | ident '=' expr ';'
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
	| '(' expr ')'	        { $$.quad = $2.quad; }
	| '-' expr %prec UMINUS { $$.quad = new_quad2( UMINUS, $2.quad); }
	| number                { $$.quad = new_quad3( '=', $1.index, 0); }
  | ident                 { $$.quad = new_quad3( '=', $1.index, 0); }
  /* add relational operators */
  | expr LE expr          { $$.quad = new_quad1( LE, $1.quad, $3.quad); }
  | expr GE expr          { $$.quad = new_quad1( GE, $1.quad, $3.quad); }
  | expr EQ expr          { $$.quad = new_quad1( EQ, $1.quad, $3.quad); }
  | expr NE expr          { $$.quad = new_quad1( NE, $1.quad, $3.quad); }
  | expr '<' expr         { $$.quad = new_quad1( '<', $1.quad, $3.quad); }
  | expr '>' expr         { $$.quad = new_quad1( '>', $1.quad, $3.quad); }
	;

number	: CONSTANT;

ident   : IDENTIFIER;
%%

void	yyerror( char *s)
{
	printf( "%s\n", s);
}

