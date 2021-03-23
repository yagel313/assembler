#include "symbol_table.h"
#include "code_table.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#define IC_FIRST 100
#define MAXLINE 80
#define MAXLABEL 32
#define MAXGUIDNCE 8
#define CASE_DATA 1
#define CASE_STRING 2
#define CASE_ENTRY 3
#define CASE_EXTERNAL 4
#define STOP 5 
#define COMMAND 5


/* first step: read a line from fd and parse it into Allocated memory. identify if there's a label definition, determine
 * whether the line contains operation or instruction. whether it's a comment / white line  and what type of it.
 * pass the information to codetable.c functions that would handle it for additional process and to update IC.
 * check for some errors (mainly semantics errors) as a preliminary validation.
 * in case of symbol name the fuction pass the name symbol to symboltable.c to that add it to symbol table.
 * the function update for every line data/command the value of IC/DC
 * in case of data statement the function  check the line and pass the information to codetable.c functions that would handle it for additional process.
 * the function stop  whan the stream input got to EOF.
 * the function check every line and return 1 if error was found otherwise 0 */
int doFirstStep(FILE *fd, ptrS*, ptrC*, int*, int*);



/*the function get a pointer to number  and calculate the length number the function return the length number 
 *or zero in case of error */
int getLengthNum(char*);

/* the function get a line number ,string ,and adress of flag error and flag errorinline 
* the function print the line number and the string 
* the function set the value of flag error and flag errorinline  to 1*/
void error( int, char*, int*, int*);

/* the function get a pointer to string  and check the name of the guidence 
 * the function return 4 in case the  name guidence is .extern ,3 in case the name guidence is .entry
 * ,2  in case the name guidence is .string,and 1 in case the name guidence is .data*/
int whichguide(char* command);

/* the function get a pointer to string  and check the name of the command 
 * the function return 3 in case the  name command  is  command that need 3 line in the memory
 * ,2  in case the name command is command that need 2 line in the memory and 1 in case the 
 * name command  is  command that need 1 line in the memory*/
int whichcommand(char* command);

/* the function get a pointer to char ,the function check the value of char 
 * in case the value is space or tab the function add to pointer 1
 * the function stop in case the value is not space or tab*/
char* passSpace(char*);

/* the function get a pointer to char ,the function check the string 
 * in case the string  is  equal to register or command statement set the value of error to 1
 * in case the string contain char that is not  digits or letter the value of error to 1
  * return the value of error( 1 if error was found otherwise 0 )*/
int checkSymbol(char*);



