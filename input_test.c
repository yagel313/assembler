/* Input analysis functions for the first and second transitions */
#include "input_test.h"

/*============================================================================
  = get name of command. Checks the number of bytes that will be in the code = 
  = for this command. return 0 if command name unlegal                       =
  ============================================================================*/
int whichcommand(char* command)
{
	if(!strcmp(command,"mov")|| !strcmp(command,"sub")||!strcmp(command,"add")||!strcmp(command,"cmp")||!strcmp(command,"lea")) 
    		return 3;
	else if(!strcmp(command,"clr")||!strcmp(command,"not")||!strcmp(command,"inc")||!strcmp(command,"dec")||!strcmp(command,"jmp")||!strcmp(command,"bne") 
     	||!strcmp(command,"jsr") ||!strcmp(command,"red")||!strcmp(command,"prn"))
     		return 2;
	else if(!strcmp(command,"rts")||!strcmp(command,"stop"))
     		return 1;
	return 0;
}

/*===============================================================================================
  = get string. returns a number depending on the type of guide. return 0 is guide name unlegal =
  ===============================================================================================*/
int whichguide(char* command)
{
	if(!strcmp(command,".extern"))
    		return 4;
	else if(!strcmp(command,".entry"))
     		return 3;
	else if(!strcmp(command,".string"))
     		return 2;
	else if(!strcmp(command,".data"))
     		return 1;
	return 0;
}

/*=========================================================================
  = get string. remove white characters from the beginning of the string. =
  ========================================================================*/
char* passSpace(char* com)

{
	while (isspace(*com) && strlen(com))  /* Promotes the index until it finds a non-white character */
		com++;
	return com;
}

/*==========================================================================================================
  = get line number, error messege and error flages. print error messege to stdout and update error flags. =
  ==========================================================================================================*/
void error( int lineN, char* errorMes, int* errorFlag, int* errorInLine)
{
	fprintf(stdout, "\tError: in line %d: %s\n", lineN, errorMes);
	*errorFlag = 1;
	*errorInLine = 1;
}

/*=========================================================================
  = get string and length. read word from the beginning of the string     = 
  = up to white character or comma or up to maxLen size. return the word. =
  = The allocated memory is not freed                                     =
  =========================================================================*/
char* getWord(char* ind, int maxLen)
{
	char* s = malloc(maxLen * sizeof(char)); /* allocate memery. size: maxlen. if fail print error */
	char* start;
	if (!s)	
	{
		printf("\n\t Error: cannot allocate memory. \n"); 
		exit(0);
	}
	start = ind;
	while(strlen(ind) && !isspace(*ind) && *ind != ',') /* find the end of word */
		ind++;
	strncpy(s, start, ind - start);	/* copy to new string */
	s[ind - start] = '\0';
	return s;
}

/*=========================================================================
  = gets string, Returns the length in characters of the number           =
  = that appears at the beginning of the string. The length in characters =
  =========================================================================*/
int getLengthNum(char* com)
{
	
	int count_c = 0;      			
	if(*com == '+'|| *com == '-')	/* add 1 if the number starts with + or - */		
		count_c++;
	while (isdigit(*(com + count_c))) /* count the digits */		                                                                                      
		count_c++;
	if (count_c == 1 && (*com == '+'|| *com == '-'))  /* if illegal number set count by 0 */
		count_c = 0;
	
	return count_c;	
}

/*================================================
  = Gets a character that has a register number. =
  = Returns the numeric value of the register    =
  ================================================*/
int regVal(char c)
{
	int retVal = 0; 
	switch(c)
	{
		case '0': retVal = r0; break;
		case '1': retVal = r1; break;
		case '2': retVal = r2; break;
		case '3': retVal = r3; break;
		case '4': retVal = r4; break;
		case '5': retVal = r5; break;
		case '6': retVal = r6; break;
		case '7': retVal = r7; break; 
	}
	return retVal; /* numeric value of the register or 0 if error character */
}
/*============================================================================================
= the function get a pointer to string ,the function check the string                        =
= in case the string  is  equal to register or command statement set the value of error to 1 =
= in case the string contain char that is not  digits or letter the value of error to 1      =
= return the value of error( 1 if error was found otherwise 0 )                              =
  ============================================================================================*/

int checkSymbol(char* symbol)
{
      int error = 0; /* error flag*/
               
  	/* Checks if the label is legal - if it does not name a command or a register */
  	if (!strcmp(symbol,"mov")|| !strcmp(symbol,"sub")||!strcmp(symbol,"add")||!strcmp(symbol,"cmp")||!strcmp(symbol,"lea")||
		!strcmp(symbol,"clr")||!strcmp(symbol,"not")||!strcmp(symbol,"inc")||!strcmp(symbol,"dec")||!strcmp(symbol,"jmp")||
		!strcmp(symbol,"bne")||!strcmp(symbol,"jsr") ||!strcmp(symbol,"red")||!strcmp(symbol,"prn")||!strcmp(symbol,"rts")||
		!strcmp(symbol,"stop")||!strcmp(symbol,"r0")||!strcmp(symbol,"r1")||!strcmp(symbol,"r2")||!strcmp(symbol,"r3")||
		!strcmp(symbol,"r4")||!strcmp(symbol,"r5")||!strcmp(symbol,"r6")||!strcmp(symbol,"r7"))
 		error=1;
 	if(!error)
 	{
		/* Checks that the label contains only letters or numbers*/
 		while(strlen(symbol))
   		{
     			if(!isdigit(*symbol)&&!isalpha(*symbol))
      			{
         			error=1;
         			break;
      			}
    			symbol++;
   		}
	}

	return error;
}
