#include "symbol_table.h"
#include "code_table.h"
#include "external_shows.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int whichcommand(char*); /* get name of command. Checks the number of bytes that will be in the code 
  			    for this command. return 0 if command name unlegal */

int whichguide(char*); /* get string. returns a number depending on the type of guide. return 0 is guide name unlegal */

void error( int, char*, int*, int*);	/*  get line number, error messege and error flages. print error messege to stdout and update error flags. */

char* passSpace(char*);			/* get string. remove white characters from the beginning of the string. */

int getLengthNum(char*);		/* gets string, Returns the length in characters of the number           
  					   that appears at the beginning of the string. The length in characters*/
   
char* getWord(char*, int);		/* get string and length. read word from the beginning of the string  
  					   up to white character or comma. return the word. The allocated memory is not freed */

int regVal(char);			/* Gets a character that has a register number. Returns the numeric value of the register */

int checkSymbol(char*);                 /*get a pointer of a symbol name and check the symbol name is legal and is not exists*/
