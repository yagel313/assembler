assembler: assembler.o first_step.o second_step.o input_test.o symbol_table.o code_table.o code_prop.o external_shows.o exit_to_files.o
	gcc -g -ansi -Wall -pedantic assembler.o first_step.o second_step.o input_test.o symbol_table.o code_table.o code_prop.o external_shows.o exit_to_files.o -o assembler
assembler.o: assembler.c assembler.h 
	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o
first_stop.o: first_step.c first_step.h
	gcc -c -ansi -Wall -pedantic first_step.c -o first_step.o
second_stop.o: second_step.c second_step.h
	gcc -c -ansi -Wall -pedantic second_step.c -o second_step.o
input_test.o: input_test.c input_test.h
	gcc -c -ansi -Wall -pedantic input_test.c -o input_test.o
symbol_table.o: symbol_table.c symbol_table.h
	gcc -c -ansi -Wall -pedantic symbol_table.c -o symbol_table.o
code_table.o: code_table.c code_table.h
	gcc -c -ansi -Wall -pedantic code_table.c -o code_table.o
code_prop.o: code_prop.c code_prop.h
	gcc -c -ansi -Wall -pedantic code_prop.c -o code_prop.o
external_shows.o: external_shows.c external_shows.h
	gcc -c -ansi -Wall -pedantic external_shows.c -o external_shows.o
exit_to_files.o: exit_to_files.c exit_to_files.h
	gcc -c -ansi -Wall -pedantic exit_to_files.c -o exit_to_files.o
