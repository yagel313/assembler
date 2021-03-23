/* header of code_prop.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nOpp 16 /* number of commends (array length) */

typedef struct opLine			/* Defining Data Type - Command Properties */
{
	char* name;			/* command name */
	unsigned short int opcode;	/* command opcode number */
	unsigned short int funct;	/* command funct number */
	unsigned short int n_Op;	/* legal argument number */
	char* options;
	
} lineOpp;

lineOpp* getOppTable();				/* create and return the table with the names of the commands and their settings and properties */

int getNumOpp(lineOpp*, char*);			/* get command table, and name of command and returns the legal number of arguments of this command */			

int getOpcode(lineOpp*, char*);				/* get command table, and name of command and returns the opcode number of this command */

int getFunct(lineOpp*, char*);				/* get command table, and name of command and returns the funct number of this command */

int isLegalTargetOperand(lineOpp*, char*, int);		/* get command table, and name of command and addressing method
							   of target argument. returns if it legal addressing method.*/

int isLegalSourceOperand(lineOpp*, char*, int);		/* get command table, and name of command and addressing method
							   of source argument. returns if it legal addressing method.*/
