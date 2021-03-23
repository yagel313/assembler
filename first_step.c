
/* This file do a first step on the file ,in case of symbol pass he symbol name to symboltable.c,
 * in case of data statement parse and pass every argument to codetable.c
 * return 1 if error was found otherwise 0  */


#include "first_step.h"

/*===============================================================================
  =get the file,first node of ptrS,first node of PtrC,pointer ICF,pointer IDF   =
  = update the node ptrS and ptrC ,update the value of ICF to final value of IC =
  = update the value of DCF to final value of DC                                =
  =  return 1 if error was found otherwise 0                                    =
  ===============================================================================*/

int doFirstStep(FILE *fd, ptrS* h, ptrC* k,int* ICF,int* DCF)
{
	int IC,DC; 			/* IC counter the line without data,DC:counter the line of data*/
     	int NumberData=0; 		/* int that hold the number data */
     	int flag1=1; 			/*flag to check if the file end */
    	int lengthnum=0;		 /*int that hold the length  number  in data*/
     	char *endNamesymbol; 		 /* end Name symbol pointer */
     	char *endNamecommand;		 /* end Name command pointer */
     	char *endNameguide;  		/* end Name command guidence pointer*/
     	int Numberguide=0;  		/*int that hold the number guidence */
     	int lineNumber=0;  		 /* count the line number*/
     	int Numbercommand=0;		/*int that hold the number command*/
     	int ERROR_FLAG=0;		 /*flag to check if the error in line */ 
     	int flagSymbol=0;		/* use as a flag to check if fgets has  a symbol in the line */
     	int   flagData=0;		/* use as a flag to check if fgets has  a data in the line */
     	int errorInLine=0;		/* use as a flag to check if error in the line */
     	int L;			/*count the numbers in data guidence */
         int flag2;		/*flag to check if the symbol name is illegal */
    	char* guideName;	/* guideName pointer */
     	char* symbol;		/* symbol pointer */
     	IC = IC_FIRST;		/*IC start with  value 100 */
     	DC = 0;
       	L=0;
   
   

   while (flag1)/*while the file is not end*/
  	{
      		char* line = malloc(MAXLINE * sizeof(char));   /* line role: hold the whole input line */  
      		char* i;              /* line pointer, run through line with */
      		flagSymbol = 0;      
      		flagData = 0;       
      		flag2=0;
		fgets(line, MAXLINE, fd);
     		if(!line)/*check if the file no open*/
       		{
       			printf("\n\t Erorr:cannot allocate memory.\n");
         		exit(0);
        	}
      		
		i = line;
		
     		if(feof(fd))	/*end of file*/
        		flag1 = 0;
     		else
       		{
			char* symbolName=malloc(MAXLABEL * sizeof(char));  /* symbolName role: hold the symbol name */
          		lineNumber++;
          		i=passSpace(i);
           		
			/* Checks whether it starts with a letter - a command or a label */
			if(isalpha(*i)) 
              		{
				/* checks if label exsist */
                		if(strstr(i, ":")!=NULL)
                 		{
                  			endNamesymbol = strstr(i, ":");	/*after the symobl must be ":"	*/
	          			strncpy(symbolName, i, endNamesymbol - i );/*copy the symbol name */
                                        
                                        symbolName[endNamesymbol - i ]='\0';
                                        
                  			if((strlen(symbolName))<=MAXLABEL)/*check if the symbol name is less from MAXLABEL(32) */
                     			{
                      				i=endNamesymbol+1;
	              				i=passSpace(i); 
                      				flagSymbol=1;
                    			}
                   		 	else
                                            error(lineNumber, "Illegal name of symbol.", &ERROR_FLAG, &errorInLine);
                       			
                 		}
              		}

			/*check if a guidence statement*/
               		if(*i=='.'&&!errorInLine)
                 	{
                                      
                        	flagData=1;
                               	endNameguide=i;
                            	while(strlen(endNameguide) > 1 && *endNameguide != ' ' && *endNameguide!='\t')/*check for the end of word guidence*/
                    			endNameguide++;
                              	/*check which guidence statement */
                      		guideName=malloc(MAXGUIDNCE * sizeof(char));
	              		strncpy(guideName, i,endNameguide - i );/*copy to guidename the  guidence name*/
                      		guideName[endNameguide - i]='\0';
                      		Numberguide=whichguide(guideName);/* get from the function the number of the guidence statement */
                      		if(!Numberguide)
					error(lineNumber, "Illegal name of directive statement.", &ERROR_FLAG, &errorInLine);
				/*  if the number guidence is 1 is a case of data statement */
                      		else if(Numberguide==CASE_DATA)
                       		{           
	                 		i=endNameguide;
                         		i=passSpace(i);
                         		if(flagSymbol)
                                        {
                                        	flag2=checkSymbol(symbolName); /*check  if symbol name  is legal */
                                                if(!flag2)
                                                {
                                                	if (!ifExsist(*h, symbolName))/*check if symbol name is exsist */
                        				      	addSymbol(h, symbolName, DC,data, 0);
                                                        else
                                                              	error(lineNumber, "the symbol name already exists.", &ERROR_FLAG, &errorInLine);
                                               	}
                                                else
                                                	error(lineNumber, "illegal symbol.", &ERROR_FLAG, &errorInLine);
                                     	} 
                                        if(!strlen(i))
                                               error(lineNumber, "Missing argument.", &ERROR_FLAG, &errorInLine);
                                        else
                                        {  
                       				while(strlen(i)&&!errorInLine)/*send every number in the data statement to the function addextra and raise DC */
                          			{
                          				i=passSpace(i);
  			  				lengthnum= getLengthNum(i);/*get the length number from the function,if the length is 0 is error*/
                          				if(!lengthnum)
				 			     error(lineNumber, "Illegal number.", &ERROR_FLAG, &errorInLine);
 			 				else 
			 				{ 
                                                              
			   					NumberData=atoi(i);/*converts the string argument to int*/
                                                                
                                                               
                           					addExtra(k, NumberData, A);/*pass the number to function addextra*/
                                                                  
                           					DC++;
                   						i = passSpace(i + lengthnum);/*pass the pointer  to end of number*/		
                           					if(*i==',')
			     					{
			      						i++;
                              						i=passSpace(i);
		
                               						if(!strlen(i))/*if the length of string is 0 and the previous label was ',' */
                                 					    error(lineNumber, "Illegal label.", &ERROR_FLAG, &errorInLine);
			      					}
                           					else if(strlen(i))/*if the previous label was number and current label not ',' */
		               					     error(lineNumber, "Illegal charcter after number.", &ERROR_FLAG, &errorInLine);
							}
						 }	
				      	}
				}
				/*  if the number guidence is 2  a case of string statement */
        			else if(Numberguide==CASE_STRING)
                       		{  
                       			i=endNameguide;
                        		i=passSpace(i);
                          		if(flagSymbol)/*line with symbol name */
                                        {
                                        	flag2=checkSymbol(symbolName);  /*check  if symbol name  is legal */    
                                               	if(!flag2)
                                                {
                                                	if (!ifExsist(*h, symbolName))/*check if symbol name is exsist */
                        				   	addSymbol(h, symbolName, DC,data, 0);
                                                        else
                                                               	 error(lineNumber, "the symbol name already exists.", &ERROR_FLAG, &errorInLine);
                                                }
                                                else
                                                	error(lineNumber, "illegal symbol.", &ERROR_FLAG, &errorInLine);
                                      	}
	                    		if(*i=='"')/*first string */
                                  	{   
                                    		i++;
                                    		while(*i!='"'&&strlen(i))/*pass every char in the string  to the function add extra and raise L */
                                    		{
                                       			addExtra(k,(int)*i, A);
                                         		L++;
                                     			i++;
                                    		}
                                              	if(*i!='"')/*case the last charcter is not " ,error string*/
                                                       error(lineNumber, "Illegal string.", &ERROR_FLAG, &errorInLine);
                                              	else
                                                {   
                                    			i++;
                                    			addExtra(k,(int)'\0', A);
							L++;
				  			i = passSpace(i);
                                    			if(strlen(i))/*case error label after end of string*/
                                     			    	error(lineNumber, "Illegal charcter after end of string.", &ERROR_FLAG, &errorInLine);
				  			DC+=L; 
                                                }
                                  	} 
                           		else /*every string must be with " in the first*/
                                		error(lineNumber, "Illegal string.", &ERROR_FLAG, &errorInLine);
                       		}   
				/*  if the number guidence is 3  a case of entry statement */
	        		else if(Numberguide==CASE_ENTRY)
                             	{
                                	if(flagSymbol)/*add to symbol table the symbol name */
                                   		printf("\tWarning: in line %d: symbol in .entry line\n", lineNumber);
                                              
                              	}
				/*  if the number guidence is 4  a case of external statement */
	        		else if(Numberguide==CASE_EXTERNAL)
                        	{
                             		symbol=malloc(MAXLABEL * sizeof(char));
                            		i=endNameguide;
                            		i=passSpace(i);
                                      	if(!strlen(i))/*check if the guidence statement without argument */
                                                error(lineNumber, "Missing argument.", &ERROR_FLAG, &errorInLine);
                                      	else
                                        {
	                    			if(isalpha(*i))
                              			{
                                                	endNamesymbol=i;
							/*find the last charcter of the symbl */
                                                     	while(strlen(endNamesymbol) > 1 && *endNamesymbol!= ' ' && *endNamesymbol!='\t')
                                                          	endNamesymbol++;
	                     				strncpy(symbol, i, endNamesymbol - i );/*copy the symbol name */
                             				symbol[endNamesymbol - i ]='\0';
                                                  	if(flagSymbol)
                                                        {
                                                              	flag2=checkSymbol(symbolName);/*check if the symbol name is legal*/
                             				       	if(!flag2)
                                                                { 	/*case of symbol name in external  statement outpout warning*/
                                                                  	if (!ifExsist(*h, symbolName))
 									  	printf("\tWarning: in line %d: symbol in .external line\n", lineNumber);     
                                                                 	else 		/*line with symbol already exists */
                                                                     		 error(lineNumber, "the symbol name already exists.", &ERROR_FLAG, &errorInLine);      
                                                               }
                                                               else
                                                                  error(lineNumber, "illegal symbol.", &ERROR_FLAG, &errorInLine); 
                                  			}  
                                                        flag2=checkSymbol(symbol);/*check if the symbol name of extrnal is legal*/
                             				if(!flag2)
                                                        { /*case of symbol name in external  statement outpout warning*/
                                                                  if (ifExsist(*h, symbol) && !ifExternalSymbol(*h, symbol))
                                                                      error(lineNumber, "the symbol name already exists.", &ERROR_FLAG, &errorInLine);  
                                                                  else if (!ifExternalSymbol(*h, symbol))
                                                                     addSymbol(h, symbol, 0,external, 0);     
                                                        }
                                                        else
                                                        	error(lineNumber, "illegal symbol.", &ERROR_FLAG, &errorInLine);              
                             			}
					      free(symbol);
                                             }
                         		}
                    			free(guideName);
      		       		
                 	}
                      	if(!flagData && *i!=';'&&!errorInLine)/*  if is not a data line and is not note line is a command line */
                          {
                               /* check if the command is stop */
                               if(strlen(i))
                                   {
                                        endNamecommand=i;
                                        while(strlen(endNamecommand)>1&&*endNamecommand!= ' '&&*endNamecommand!='\t')/*find a space or tab */
                    		             {
                                              endNamecommand++;
                                             }
                                      		char* commandlName=malloc(COMMAND  * sizeof(char));
	                           		strncpy(commandlName, i,endNamecommand - i );/*copy to coomandlname the  command name*/
                                   		commandlName[endNamecommand - i ]='\0';
		                   		Numbercommand=whichcommand(commandlName);/*find which type of command */
                         
	                           		if(Numbercommand)
                                   		{
                                      			if(flagSymbol)/*line with symbol name */
                                                       {
                                                        flag2=checkSymbol(symbolName);  /*check if the symbol name legal */   
                                                        if(!flag2)
                                                          {
                                                             if (!ifExsist(*h, symbolName))/*check if the symbol name exsist */  
                        				           addSymbol(h, symbolName, IC,code, 0);
                                                             else
                                                                  error(lineNumber, "the symbol name already exists.", &ERROR_FLAG, &errorInLine);
                                                           }
                                                        else
                                                                error(lineNumber, "illegal symbol.", &ERROR_FLAG, &errorInLine);
                                                        }
                                    			IC+=Numbercommand;/*add the number command to IC */
                                  		}
                                  		else/*case numbercommand is 0 is a error command */ 
                                      		   error(lineNumber, "Illegal command.", &ERROR_FLAG, &errorInLine);

						free(commandlName);
                             		
                                    }
			}
                       
			   free(symbolName); 
                } 
                 
                errorInLine=0;              
                L=0;
		flagData = 0;
                free(line);                  
       	}
            *ICF=IC-100;	/*ICF get the final value of IC-100*/
            *DCF=DC;  		/*DCF get the final value of DC*/
          updateValue(*h,IC);	/*pess to function updateValue arguments*/
     	return ERROR_FLAG;
}

