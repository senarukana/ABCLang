
TARGET = abclang
OBJS = y.tab.c lex.yy.c \
	map.o abc.o create.o error.o eval.o execute.o heap.o stack.o\
	memory.o native.o string.o util.o wchar.o\
	./memory/memory.o
CFLAGS = -c -g -Wall -ansi -DDEBUG
CC=gcc

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) -lm -ly -ll
clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h *.out *~

y.tab.c: abclang.y abclang.h
	bison --yacc -dv abclang.y

y.tab.h: abclang.y

lex.yy.c: abclang.l abclang.h y.tab.h
	flex abclang.l

./memory/memory.o:
	cd ./memory; $(MAKE);

abclang.h: ./memory/memory.h
memory.o: memory.c abclang.h
create.o: create.c abclang.h 
error.o: error.c abclang.h 
eval.o: eval.c abclang.h 
execute.o: execute.c abclang.h 
heap.o: heap.c abclang.h 
stack.o: stack.c memory.c
abc.o: abc.c abclang.h 
main.o: main.c abclang.h 
native.o: native.c abclang.h
string.o: string.c abclang.h 
util.o: util.c abclang.h 
wchar.o: wchar.c abclang.h 
map.o: map.c abclang.h