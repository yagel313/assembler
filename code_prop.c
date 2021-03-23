
/* This file creates and returns the command table for each command saved funct, opcode, number of arguments, 
   and valid addressing methods for each operand. The table uses the lineOpp data type */

#include "code_prop.h"

/*================================================================================================
  = create and return the table with the names of the commands and their settings and properties
==================================================================================================*/
lineOpp* getOppTable()
{
	lineOpp* oppArr = (lineOpp*)malloc(nOpp * sizeof(lineOpp)); /* create array of lineOpp items */

	/* fill the array */

	oppArr[0].name = "mov";
	oppArr[0].opcode = 0;
	oppArr[0]. funct = 0;
	oppArr[0].n_Op = 2;
	oppArr[0].options = "11010101";

	oppArr[1].name = "cmp";
	oppArr[1].opcode = 1;
	oppArr[1]. funct = 0;
	oppArr[1].n_Op = 2;
	oppArr[1].options = "11011101";

	oppArr[2].name = "add";
	oppArr[2].opcode = 2;
	oppArr[2]. funct = 10;
	oppArr[2].n_Op = 2;
	oppArr[2].options = "11010101";

	oppArr[3].name = "sub";
	oppArr[3].opcode = 2;
	oppArr[3]. funct = 11;
	oppArr[3].n_Op = 2;
	oppArr[3].options = "11010101";
	
	oppArr[4].name = "lea";
	oppArr[4].opcode = 4;
	oppArr[4]. funct = 0;
	oppArr[4].n_Op = 2;
	oppArr[4].options = "01000101";

	oppArr[5].name = "clr";
	oppArr[5].opcode = 5;
	oppArr[5]. funct = 10;
	oppArr[5].n_Op = 1;
	oppArr[5].options = "00000101";

	oppArr[6].name = "not";
	oppArr[6].opcode = 5;
	oppArr[6]. funct = 11;
	oppArr[6].n_Op = 1;
	oppArr[6].options = "00000101";

	oppArr[7].name = "inc";
	oppArr[7].opcode = 5;
	oppArr[7]. funct = 12;
	oppArr[7].n_Op = 1;
	oppArr[7].options = "00000101";

	oppArr[8].name = "dec";
	oppArr[8].opcode = 5;
	oppArr[8]. funct = 13;
	oppArr[8].n_Op = 1;
	oppArr[8].options = "00000101";

	oppArr[9].name = "jmp";
	oppArr[9].opcode = 9;
	oppArr[9]. funct = 10;
	oppArr[9].n_Op = 1;
	oppArr[9].options = "00000110";

	oppArr[10].name = "bne";
	oppArr[10].opcode = 9;
	oppArr[10]. funct = 11;
	oppArr[10].n_Op = 1;
	oppArr[10].options = "00000110";

	oppArr[11].name = "jsr";
	oppArr[11].opcode = 9;
	oppArr[11]. funct = 12;
	oppArr[11].n_Op = 1;
	oppArr[11].options = "00000110";

	oppArr[12].name = "red";
	oppArr[12].opcode = 12;
	oppArr[12]. funct = 0;
	oppArr[12].n_Op = 1;
	oppArr[12].options = "00000101";

	oppArr[13].name = "prn";
	oppArr[13].opcode = 13;
	oppArr[13]. funct = 0;
	oppArr[13].n_Op = 1;
	oppArr[13].options = "00001101";

	oppArr[14].name = "rts";
	oppArr[14].opcode = 14;
	oppArr[14]. funct = 0;
	oppArr[14].n_Op = 0;
	
	oppArr[15].name = "stop";
	oppArr[15].opcode = 15;
	oppArr[15]. funct = 0;
	oppArr[15].n_Op = 0;

	return oppArr;	/* return the command array */
}
/*====================================================================================================
  = get command table, and name of command and returns the legal number of arguments of this command =
  ====================================================================================================*/
int getNumOpp(lineOpp* table, char* oppName)
{	
	int i, retVal;
	for (i = 0; i < nOpp; i++)
		if(strcmp(table[i].name, oppName) == 0) /* look for the array item of this method */
			retVal = table[i].n_Op;
	return retVal;	/* return the number of arguments */
}

/*========================================================================================
  = get command table, and name of command and returns the opcode number of this command =
  ========================================================================================*/
int getOpcode(lineOpp* table, char* oppName)
{
	int i, retVal;
	for (i = 0; i < nOpp; i++)
		if(strcmp(table[i].name, oppName) == 0) /* look for the array item of this method */
			retVal = table[i].opcode;
	return retVal;	/* return the opcode */
}

/*=======================================================================================
  = get command table, and name of command and returns the funct number of this command =
  =======================================================================================*/
int getFunct(lineOpp* table, char* oppName)
{
	int i, retVal;
	for (i = 0; i < nOpp; i++)
		if(strcmp(table[i].name, oppName) == 0) /* look for the array item of this method */
			retVal = table[i].funct;
	return retVal;	/* return the funct */
}

/*===========================================================================================================================
  = get command table, and name of command and addressing method of target argument. returns if it legal addressing method. =
  ===========================================================================================================================*/
int isLegalTargetOperand(lineOpp* table, char* oppName, int target)
{
	int i, retVal;
	for (i = 0; i < nOpp; i++)
		if(strcmp(table[i].name, oppName) == 0) 		/* look for the array item of this method */
			retVal = table[i].options[4 + target] == '1';	/* Check the value on the right side of options (last four characters) */
	return retVal;
}

/*===========================================================================================================================
  = get command table, and name of command and addressing method of source argument. returns if it legal addressing method. =
  ===========================================================================================================================*/
int isLegalSourceOperand(lineOpp* table, char* oppName, int source)
{
	int i, retVal;
	for (i = 0; i < nOpp; i++)
		if(strcmp(table[i].name, oppName) == 0) 		/* look for the array item of this method */
			retVal = table[i].options[source] == '1'; 	/* Check the value on the left side of options (first four characters) */
	return retVal;
}

