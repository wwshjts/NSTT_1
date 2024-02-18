.PHONY : all clean
src_dir := sources
header_dir := headers
targets := fibonacciHeap
debug_flugs := -fsanitize=address -fsanitize=undefined -fsanitize=leak

all : bin/ bin/fibonacciHeap.o

bin/ : 
	mkdir bin

bin/fibonacciHeap.o : sources/fibonacciHeap.cpp headers/fibonacciHeap.h
	cc -c sources/fibonacciHeap.cpp -o bin/fibonacciHeap.o $(debug_flugs) 


clean : 
	rm -f bin/*.o