/*******************************************************************************
*
* FILE:		Echo2.c
*
* DESC:		EECS 337 Homework Assignment 1
*
* AUTHOR:	djz24
*
* DATE:		August 27, 2013
*
* EDIT HISTORY:	
* 1, Sept, 2013 - first edit
* 5, Sept, 2013 - second edit
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tokens.c"

/*
 * define flags: [+/-]echo 
 */
#define FLAGS_ECHO 0x00000001
#define IS_FLAGS_ECHO(a) (a & FLAGS_ECHO)
#define SET_FLAGS_ECHO(a) (a |= FLAGS_ECHO)
#define CLR_FLAGS_ECHO(a) (a &= ~FLAGS_ECHO)

#define IN_VOID 6
#define IN_VOID2 61
#define IN_VOID3 62
#define IN_INT 7
#define IN_INT2 71
#define IN_CHAR 8
#define IN_CHAR2 81
#define IN_CHAR3 82
#define IN_RETURN 9
#define IN_RETURN2 91
#define IN_RETURN3 92
#define IN_RETURN4 93
#define IN_RETURN5 94
#define IN_ID 1
#define IN_LITERAL 2

  int parse_state = 0; // 0 = in nothing
  char ident_arr[64];
  char lit_arr[64];

void my_handle_lit(char c){
  parse_state = IN_LITERAL;
  int it;
  for(it = 0; it < 64; it++){
    if(lit_arr[it] == 0){
      lit_arr[it] = c;
      it = 500;
    }
  }
}
void clear_lit_arr(){
  int poo = 0;
  for(poo = 0; poo < 64; poo++){
    lit_arr[ poo] = 0;
  }
}

void my_handle_id(char c){
  int poo = 0;
  parse_state = IN_ID;
  for(poo = 0; poo < 64; poo++){
    if (ident_arr[poo] == 0){
      ident_arr[ poo] = c;
      poo = 500;
    }
  }
}
void clear_ident_arr(){
  int poo = 0;
  for(poo = 0; poo < 64; poo++){
    ident_arr[ poo] = 0;
  }
}
void my_redo_char(char c){
  parse_state = 0;
  my_putchar( c);
}

void finish_id( char c){
  if (isalpha( c)){
    // handle another id character
    my_handle_id( c);
  } else{
    print_token( IDENTIFIER, ident_arr);
    clear_ident_arr();
    my_redo_char( c);
  }
}

