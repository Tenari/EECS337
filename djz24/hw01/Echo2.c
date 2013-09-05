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
*
*******************************************************************************/
#include	<stdio.h>
/*
 * define flags: [+/-]echo 
 */
#define FLAGS_ECHO 0x00000001
#define IS_FLAGS_ECHO(a) (a & FLAGS_ECHO)
#define SET_FLAGS_ECHO(a) (a |= FLAGS_ECHO)
#define CLR_FLAGS_ECHO(a) (a &= ~FLAGS_ECHO)
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
        putchar( c); // put the charater to the stdout
    } else {
      putchar( c );
    }
  }
	return 0;
}
