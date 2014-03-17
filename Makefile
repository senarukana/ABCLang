
TARGET = abc
CC=gcc

y.tab.c: abclang.h abclang.y
	yacc -dv abclang.y

lex.yy.c: abclang.h abclang.l 
	lex abclang.l

y.tab.o: y.tab.c abclang.h
	$(CC) -c -g $*.c

lex.yy.o: lex.yy.c abclang.h
	$(CC) -c -g $*.c