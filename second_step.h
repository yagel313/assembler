#include "symbol_table.h"
#include "code_table.h"
#include "code_prop.h"
#include "external_shows.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE_LINE 80
#define ENTRY_LEN 5
#define FIRST_ADDRESS 100
#define FIRST_LINE 1
#define MAX_LEN_LABEL 32
#define MAX_LEN_COMMEND 5

enum addressingMethod {IMMEDIATE = 0, DIRECT = 1, RELATIVE = 2, REGISTER = 3}; /* the addressing methods of arguments */

int doSecondStep(FILE*, ptrS*, ptrC*, ptrExt*); /* get pointer to file (asmFile), pointer address of the symbol list (ptrS), 
						   pointer address of the code list (ptrC) and pointer address to list of external label
 						   appearances (ptrExt). do the second pass and Refund 1 if no errors are found, 0 if found. */

void error( int, char*, int*, int*);

char* passSpace(char*);

int getLengthNum(char*);
   
char* getWord(char*, int);

int regVal(char);

