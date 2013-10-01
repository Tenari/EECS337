/*******************************************************************************
*
* FILE:		scan.l
*
* DESC:		EECS 337 Assignment 5
* 		To avoid the syntax errors in test2.c we spell out the a, b, and
*		newline (\n) characters and filter away everything else.
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

%%

"a"	{ yylval = 'a'; return 'a'; }
"b"	{ yylval = 'b'; return 'b'; }
[\n]	{ yylval = (int) yytext[0]; return yytext[ 0]; }
.	{  } /* return everything else */

%%

/*
* resync the parser with a syntax error
*/
void yysync( void)
{
  int c;
  data.errors++;
  while (( c = getc( yyin )) != EOF)
  {
    if( c == '\n')
    {
      unput( c);
      break;
    }
  }
}

/*
 *	yywrap function
 */
int	yywrap( void)
{
	return(1);
}
