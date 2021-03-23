/* The second pass of the assembler on the code file */
#include "second_step.h"

/*===========================================================================================================================================
  = get pointer to file (asmFile), pointer address of the symbol list (ptrS), pointer address of the code list (ptrC)                       = 
  = and pointer address to list of external label appearances (ptrExt). do the second pass and Refund 1 if no errors are found, 0 if found. = 
  ===========================================================================================================================================*/
int doSecondStep(FILE* asmFile, ptrS* symbolTable, ptrC* codeTable, ptrExt* ext)
{
	lineOpp* oppTable = getOppTable(); /* table of details and rules of all commands */

	int lineCode = FIRST_ADDRESS;		/* address in bytes: */
	int flag = 1;			/* end file flag */
	int lineNumber = FIRST_LINE;	/* the number of line (start at 1) */
	int errorFlag = 0;		/* if found error in file */
	int errorInLine = 0;		/* if found error in current line */
	char* line;	/* to read line from file */	
	char* label;	/* name of symbol */
	char* ind;	/* copy of line to scan the line */
	char* s;	/* to read word */


	while(flag) 	/* while file not finished */
	{
		line = malloc(MAX_SIZE_LINE * sizeof(char));	/*Allocation of memory to a row from the file. if fail print error */					
		if (!line)	
		{
			printf("\n\t Error: cannot allocate memory. \n"); 
			exit(0);
		}
		/* get line from file .as */
		fgets(line, MAX_SIZE_LINE, asmFile);	
		ind = line;			/* to save the first index for free */
		if(feof(asmFile))		/* if it the last line in the file */	
			flag = 0;
		else if(strlen(ind = passSpace(ind)) && *ind != ';')	/* if it not empty or comment line */		
		{
			ind = strchr(ind, ':') ? strchr(ind, ':') + 1 : ind; /* pass label if exsist */
			ind = passSpace(ind);
			/* if Appears .entry in line */
			if (strlen(ind) && *ind == '.'){		
				if (strlen(++ind) >= ENTRY_LEN && strncmp(ind, "entry", ENTRY_LEN) == 0)
				{
					/* Check the validity of the .entry command */
					ind+= ENTRY_LEN;
					if (!strlen(ind) || !isspace(*ind)) 		
						error(lineNumber, "Illegal charecters after .entry.", &errorFlag, &errorInLine);
					else if (!strlen(ind = passSpace(ind)))		
						error(lineNumber, "Missing label after .entry.", &errorFlag, &errorInLine);
					else
					{	
						/* read the name of label to s */
						/* Check that the label is legal, that there are no unnecessary characters
 						   after it, and update in the symbol table that the label is an entry */
						s = getWord(ind, MAX_LEN_LABEL);
						ind = passSpace(ind + strlen(s));
						if (strlen(ind))
							error(lineNumber, "Ilegal chareters after label name.", &errorFlag, &errorInLine);
						else if (ifExternalSymbol(*symbolTable, s) )
							error(lineNumber, "extern label can't appear after .entry", &errorFlag, &errorInLine);
						else if (!setEntry(*symbolTable, s))
							error(lineNumber, "The label not exsist.", &errorFlag, &errorInLine);
						else if (strlen(ind = passSpace(ind)))
							error(lineNumber, "Ilegal chareters after end of command.", &errorFlag, &errorInLine);
						free(s);		
					}
				}}		
				
			else		/* it command line */
			{
				s = getWord(ind, MAX_LEN_COMMEND);	/* get the coomand name */
				int nOp = getNumOpp(oppTable, s);	/* find the legal number of arguments for this command */
				ptrC extra = NULL;			/* the arguments bytes of the command */
				int target = 0, source = 0;		/* the Source and target addressing method */
				/* found the funct and opcode numbers of the command */
				int funct = getFunct(oppTable, s);
				int opcode = getOpcode(oppTable, s);
				int i = 0;		/* argument index */
				int isFirstArg = 1;	/* if its the dirst argument */
				ind = passSpace(ind + strlen(s));
				/* scan all arguments */
				for (i = 1; i <= nOp && !errorInLine; i++)
				{
					lineCode++;
					/* If an argument is missing */
					if(!strlen(ind))	
						error(lineNumber, "Missing argument.", &errorFlag, &errorInLine); 					
					/* immediate addressing method (0) */
					else if (*ind == '#')
					{
						/* Check for a number if not exsist print error */
						int len; /* length of number in characters */
						len = getLengthNum(++ind);
						if (!len)
							error(lineNumber, "Missing number after #.", &errorFlag, &errorInLine);
						else
						{
							addExtra(&extra, atoi(ind), A);	/* add one byte to the list for this argument */ 
							ind += len;
							if (isFirstArg)			/* Save the addressing method of this argument. */
								isFirstArg = 0;		/* single argument sets a target addressing method */
							else
								source = target;
							target = IMMEDIATE;		
						}
					}
					/* Relative addressing method (2) */
					else if (*ind == '%')
					{
						/* Check for a label if not exsist print error */
						ind++;
						if (!strlen(ind))
							error(lineNumber, "Missing label after %.", &errorFlag, &errorInLine);
						else
						{
							/* Find the name of the label, and checks if this label is legal */
							label =  getWord(ind, MAX_LEN_LABEL);
							if(!ifExsist(*symbolTable, label))
								error(lineNumber, "The label not exsist or illegal.", &errorFlag, &errorInLine);
							else if (!ifCodeSymbol(*symbolTable, label))
								error(lineNumber, "after % must be a code label.", &errorFlag, &errorInLine);
							else
							{
								/* add one byte to the list for this argument */
								addExtra(&extra, getAddressByName(*symbolTable, label) - lineCode, A); 
								ind += strlen(label);
								target = RELATIVE;		/* Save the addressing method of this argument. */		
							}
							free(label);
						}
						
					}
					/* register direct addressing method (3) */
					else if (*ind == 'r')
					{
						/* Finds the name of the hamster, checks the existing hamster, and finds its numeric value */
						int reg = regVal(*(++ind));
						if (!regVal)
							error(lineNumber, "Wrong register name.", &errorFlag, &errorInLine);
						else
						{
							addExtra(&extra, reg, A);	/* add one byte to the list for this argument - the value of register */
							ind++;
							if (isFirstArg)			/* Save the addressing method of this argument. */
								isFirstArg = 0;		/* single argument sets a target addressing method */
							else
								source = target;
							target = REGISTER;
						}	
						
					}
					else
					/* direct addressing method (1) */
					{
						/*  Find the name of the label, and checks if this label is legal */
						label =  getWord(ind, MAX_LEN_LABEL);
						if(!ifExsist(*symbolTable, label))
							error(lineNumber, "The label not exsist or illegal.", &errorFlag, &errorInLine);
						else
						{
							/* Checks if the label is under external in the symbol table. Defines whether the byte will be R or E */
							Attribute att = ifExternalSymbol(*symbolTable, label) ? E : R;
							/* add one byte to the list for this argument - address of the symbol */
							addExtra(&extra,getAddressByName(*symbolTable, label), att);
							/* If the label is external - add to list of external label appearances (ptrExt) */
							if (att == E)
								addExtShow(ext, label, lineCode);
							ind += strlen(label);
							if (isFirstArg)			/* Save the addressing method of this argument. */
								isFirstArg = 0;		/* single argument sets a target addressing method */
							else
								source = target;
							target = DIRECT;			
						}
						free(label);
					}
					/* If no line errors were found, check for additional arguments to this command. */
					if (errorInLine)
						continue;
					ind = passSpace(ind);
					if (i < nOp) {
						if (*ind != ',')
						    error(lineNumber, "More than one arg required, comma-separated args required.", &errorFlag, &errorInLine);
						else
						  ind = passSpace(++ind); }
		
				}
				if (!errorInLine) 
				{
					/* Checks if the addressing methods of the arguments are legal */
					if (!strlen(ind))
					{
						if (nOp > 0)
						{	
							if (!isLegalTargetOperand(oppTable, s, target))
								error(lineNumber, "Ilegal addressing mode of target operand.", &errorFlag, &errorInLine);
							else if (nOp == 2 & !isLegalSourceOperand(oppTable, s, source))
								error(lineNumber, "Ilegal addressing mode of source operand.", &errorFlag, &errorInLine);
						}
						/* if no line error create the memory byte of the command header.
						   Attach to it the additional bytes of the arguments. 
						   And attach this list to the byte list - the code list (codeTable) */						
						if (!errorInLine)
						{
							addFirst(codeTable, target, source, funct, opcode, A);
							joinCodeTables(codeTable, extra);
						}
					}
					else
						error(lineNumber, "Ilegal chareters after end of command.", &errorFlag, &errorInLine);
				}
				lineCode++;
				free(s);		 
			}
				
		}			
		lineNumber++;	/* update the line number */
		errorInLine = 0;
	}
	free(line);

	return errorFlag;	/* return error flag */
}
