/*  in this file functions for the code table - list of ptrC variables */
 
#include "code_table.h"

/*======================================================================================================
  = Add a divided memory byte - for a command line.                                                    =
  = get address of pointer to the head list of the code table (h), the target and source addressing, =
  = the funct and opcode number, and A or R or E. add the word (the node) to the list                  =
  ======================================================================================================*/
void addFirst(ptrC* h, int target, int source, int funct, int opcode, ARE prop)
{
	ptrC b = (ptrC)malloc(sizeof(byte)); /* Allocating memory for the byte node. if fail print error */
	if (!b) 
	{
		printf("\n\t Error: cannot allocate memory. \n"); 
		exit(0);
	}
	/* set the data of the node  to the first option of the union */
	b->content.first.target = target;
	b->content.first.source = source;
	b->content.first.funct = funct;
	b->content.first.opcode = opcode;
	b->prop = prop;
	b->next = NULL;
	
	/* add the node to the list. if the list empty add to the head, if not add after the last node */
	if(!(*h))
	{
		b->next = NULL;
		*h = b;
	}
	else
	{	
		ptrC p = *h;
		while(p->next) p = p->next;
		p->next = b;
	}
	
}

/*===========================================================================================
  = Add a not divided memory byte to the code list.                                         =
  = get address of pointer to the head list of the code table (h), the content of the byte, =
  = and if A or R or E. add the word (the node) to the list
  ===========================================================================================*/
void addExtra(ptrC* h, int content, ARE prop)
{
	ptrC b = (ptrC)malloc(sizeof(byte)); /* Allocating memory for the byte node. if fail print error */
	if (!b) 
	{
		printf("\n\t Error: cannot allocate memory. \n"); 
		exit(0);
	}
	/* set the data of the node to the extra option of the union */
	b->content.extra = content;
	b->prop = prop;
	b->next = NULL;

	/* add the node to the list. if the list empty add to the head, if not add after the last node */
	if(!(*h))
	{
		b->next = NULL;
		*h = b;
	}
	else
	{	
		ptrC p = *h;
		while(p->next)
			p = p->next;
		p->next = b;
	}
}

/*========================================================================================================================
  =  get address of pointer to the head list of the code table (h1), and a pointer to the head list of a code table (h2) = 
  = Join 2 list of code to one. add all the nodes of the second list (h2) after the last node of the first list (h1)     =
  ========================================================================================================================*/
void joinCodeTables(ptrC* h1, ptrC h2)
{
	if (*h1)	/* if the first list not empty */
	{	
		ptrC p = *h1;
		while(p->next)		/* go to the last node and set the next fild to be the head of the second list */
			p = p->next;
		p->next = h2;
	}
}

/*=================================================================
  = get address of pointer to the head list of the code table (h) =
  = free the memory allocated to all nodes in the list            =
  =================================================================*/
void freeCodeList(ptrC* h)
{
	ptrC p;
	while(*h)	/* free each node of the list */
	{
		p = *h;
		*h = p->next;
		free(p);
	}
	
}

/*====================================================================================
  = get pointer to the head list of the code table (h). return if the ARE field is E =
  ====================================================================================*/
int isExternal(ptrC c)
{
	return c->prop == E;
}

/*========================================================================================
  = get pointer to the head list of the code table (h). return the next node in the list =
  ========================================================================================*/
ptrC nextC(ptrC c)
{	
	return c->next;
}

/*=====================================================================================
  = get pointer to the head list of the code table (h). return the content (the byte) =
  =====================================================================================*/
int getLine(ptrC h)
{
	return h->content.extra;
}

/*=========================================================================================
  = get pointer to the head list of the code table (h). return the ARE field in character =
  =========================================================================================*/
char getCharOfARE(ptrC h)
{
	return h->prop == A ? 'A' : h->prop == R ? 'R' : 'E';
}

