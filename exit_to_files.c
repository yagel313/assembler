/* This file contains commands for exporting files from the assembler */

#include "exit_to_files.h"
/*==============================================================================
  = get ICF, DCF, the symbol list and the name of file and create the .ob file =
  = Return 1 in case of success, 0 in case of failure                          =
  ==============================================================================*/
int exitOB(int ICF, int DCF, ptrC code, char* file)
{
	FILE* fd;	/* to create the .ob file */
	int address;	/* the memory address */
	
	/* look for point and change to .ob */
	char* point = strchr(file, '.');
	*point = '\0';
	strcat(file, ".ob");
	
	fopen(file, "w");				/* create the .ob file */			
	fd = fopen(file, "r");				/* check if the file was created successfully, if not - print error */
	if (!fd)
	{
		printf("\n\tError: Can't create file %s.\n\n", file);
		return 0;
	}	
	fd = fopen(file, "w");	/* open the file to write */
	fprintf(fd, "%d %d\n", ICF, DCF);	/* print the ICF and DCF in the first line */
	
	/* print all the mechine code (from the code list) to the .ob file */	
	for (address = 100; code; address++)
	{
		fprintf(fd,"%04d %03X %c\n",address, getLine(code), getCharOfARE(code));	/* print address and the byte content */
		code = nextC(code);
	}
		
	if (fclose(fd))	/* close the file - if fail print error */
	{
		printf("\n\tError: Can't close file %s.\n\n", file);
		return 0;
	}

	return 1;
}

/*===================================================================
  = get the symbol table and the file name and create the .ent file =
  = Return 1 in case of success, 0 in case of failure               =
  ===================================================================*/
int exitENT(ptrS s, char* file)
{
	FILE* fd;	/* to create .ent file */
	
	/* look for point and change to .ent */
	char* point = strchr(file, '.');
	*point = '\0';
	strcat(file, ".ent");

	/* check if exsist lables in the symbol table with the .entry mark. only if exsist create the file */
	while(s)
		if(isEntry(s)) 
		{
			if (!file)					/* If memory allocation failed - print error */
			{
				printf("\n\tError: malloc fail.\n\n");
				return 0;
			}		
			fopen(file, "w");				/* create the  .ent file */			
			fd = fopen(file, "r");				/* check if the file was created successfully, if not - print error */
			if (!fd)
			{
				printf("\n\tError: Can't create file %s.\n\n", file);
				return 0;
			}	
			fd = fopen(file, "w");	/* open the file to write */
			
			while(s) /* scan all the symbol table for lables with .entry mark */
			{
				if(isEntry(s))
					fprintf(fd,"%s %04d\n", symbolName(s), symbolValue(s)); /* print the symbol name and his address to .ent file */
				s = nextS(s);	
			}
			if (fclose(fd))		/* close file, if fail print error */
			{
				printf("\n\tError: Can't close file %s.\n\n", file);
				return 0;
			}
		}
		else
			s = nextS(s);	
	return 1;	
}

/*========================================================
  = get address of pointer to list of external showes,   =
  = and name of file and create the .ext file            =
  =  = Return 1 in case of success, 0 in case of failure =
  ========================================================*/
int exitEXT(ptrExt p, char* file)
{	
	if(p)	/*only if the extern list not enpty create the .ext file */
	{	
		FILE* fd;	/* to create .ext file */
		
		/* look for point and change to .ent */
		char* point = strchr(file, '.');
		*point = '\0';
		strcat(file, ".ext");
		
		fopen(file, "w");				/* create the  .ext file */			
		fd = fopen(file, "r");				/* check if the file was created successfully, if not - print error */
		if (!fd)
		{
			printf("\n\tError: Can't create file %s.\n\n", file);
			return 0;
		}	
		fd = fopen(file, "w");	/* open the file to write */
		printExtListToFile(fd, p);	/* print all the extern list to .ext */
		
		if (fclose(fd))	/* close the file. if fail print error */	
		{
			printf("\n\tError: Can't close file %s.\n\n", file);
			return 0;
		}

	}
	return 1;	
}
