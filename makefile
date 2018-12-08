all: share.o
	gcc share.o

share.o: share.c
	gcc -c share.c

run:
	./a.out
