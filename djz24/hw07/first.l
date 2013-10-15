/*******************************************************************************
*
* FILE:		first.l
*
* DESC:		EECS 337 Assignment 6
*      		Scanner program for the Calculator page 296-296
*
* AUTHOR:	djz24
*
* DATE:		October 8, 2013
*
*
* EDIT HISTORY:	
*
*******************************************************************************/
D       [0-9]
L       [a-zA-Z_]
H       [a-fA-F0-9]
E       [Ee][+-]?{D}+
FS      (f|F|l|L)
IS      (u|U|l|L)*

%{
#include	"yystype.h"
#include	"y.tab.h"
/*
 * define the scanner symbol table (static)
 */
#define MAX_IDENTIFIERS 128
SYMBOL_TABLE symbol_tables[ MAX_IDENTIFIERS];
unsigned int symbol_table_index = 0;
/*
 * scanner symbol table register function
 * return an index into the symbol table (static)
 */
int identifier( char *buffer, unsigned int length)
{
  /*
   * find the same string and return the index
   */
  /*
   * else update to the next symbol table field
   */
   return symbol_table_index;
};
%}

%%

"$"		{ return( EOF); }
0[xX]{H}+{IS}? { sscanf( yytext, "%Lx", &yylval.lvalue); yylval.type = INTEGER; return( INTEGER); }
0{D}+{IS}? { sscanf( yytext, "%Lo", &yylval.lvalue); yylval.type = INTEGER; return( INTEGER); }
{D}+{IS}? { sscanf( yytext, "%Ld", &yylval.lvalue); yylval.type = INTEGER; return( INTEGER); }
{D}+{E}{FS}? { sscanf( yytext, "%Lf", &yylval.dvalue); yylval.type = FLOAT; return( FLOAT); }
{D}*"."{D}+({E})?{FS}? { sscanf( yytext, "%Lf", &yylval.dvalue); yylval.type = FLOAT; return( FLOAT); }
{D}+"."{D}*({E})?{FS}? { sscanf( yytext, "%Lf", &yylval.dvalue); yylval.type = FLOAT; return( FLOAT); }
" " {/*do nothing*/}
\n|.   { return( yytext[ 0]); /* return everything else */ }

%%

/*
 *	yy wrap function	always return NO
 */
yywrap()
{
	return( 1);
}

