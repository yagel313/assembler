#include "assembler.h"
/*========================================================================================
  = main program - get arguments from user (.asm files) and sends them for compilation   =
==========================================================================================*/
int main(int argc, char *argv[])
{
	
               /* check: valid argument amount */
	if(argc < MIX_ARG) 
	{
	        printf("Please run with at list one file name argument\n");
        	return 1; /* exit with error */
      	}
      /* send files to process */
   	 while (*(++argv))
	{
        	process_file(*argv);
	}
	return 0;	
}

/*===============================================================
  = compilation of .asm file. get the name of file to compile   =
=================================================================*/

void process_file(char* file_name)
{
	char str[MAX_FILE_NAME];  	/* file name */
    	FILE *asFile;	/* to read the .asm file */
	int errorFlag = 0;		/* error flag */
	int exitFilesFlag = 0;		/* error flag */ 
	int ICF, DCF;	/* code length and data length */
	
	ptrS s = NULL;			/* the symbol list - to save the labels that exsist in the file (Pointer to a linked list) */ 
        ptrC dataCode = NULL;		/* machine code table - the data section in the file (Pointer to a linked list) */ 
	ptrC totalCode = NULL;		/* all the machine code table of the file (Pointer to a linked list) */
	ptrExt ext = NULL;		/* list of all appearances of external variables (Pointer to a linked list) */
    
	/* open a file to assemble */ 
	strcpy(str,file_name);
	strcat(str, ".as");
    	
	asFile = fopen(str,"r");
 	if(asFile == NULL)
       	{
		printf("\n\tError: Can't open file %s.\n\n", str);
		exit(0);
	}
  
	printf("\nStart processing \"%s.as\" file.\n",file_name);

	/* ---- first step -- send assembly file to first read processing (Create the code table for the data rows and create the symbol table and update ICF, DCF) -*/

 	errorFlag = doFirstStep(asFile, &s, &dataCode, &ICF, &DCF);
	
	/*---- second step --(Finished creating the entire code table)   --------------------------------------------------------------------------------------------*/
	
	if(!errorFlag)		/* If the first step passed successfully go to the second step */
	{
		rewind(asFile); /* return to head of file */
		
		errorFlag = doSecondStep(asFile, &s, &totalCode, &ext);	/* send assembly file to second read processing */
		
		if (!errorFlag)						/* if passed successfully Go to export output files */
		{
			joinCodeTables(&totalCode, dataCode);	 /* join the cdoe data list with the list of all the code */
			
			/* output 3 files: .ob, .ent, ext */
			exitFilesFlag = exitOB(ICF, DCF, totalCode, str) && exitENT(s, str) && exitEXT(ext, str); 
			
			freeCodeList(&totalCode); /* free allocated memory */
		}
	}
	else
		freeCodeList(&dataCode); /* free allocated memory */  
	
	if(!errorFlag && exitFilesFlag)						/* print messege if assembler complete sucssefuly */
		printf("\nProcessing \"%s.as\" file completed.\n",file_name);
	else
		printf("\nProcessing \"%s.as\" file failed.\n",file_name);	
	

	if (fclose(asFile))	/* close the file , if fail print error */
	{
		printf("\n\tError: Can't close file %s.\n\n", str);
		exit(0);
	}

	freeSymbolList(&s);	 /* free allocated memory */   
}


