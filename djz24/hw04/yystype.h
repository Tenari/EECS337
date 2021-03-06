/*******************************************************************************
*
* FILE:		yystype.h for ansi_c compiler
*
* DESC:		EECS 337 Assignment 3
*
* AUTHOR:	djz24
*
* DATE:		September 10, 2013
*
* EDIT HISTORY:	
*
*******************************************************************************/
#ifndef	YYSTYPE_H
#define	YYSTYPE_H	1

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

/*
 * define an attribute structure
 */
#define ATTRIBUTE struct attribute
ATTRIBUTE
{
  int token;
  #define MAX_BUFFER_SIZE 128
  char buffer[ MAX_BUFFER_SIZE]; // static buffer
  int length;
  #define FORMAT_NONE 0
  #define FORMAT_CHAR 1
  #define FORMAT_DECIMAL 2
  #define FORMAT_HEXADECIMAL 3
  #define FORMAT_OCTAL 4
  #define FORMAT_FLOAT 5
  int format;
};
/*
 * define yystype
 */
#define YYSTYPE struct yystype
YYSTYPE
{
  int token;
  int index;
};

#include	"y.tab.h"
/*
 *	define a global data structure
 */
#define	DATA	struct data
DATA
{
	int	column;
	int	flags;
#define	FLAGS_ECHO	0x0001
#define	FLAGS_DEBUG	0x0002
#define	FLAGS_PARSE	0x0004
#define FLAGS_SYMBOL 0x0008

#define	IS_FLAGS_ECHO(a)	(a & FLAGS_ECHO)	
#define	SET_FLAGS_ECHO(a)	(a |= FLAGS_ECHO)
#define	CLR_FLAGS_ECHO(a)	(a &= ~FLAGS_ECHO)
#define	IS_FLAGS_DEBUG(a)	(a & FLAGS_DEBUG)	
#define	SET_FLAGS_DEBUG(a)	(a |= FLAGS_DEBUG)
#define	CLR_FLAGS_DEBUG(a)	(a &= ~FLAGS_DEBUG)
#define	IS_FLAGS_PARSE(a)	(a & FLAGS_PARSE)	
#define	SET_FLAGS_PARSE(a)	(a |= FLAGS_PARSE)
#define	CLR_FLAGS_PARSE(a)	(a &= ~FLAGS_PARSE)
#define IS_FLAGS_SYMBOL(a) (a & FLAGS_SYMBOL)
#define SET_FLAGS_SYMBOL(a) (a |= FLAGS_SYMBOL)
#define CLR_FLAGS_SYMBOL(a) (a &= ~FLAGS_SYMBOL)
/*
 * define the scanner attribute table (static)
 */
#define MAX_ATTRIBUTES 128
  ATTRIBUTE attributes[ MAX_ATTRIBUTES];
  unsigned int index;
};

/*
 *	define for yyparser debugging
 */
#define	YYDEBUG	1
/*
 *	external variables and functions from scan.l
 */
extern FILE	*yyin;
extern FILE	*yyout;
extern	char	*yytext;
extern	YYSTYPE yylval;
extern	int	yywrap( void);
extern	void	comment( void);
extern	void	commentT( void);
extern	void	count( int token);
extern	int	check_type( void);
/*
 *	external variables and functions from gram.y
 */
extern	int	yydebug;
extern	int	yyparse( void);
extern	void	yyerror( char *s);
/*
 *	external variables and functions from main.c
 */
extern	DATA	data;
extern	int	main( int argc, char *argv[]);

#endif
/*
 * external variables and functions from attribute.c
 */
extern void print_attribute( int index);
extern void print_attribute_table( void);
extern int attribute( int token, char *buffer, unsigned int length, int format);
