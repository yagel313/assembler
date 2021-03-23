/* The file handles the ptrExt data type,
    pointing to an appearances table for .extern labels */

#include "external_shows.h"
/*=============================================================================================
  = get the extern appearances list, name of labe and the address in the code                 =
  = Adds an additional value to the list (label name along with the address where it appears) =
  =============================================================================================*/
void addExtShow(ptrExt* h, char* s, int n)
{
	ptrExt t = (ptrExt)malloc(sizeof(extShow)); /* Create a new variable of type ptrExt (pointer to node of list) */
	if (!t) /* If the allocation failed print an error and exit */
	{
		printf("\n\t Error: cannot allocate memory. \n"); 
		exit(0);
	}

	/* put into the variable the values that the function received */
	strcpy(t->symbol, s);
	t->byteNumber = n;
	t->next = NULL;
	
	/* If the list is empty, enter the node at the top of the list, otherwise enter the end */
	if(!(*h))
	{
		t->next = NULL;
		*h = t;
	}
	else
	{	
		ptrExt p = *h;
		while(p->next)
			p = p->next;
		p->next = t;
	}
}

/*============================================================================
  = get a file and a extern appearances list. print all the list to th file. =
  ============================================================================*/

void printExtListToFile(FILE* fd, ptrExt p)
{
	while(p)
	{
		fprintf(fd, "%s %04d\n", p->symbol, p->byteNumber); /* print the content of each node in new line */
		p = p->next;
		
	}	
}
