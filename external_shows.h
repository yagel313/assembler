#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct extNode* ptrExt; /* New data type - pointer to node in the list of extern appearances */

typedef struct extNode		/* New data type - node in the list of extern appearances */
{
	char symbol[31];	/* the name of label */
	int byteNumber;		/* the address where it appears */
	ptrExt next;		/* next node */
	
} extShow;

void addExtShow(ptrExt*, char*, int); /* get the extern appearances list, name of labe and the address in the code                 
 					 Adds an additional value to the list (label name along with the address where it appears) */

void printExtListToFile(FILE*, ptrExt); /* get a file and a extern appearances list. print all the list to th file. */


