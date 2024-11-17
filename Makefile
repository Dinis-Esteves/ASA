compile:
	g++ -o proj1.o -g -std=c++11 -O3 -Wall main.cpp -lm

run:
	./proj1.o

debug:
	gdb -tui proj1.o

