/* in this file functions for the symbol table - list of ptrS variables */

#include "symbol_table.h"

/*====================================================================================================
  = get address of pointer to the head list of the symbol table (h), and the values of the new node: = 
  = name of label, the address, the attribute; A or R or E.                                          =
  = add new node (with this parameters) to the end of list h                                         =
  ==================================================================================================== */
void addSymbol(ptrS* h, char* name, int val, Attribute a, unsigned short int entry)
{
	ptrS t = (ptrS)malloc(sizeof(symbol)); /* Allocation of memory. if faul print error */
	if (!t) 
	{
		printf("\n\t Error: cannot allocate memory. \n"); 
		exit(0);
	}
	/* set values of new node */
	strcpy(t->symbolName, name); 	/* set the name */
	t->value = val;			/* set the address */	
	t->attr = a;			/* set A or R or E */
	t->ifEntry = entry;		/* set if symvol is .entry  */
	t->next = NULL;
	
	/* if the list empty add to the top, if not add after the lest node */
	if(!(*h))
	{
		t->next = NULL;
		*h = t;
	}
	else
	{	
		ptrS p = *h;
		while(p->next) p = p->next;
		p->next = t;
	}
}

/*============================================================================================
  = get pointer to the node (symbol) in the symbol table (h). return the name of the symbol. =
  ============================================================================================ */
char* symbolName(ptrS h)
{
	return h->symbolName;
}

/*==============================================================================================
  = get pointer to the node (symbol) in the symbol table (h). return the address of the symbol =
  ============================================================================================== */
int symbolValue(ptrS h)
{
	return h->value;
}



/*============================================================================================================
  = get pointer to the node (symbol) in the symbol table (h). return the next node (next symbol) in the list =
  ============================================================================================================ */
ptrS nextS(ptrS h)
{
	return h->next;
}

/*=============================================================================================================
  = get pointer to the node (symbol) in the symbol table (h). return if the entry property of the symbol is 1 =  
  ============================================================================================================= */
int isEntry(ptrS h)
{	
	return h->ifEntry == 1;
}

/*===============================================================================
  = get pointer to the head list of the symbol table (h), and name of label (s) =
  = set the entry property of the symbol (node) with the name s to TRUE (1)     =
  =============================================================================== */
int setEntry(ptrS h, char* s)
{	
	while (h && strcmp(h->symbolName, s))	/* scan the list to look for the symbol with this name */
		h = h->next;
	if (h)
		h->ifEntry = 1;
	return h ? 1 : 0;	/* return if the symbol exsist in the list */
}

/*==========================================================================================
  = get address of pointer to the head list of the symbol table (h), and name of label (s) =
  = return if exsist symbol (node) with the name s in te list (h)                          =
  ========================================================================================== */
int ifExsist(ptrS h, char* s)
{	
	while (h && strcmp(h->symbolName, s))	/* scan the list to look for the symbol with this name */
		h = h->next;
	return h ? 1 : 0;
}

/*===============================================================================
  = get pointer to the head list of the symbol table (h), and name of label (s) =
  = return if the symbol with the name s is pointing to a code line             =
  =============================================================================== */
int ifCodeSymbol(ptrS h, char* s)
{
	while (h && strcmp(h->symbolName, s))	/* scan the list to look for the symbol with this name */
		h = h->next;
	return h ? (h->attr == code ? 1 : 0) : 0;
}

/*=======================================================================================
  = get pointer to the head list of the symbol table (h), and name of label (s)         =
  = return if the symbol with the name s is pointing to a declaration of external data  =  
  ======================================================================================= */
int ifExternalSymbol(ptrS h, char* s)
{
	while (h && strcmp(h->symbolName, s))	/* scan the list to look for the symbol with this name */
		h = h->next;
	return h ? (h->attr == external ? 1 : 0) : 0;
}
		
/*================================================================================
  = get  pointer to the head list of the symbol table (h), and name of label (s) =
  = return the address of the symbol with the name s                             =
  ================================================================================ */
int getAddressByName(ptrS h, char* s)
{
	while (h && strcmp(h->symbolName, s))	/* scan the list to look for the symbol with this name and return the address of this symbol */
		h = h->next;
	return h ? h->value : 0;
	
}

/*==================================================================================
  = get pointer to the head list of the symbol table (h), and the length of the    =
  = code in bytes - codeLen. add codeLen to address fild of each data symbol in h  =
  ================================================================================== */
void updateValue(ptrS h, int codeLen)
{
	while (h)
	{
		if (h->attr == data)		/* look for evry data label  and update the address fild */
			h->value += codeLen;
		h = h->next;
	}
}

/*====================================================================
  = get address of pointer to the head list of the symbol table (h). =
  = free all the allocated memory of the list h.                     =
  ==================================================================== */
void freeSymbolList(ptrS* h)
{
	ptrS p;
	while(*h)		/* free the memory of each node in the list */
	{
		p = *h;
		*h = p->next;
		free(p);
	}
	
}


