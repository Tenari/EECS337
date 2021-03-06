/*******************************************************************************
*
* FILE:		second.y 
*
* DESC:		EECS 337 Assignment 6
*      		yacc program for the Calculator page 295-296
*
* AUTHOR:	caseid
*
* DATE:		October 8, 2013
*
* EDIT HISTORY:	
*
*******************************************************************************/
%{
#include <ctype.h>
#include <stdio.h>
#include "yystype.h"
#include "y.tab.h"
%}

%start lines

%token INTEGER
%token FLOAT

%left '|'
%left '^'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%right UMINUS '~'/* supplies precedence for unary minus */

%% 	/* beginning of rules section */

lines	: lines expr '\n' 
   {
     switch( $2.type)
     {
       case INTEGER:
         printf("%Ld\n", $2.lvalue);
         break;
       case FLOAT:
         printf("%Lg\n", $2.dvalue);
         break;
     }
   }
	| lines '\n' 
	| /* empty */
	| error '\n' { yyerror(" reenter previous line: "); yyerrok; }
	;
expr	: expr '+' expr	
    {
      switch( $1.type)
      {
        case INTEGER:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = INTEGER;
              $$.lvalue = $1.lvalue + $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = (long double)$1.lvalue + $3.dvalue;
              break;
          }
          break;
        case FLOAT:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = FLOAT;
              $$.dvalue = $1.dvalue + (long double)$3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = $1.dvalue + $3.dvalue;
              break;
          }
          break;
      }
    }
	| expr '-' expr	
    {
      switch( $1.type)
      {
        case INTEGER:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = INTEGER;
              $$.lvalue = $1.lvalue - $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = (long double)$1.lvalue - $3.dvalue;
              break;
          }
          break;
        case FLOAT:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = FLOAT;
              $$.dvalue = $1.dvalue - (long double)$3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = $1.dvalue - $3.dvalue;
              break;
          }
          break;
      }
    }
	| expr '*' expr	
    {
      switch( $1.type)
      {
        case INTEGER:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = INTEGER;
              $$.lvalue = $1.lvalue * $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = (long double)$1.lvalue * $3.dvalue;
              break;
          }
          break;
        case FLOAT:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = FLOAT;
              $$.dvalue = $1.dvalue * (long double)$3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = $1.dvalue * $3.dvalue;
              break;
          }
          break;
      }
    }
	| expr '/' expr	
    {
      switch( $1.type)
      {
        case INTEGER:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = INTEGER;
              $$.lvalue = $1.lvalue / $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = (long double)$1.lvalue / $3.dvalue;
              break;
          }
          break;
        case FLOAT:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = FLOAT;
              $$.dvalue = $1.dvalue / (long double)$3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = $1.dvalue / $3.dvalue;
              break;
          }
          break;
      }
    }
	| expr '^' expr	
    {
      switch( $1.type)
      {
        case INTEGER:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = INTEGER;
              $$.lvalue = $1.lvalue ^ $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = $1.lvalue ^ (int)$3.dvalue;
              break;
          }
          break;
        case FLOAT:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = FLOAT;
              $$.dvalue = (int)$1.dvalue ^ $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = (int)$1.dvalue ^ (int)$3.dvalue;
              break;
          }
          break;
      }
    }
	| expr '&' expr	
    {
      switch( $1.type)
      {
        case INTEGER:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = INTEGER;
              $$.lvalue = $1.lvalue & $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = $1.lvalue & (int)$3.dvalue;
              break;
          }
          break;
        case FLOAT:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = FLOAT;
              $$.dvalue = (int)$1.dvalue & $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = (int)$1.dvalue & (int)$3.dvalue;
              break;
          }
          break;
      }
    }
	| expr '%' expr	
    {
      switch( $1.type)
      {
        case INTEGER:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = INTEGER;
              $$.lvalue = $1.lvalue % $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = $1.lvalue % (int)$3.dvalue;
              break;
          }
          break;
        case FLOAT:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = FLOAT;
              $$.dvalue = (int)$1.dvalue % $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = (int)$1.dvalue % (int)$3.dvalue;
              break;
          }
          break;
      }
    }
	| '~' expr	
    {
      $$.type = $2.type;
      switch( $2.type)
      {
        case INTEGER:
          $$.lvalue = ~ $2.lvalue ;
          break;
        case FLOAT:
          $$.dvalue = ~ (int)$2.dvalue ;
          break;
      }
    }
	| expr '|' expr	
    {
      switch( $1.type)
      {
        case INTEGER:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = INTEGER;
              $$.lvalue = $1.lvalue | $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = $1.lvalue | (int)$3.dvalue;
              break;
          }
          break;
        case FLOAT:
          switch( $3.type)
          {
            case INTEGER:
              $$.type = FLOAT;
              $$.dvalue = (int)$1.dvalue | $3.lvalue;
              break;
            case FLOAT:
              $$.type = FLOAT;
              $$.dvalue = (int)$1.dvalue | (int)$3.dvalue;
              break;
          }
          break;
      }
    }
	| '(' expr ')'	{ $$ = $2; }
	| '-' expr %prec UMINUS 
  {
     $$.type = $2.type;
     switch( $2.type)
     {
       case INTEGER:
         $$.lvalue = - $2.lvalue;
         break;
       case FLOAT:
         $$.dvalue = - $2.dvalue;
         break;
     }
   }
	| number
	;

number	: INTEGER
        | FLOAT
	;
%%

void	yyerror( char *s)
{
	printf( "%s\n", s);
}

