/* header of code_table.c */

#include <stdio.h>
#include <stdlib.h>

typedef enum {A, R, E} ARE;	/* new Data Type - one of 3 options: A or R or E */

enum reg {r0 = 1, r1 = 2, r2 = 4, r3 = 8, r4 = 16, r5 = 32, r6 = 64, r7 = 128}; /* the value of each register in the memory */

typedef struct Cnode* ptrC;	/* new Data Type - pointer to Node in a linked list (pointer to code table) */

typedef struct Cnode	/* new Data Type - Node in a linked list of memory bytes (code table) */
{
	union 	/* The memory byte can be divided or undivided */
	{
		struct			/* The first option: byte is divided into bits */
		{
			unsigned target : 2;	/* target addressing method */
			unsigned source : 2;	/* source addressing method */
			unsigned funct  : 4;	/* funct number of the commend */
			unsigned opcode : 4;	/* opcode number of the commend */
		} first;
		unsigned extra : 12;	/* The second option: byte is not divided into bits */
	} content;
	ARE prop;	/* */
	ptrC next;	/* the next node in the list */
} byte;

void addFirst(ptrC*, int, int, int, int, ARE); 		/* Add a divided memory byte - for a command line.                                                    
  							   get address of pointer to the head list of the code table (h), the target and source addressing, 
   							   the funct and opcode number, and A or R or E. add the word (the node) to the list  */

void addExtra(ptrC*, int, ARE);				/* Add a not divided memory byte to the code list.                                         
  							   get address of pointer to the head list of the code table (h), the content of the byte, 
  							   and if A or R or E. add the word (the node) to the list */

void joinCodeTables(ptrC*, ptrC);	/* get address of pointer to the head list of the code table (h1), and a pointer to the head list of a code table (h2)  
  					   Join 2 list of code to one. add all the nodes of the second list (h2) after the last node of the first list (h1) */

int isExternal(ptrC);		/* get pointer to the head list of the code table (h). return if the ARE field is E */

char getCharOfARE(ptrC); 	/* get pointer to the head list of the code table (h). return the ARE field in character */

int getLine(ptrC);		/* get pointer to the head list of the code table (h). return the content (the byte) */

ptrC nextC(ptrC);		/* get pointer to the head list of the code table (h). return the next node in the list */

void freeCodeList(ptrC*);	/* get address of pointer to the head list of the code table (h) 
  				   free the memory allocated to all nodes in the list 	*/   

