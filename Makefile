build_flags = -g -Wall -pedantic-errors -std=gnu99

all: clean closure

build: closure

closure: closure.o
	gcc $(build_flags) bin/closure.o -o closure

closure.o: src/closure.c
	gcc $(build_flags) -c src/closure.c -o bin/closure.o

clean:
	rm -rf bin/*.o closure
