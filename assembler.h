/* header file of assembler.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "symbol_table.h"	
#include "code_table.h"
#include "external_shows.h"

#define MAX_FILE_NAME 81
#define MIX_ARG 2

void process_file(char*);	/* get name of file and send the file to compailer */

int doFirstStep(FILE*, ptrS*, ptrC*, int*, int*);	/* get a file address, address of pointer to symbol list , address of pointer to code list,
							   address of DC and IC, and send them to the first step - create the code table for the data rows
							   and create the symbol table and update ICF, DCF. */

int doSecondStep(FILE*, ptrS*, ptrC*, ptrExt*);		/* get a file address, address of pointer to symbol list , address of pointer to code list, 	
							   address of pointer to list of external showes, and send them to second step - 
							   finish creating the entire code table. */ 

int exitOB(int, int, ptrC, char*);			/* get ICF, DCF, the symbol list and the name of file and create the .ob file */

int exitENT(ptrS, char*);				/* get the symbol table and the file name and create the .ent file */

int exitEXT(ptrExt, char*);				/* get address of pointer to list of external showes, and name of file and create the .ext file */

void joinCodeTables(ptrC*, ptrC);			/* join two code lists to one, conect the second list to the end of the first */

void freeCodeList(ptrC*);				/* free allocated memory */	

