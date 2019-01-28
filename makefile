ALL: EXEC EXECUTION

functions.o: functions.c functions.h
	gcc -c functions.c

main.o: main.c functions.h
	gcc -c main.c

EXEC: main.o functions.o
	gcc -o EXEC main.o functions.o -Wall

EXECUTION:
	./EXEC
