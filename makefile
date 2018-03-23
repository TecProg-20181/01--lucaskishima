photopobre: main.o functions.h structs.h
	cc -o photopobre main.o functions.h structs.h
main.o:main.c
	cc -c main.c