void my_putchar(char c){
  char text[2];
  if (parse_state == 0){
    switch( c)
    {
      case 'v':
        parse_state = IN_VOID;
        break;
      case 'i':
        parse_state = IN_INT;
        break;
      case 'c':
        parse_state = IN_CHAR;
        break;
      case 'r':
        parse_state = IN_RETURN;
        break;
      case '"':
        my_handle_lit( c);
        break;
      case '(':
      case ')':
      case '*':
      case '+':
      case ',':
      case ';':
      case '=':
      case '[':
      case ']':
      case '{':
      case '}':
        text[ 0] = c;
        text[ 1] = 0;
        print_token( c, text);
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        text[ 0] = c;
        text[ 1] = 0;
        print_token( CONSTANT, text);
        break;
      case ' ':
      case '\t':
      case '\v':
      case '\f':
      default: // skip all these characters
        break;
    }
    if (parse_state == 0 && isalpha(c))
      my_handle_id(c);

  } else if(parse_state == IN_ID){
    finish_id( c);
  } else if (parse_state == IN_LITERAL){
    if (c == '"'){
      my_handle_lit( c);
      print_token( STRING_LITERAL, lit_arr);
      clear_lit_arr();
      parse_state = 0;
    } else {
      my_handle_lit( c);
    }
  } else {
    switch( parse_state){
      case IN_VOID:
        if (c == 'o')
          parse_state = IN_VOID2;
        else {
          my_handle_id( 'v');
          finish_id( c);
        }
        break;
      case IN_VOID2:
        if (c == 'i')
          parse_state = IN_VOID3;
        else {
          my_handle_id( 'v');
          my_handle_id( 'o');
          finish_id( c);
        }
        break;
      case IN_VOID3:
        if (c == 'd'){
          parse_state = 0;
          print_token( VOID, "void");
        } else {
          my_handle_id( 'v');
          my_handle_id( 'o');
          my_handle_id( 'i');
          finish_id( c);
        }
        break;

      case IN_INT:
        if (c == 'n')
          parse_state = IN_INT2;
        else {
          my_handle_id( 'i');
          finish_id( c);
        }
        break;
      case IN_INT2:
        if (c == 't'){
          parse_state = 0;
          print_token( INT, "int");
        } else {
          my_handle_id( 'i');
          my_handle_id( 'n');
          finish_id( c);
        }
        break;

      case IN_CHAR:
        if (c == 'h')
          parse_state = IN_CHAR2;
        else {
          my_handle_id( 'c');
          finish_id( c);
        }
        break;
      case IN_CHAR2:
        if (c == 'a')
          parse_state = IN_CHAR3;
        else{
          my_handle_id( 'c');
          my_handle_id( 'h');
          finish_id( c);
        }
        break;
      case IN_CHAR3:
        if (c == 'r'){
          parse_state = 0;
          print_token( CHAR, "char");
        } else {
          my_handle_id( 'c');
          my_handle_id( 'h');
          my_handle_id( 'a');
          finish_id( c);
        }
        break;

      case IN_RETURN:
        if (c == 'e')
          parse_state = IN_RETURN2;
        else {
          my_handle_id( 'r');
          finish_id( c);
        }
        break;
      case IN_RETURN2:
        if (c == 't')
          parse_state = IN_RETURN3;
        else {
          my_handle_id( 'r');
          my_handle_id( 'e');
          finish_id( c);
        }
        break;
      case IN_RETURN3:
        if (c == 'u')
          parse_state = IN_RETURN4;
        else {
          my_handle_id( 'r');
          my_handle_id( 'e');
          my_handle_id( 't');
          finish_id( c);
        }
        break;
      case IN_RETURN4:
        if (c == 'r')
          parse_state = IN_RETURN5;
        else {
          my_handle_id( 'r');
          my_handle_id( 'e');
          my_handle_id( 't');
          my_handle_id( 'u');
          finish_id( c);
        }
        break;
      case IN_RETURN5:
        if (c == 'n'){
          parse_state = 0;
          print_token( RETURN, "return");
        } else {
          my_handle_id( 'r');
          my_handle_id( 'e');
          my_handle_id( 't');
          my_handle_id( 'u');
          my_handle_id( 'r');
          finish_id( c);
        }
        break;
      default:
        break;
    }
  }
}

/*
 *	main program
 */
int	main( int argc, char *argv[])
{
/*
 *	declare variables
 */
	int i;
	int c;
  int flags = 0;

  int state = 0;  // 0 = not in comment
                  // 1 = found one '/'
                  // 2 = found two '/' and are in a comment
                  // 3 = found a '*' after a '/' and are now in a comment
                  // 4 = found a '*' that might be getting us out of a comment block
                  // 5 = found the '/' that gets us out of the comment block
 time_t t;
/*
 * print start of test time
 */
 time( &t);
 fprintf( stdout, "for djz24 start time: %s", ctime( &t));

/*
 *	read from the command line and write out parameters
 */
  for( i = 0; i < argc; i++) {
    if( !strcmp( argv[ i], "+echo")){
      SET_FLAGS_ECHO(flags);
    }
    else if( !strcmp( argv[ i], "-echo")){
      CLR_FLAGS_ECHO(flags);
    }
  }
/*
 *	read from stdin and write to stdout
 */
	while(( c = getchar()) != EOF)	// while input character from stdin does not equal end of file (-1)
  {
    if( ! IS_FLAGS_ECHO(flags)){
      // manage state
      if (c == '/'){
        if (state == 0)
          state = 1;
        else if (state == 1)
          state = 2;
        else if (state == 4)
          state = 5;
      }
      else if (c == '*'){
        if (state == 1)
          state = 3;
        else if (state == 3)
          state = 4;
        else if (state == 4) // was just a comment *
          state = 3;         // back to 'in block comment'
      }
      else if (c == '#'){
        if (state == 0 )
          state = 2;
        else if  (state == 1)
          state = 0;
        else if (state == 4) // was just a comment *
          state = 3;         // back to 'in block comment'
        else if (state == 5) // we are finally truly out of a comment
          state = 0;
      }
      else if (c == '\n' && state == 2){
        state = 0;
      }
      else if (state == 1){
        state = 0;
        putchar('/');
      }
      else if (state == 4) // was just a comment *
        state = 3;         // back to 'in block comment'
      else if (state == 5) // we are finally truly out of a comment
        state = 0;

      // put characters by state
      if(state == 0)
        my_putchar( c);

    } else {
      my_putchar( c );
    }
  }
	return 0;
}
