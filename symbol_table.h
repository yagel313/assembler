#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {external, code, data } Attribute;  /* New data type - property name */

typedef struct Snode* ptrS;	/* New data type - pointer to a node in the list of symbel table */

typedef struct Snode		/* New data type  - a node in the list of symbel table */
{
	char symbolName[31];		/* the name of the label */
	unsigned int value;		/* the address of the label in the code (in bytes) */
	Attribute attr;			/* Absolute or Relocatable or External */
	unsigned short int ifEntry;	/* For a data label, whether this data is intended for export to other files */
	ptrS next;
} symbol;

void addSymbol(ptrS*, char*, int, Attribute, unsigned short int);  /*get address of pointer to the head list of the symbol table (h), 
				                                     and the values of the new node: name of label, the address, the attribute; A or R or E.        
                                                  		     add new node (with this parameters) to the end of list h  */  

int ifExsist(ptrS, char*);		/* get address of pointer to the head list of the symbol table (h), and name of label (s)
					   return if exsist symbol (node) with the name s in te list (h)  */	

int ifCodeSymbol(ptrS, char*);		/* get pointer to the head list of the symbol table (h), and name of label (s) 
  					   return if the symbol with the name s is pointing to a code line */

int ifExternalSymbol(ptrS, char*);     	/* get pointer to the head list of the symbol table (h), and name of label (s)         
					  return if the symbol with the name s is pointing to a declaration of external data  */

int setEntry(ptrS, char*);		/* get pointer to the head list of the symbol table (h), and name of label (s) 
					   set the entry property of the symbol (node) with the name s to TRUE (1) */	

int symbolValue(ptrS);			/* get pointer to the node (symbol) in the symbol table (h). return the address of the symbol */

char* symbolName(ptrS);			/* get pointer to the node (symbol) in the symbol table (h). return the name (label) of the symbol */

int isEntry(ptrS);			/* get pointer to the node (symbol) in the symbol table (h). return if the entry property of the symbol is 1 */

ptrS nextS(ptrS);			/* get pointer to the node (symbol) in the symbol table (h). return the next node (next symbol) in the list */

int getAddressByName(ptrS, char*); 	/* get  pointer to the head list of the symbol table (h), and name of label (s) 
  					   return the address of the symbol with the name s */

void freeSymbolList(ptrS*);		/* get address of pointer to the head list of the symbol table (h). 
  					   free all the allocated memory of the list h.       */

void updateValue(ptrS, int);		/* get pointer to the head list of the symbol table (h), and the length of the    
  					   code in bytes - codeLen. add codeLen to address fild of each data symbol in h */

