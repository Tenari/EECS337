/*******************************************************************************
*
* FILE:		quad.c
*
* DESC:		EECS 337 Assignment 9
*
* AUTHOR:	djz24
*
* DATE:		October 29, 2013
*
* EDIT HISTORY:	
*
*******************************************************************************/
#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<string.h>
#include 	<ctype.h>
#include 	"yystype.h"
#include 	"y.tab.h"

/*******************************************************************************
 *
 *	dynamic memory routines
 *
 ******************************************************************************/
/*
 *	memory allocation error (FATAL no return!)
 */
void	new_error( int length)
{
	fprintf( stderr, "Fatal error: memory allocation failure: %d\n", length);
	exit( -1);
}

/*
 *	allocate a quad data structure
 */
QUAD	*new_quad( int operator, int dst_type, int dst_index, int op1_type, int op1_index, int op2_type, int op2_index)
{
	QUAD *quad;

	if( !(quad = ( QUAD*)malloc( sizeof( QUAD))))
		new_error( sizeof( QUAD));
	else
	{
		memset( (void *)quad, 0, (size_t)sizeof( QUAD));
		quad->operator = operator;
		quad->dst_type = dst_type;
		quad->dst_index = dst_index;
		quad->op1_type = op1_type;
		quad->op1_index = op1_index;
		quad->op2_type = op2_type;
		quad->op2_index = op2_index;
		data.memory += sizeof( QUAD);
	}
	return( quad);
}

/*
 *	deallocate a quad data structure
 */
void	free_quad( QUAD *quad)
{
	if( quad)
	{
		free( quad);
		data.memory -= sizeof( QUAD);
	}
	return;
}

/*
 *	deallocate a quad linked list
 */
void	free_quad_list( QUAD *quad_list)
{
	QUAD	*quad_next;
/*
 *	deallocate the quad linked list structure
 */
	while( quad_list)
	{
		quad_next = quad_list->next;
		free_quad( quad_list);
		quad_list = quad_next;
	}
/*
 *	set the temporary variable back to zero
 */
	data.temp = 0;
	return;
}

/*
 *	find the last quad structure in linked list
 */
QUAD	*end_quad_list( QUAD *quad_list)
{
	if( quad_list)
		while( quad_list->next)
			quad_list = quad_list->next;
	return quad_list;
}

/*
 *	print a quad operand structure
 */
void	print_quad_operand( int type, int index)
{
/*
 *	switch on the operand type
 */
	switch( type)
	{
	case TYPE_IDENTIFIER:
	case TYPE_CONSTANT:
	     printf( "%s", data.st[ index].buffer);
	     break;
	case TYPE_TEMPORARY:
	     printf( "t%d", index);
	     break;
	case TYPE_LABEL:
	     printf( "label%d", index);
	     break;
	}
	return;
}

/*
 * define the relational operator strings
 */
char *relational[] =
{
  "<=",
  ">=",
  "==",
  "!=",
};

/*
 *	print a quad structure
 */
void	print_quad( QUAD *quad)
{
	switch( quad->operator)
	{
	case '|':
	case '^':
	case '&':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
  case '<':
  case '>':
       printf( "\t");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     printf( " %c ", quad->operator);
	     print_quad_operand( quad->op2_type, quad->op2_index);
	     break;
  case LE:
  case GE:
  case EQ:
  case NE:
       printf( "\t");
       print_quad_operand( quad->dst_type, quad->dst_index);
       printf( " = ");
       print_quad_operand( quad->op1_type, quad->op1_index);
       printf( " %s ", relational[ quad->operator - LE]);
       print_quad_operand( quad->op2_type, quad->op2_index);
       break;
	case UMINUS:
       printf( "\t");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = - ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
	case '~' :
       printf( "\t");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = ~ ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
	case '=':
       printf( "\t");
	     print_quad_operand( quad->dst_type, quad->dst_index);
	     printf( " = ");
	     print_quad_operand( quad->op1_type, quad->op1_index);
	     break;
  case IFTRUE:
      printf( "\t");
      printf( "IFTRUE ");
      print_quad_operand( quad->dst_type, quad->dst_index);
      printf( " GOTO ");
      print_quad_operand( quad->op1_type, quad->op1_index);
      break;
  case IFFALSE:
      printf( "\t");
      printf( "IFFALSE ");
      print_quad_operand( quad->dst_type, quad->dst_index);
      printf( " GOTO ");
      print_quad_operand( quad->op1_type, quad->op1_index);
      break;
  case LABEL:
      print_quad_operand( quad->dst_type, quad->dst_index);
      printf( ": ");
      break;
  case GOTO:
      printf( "\t");
      printf( "GOTO ");
      print_quad_operand( quad->dst_type, quad->dst_index);
      break;
  case ']':
      printf( "\t");
      print_quad_operand( quad->dst_type, quad->dst_index);
      printf( " = ");
      print_quad_operand( quad->op1_type, quad->op1_index);
      printf( " [ ");
      print_quad_operand( quad->op2_type, quad->op2_index);
      printf( " ] ");
      break;
	}
	printf( "\n");
	//	printf( "\nnext: %08.8x\n", (int)quad->next);
	return;
}

