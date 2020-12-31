all: input calculator

input: input.c
	gcc -o input input.c

calculator: calculator.c
	gcc -o calculator calculator.c
