/* header of exit_to_files.c */

#include "symbol_table.h"
#include "code_table.h"
#include "external_shows.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int exitOB(int, int, ptrC, char*); 	/* get ICF, DCF, the symbol list and the name of file and create the .ob file */

int exitENT(ptrS, char*);		/* get the symbol table and the file name and create the .ent file */		

int exitEXT(ptrExt, char*);		/* get address of pointer to list of external showes, and name of file and create the .ext file */	