/*
 *	print a quad linked list
 */
void	print_quad_list( QUAD *quad_list)
{
	QUAD	*quad;
/*
 *	print the quad linked list structure
 */
	for( quad = quad_list; quad; quad = quad->next)
	{
		print_quad( quad);
	}
	return;
}

/*
 *	allocate the next temporary location
 */
int	next_temp( void)
{
	return ++data.temp;
}

/*
 *	allocate the next label location
 */
int	next_label( void)
{
	return ++data.label;
}

/*
 *	allocate a quad1 function
		$$.quad = new_quad1( '+', $1.quad, $3.quad);
 */
QUAD	*new_quad1( int operator, QUAD *q1, QUAD *q2)
{
  QUAD *quad;
  QUAD *last1 = end_quad_list( q1);
  QUAD *last2 = end_quad_list( q2);
  quad = new_quad( operator, TYPE_TEMPORARY, next_temp(), last1->dst_type, last1->dst_index, last2->dst_type, last2->dst_index);

  last1->next = q2;
  last2->next = quad;
	return q1;
}

/*
 *	allocate a quad2 function
		$$.quad = new_quad2( '~', $1.quad);
 */
QUAD	*new_quad2( int operator, QUAD *q1)
{
  QUAD *quad;
  QUAD *quad1 = end_quad_list( q1);
  quad = new_quad( operator, quad1->dst_type, quad1->dst_index, 0, 0, 0, 0);

  q1->next = quad;
	return q1;
}
/*
 *	allocate a quad3 function
		$$.quad = new_quad3( '=', $1.index, $3.quad);
 */
QUAD	*new_quad3( int operator, int index, QUAD *q1)
{
  QUAD *quad;
  if ( q1 == 0){
	  quad = new_quad(operator, TYPE_TEMPORARY, next_temp(), data.st[ index].type, index, 0, 0);
    return quad;
  }
  else {
    QUAD *quad1 = end_quad_list( q1);
    quad = new_quad( operator, data.st[ index].type, index, quad1->dst_type, quad1->dst_index, 0, 0);
    quad1->next = quad;
  }

  return q1;
}

/*
 * allocate a quad5 function
     $$.quad = new_quad5( IFTRUE, $3.quad, $5.quad, 0);       // if
     $$.quad = new_quad5( IFTRUE, $3.quad, $5.quad, $7.quad); // if else
 */
QUAD *new_quad5( int operator, QUAD *q1, QUAD *q2, QUAD *q3)
{
  QUAD *me;
  QUAD *last1 = end_quad_list( q1);
  QUAD *last2 = end_quad_list( q2);
  QUAD *label1 = new_quad( LABEL, TYPE_LABEL, next_label(), 0,0, 0,0);
  QUAD *last3;
  QUAD *label2;
  QUAD *theGoto;
  if ( q3 == 0){
    me = new_quad( operator, last1->dst_type, last1->dst_index, label1->dst_type, label1->dst_index, 0, 0);
  } else {
    last3 = end_quad_list( q3);
    label2 = new_quad( LABEL, TYPE_LABEL, next_label(), 0,0, 0,0);
    theGoto = new_quad( GOTO, TYPE_LABEL, label2->dst_index, 0,0, 0,0);
    me = new_quad( operator, last1->dst_type, last1->dst_index, label1->dst_type, label1->dst_index, label2->dst_type, label2->dst_index);
  }

  last1->next = me;
  me->next    = q2;
  if ( q3 != 0){
    last2->next  = theGoto;
    theGoto->next= label1;
    label1->next = q3;
    last3->next  = label2;
  } else {
    last2->next = label1;
  }

  return q1;
}
/*
 * allocate a quad8 function
     $$.quad = new_quad8( ']', $1.index, $3.quad, 0);
 */
QUAD *new_quad8( int operator, int index, QUAD *q1, QUAD *q2)
{
  // declare variables
  QUAD *newQuad;
  QUAD *multQuad;
  QUAD *last1 = end_quad_list( q1);
  char size[2];
  int  multIndex;

  // make new quad(s)
  if ( q2 == 0){
    size[0]  = (char)data.st[ index].specifier+48;
    size[1]  = 0;
    multIndex= install( TYPE_CONSTANT, size, 2, FORMAT_DECIMAL);
    multQuad = new_quad( '*', TYPE_TEMPORARY, next_temp(), last1->dst_type, last1->dst_index, TYPE_CONSTANT, multIndex);
    newQuad  = new_quad( operator, TYPE_TEMPORARY, next_temp(), data.st[ index].type, index, multQuad->dst_type, multQuad->dst_index);
  } else {
  }

  // link up new quad and old quads correctly
  last1->next    = multQuad;
  multQuad->next = newQuad;

  // return the head quad in the linked list
  return q1;
}
