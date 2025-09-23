INC := inc

all: build_objects compile

build_objects: src/coolStack.c inc/coolStack.h src/mem.c inc/mem.h
	clang -I$(INC) -c -o obj/coolStack.o src/coolStack.c
	clang -I$(INC) -c -o obj/coolStackTest.o src/coolStackTest.c
	clang -I$(INC) -c -o obj/main.o src/main.c
	clang -I$(INC) -c -o obj/bfi.o src/bfi.c
	clang -I$(INC) -c -o obj/mem.o src/mem.c

compile: src/main.c src/bfi.c
	clang -I$(INC) -o bin/main obj/main.o obj/coolStack.o obj/coolStackTest.o obj/mem.o
	clang -I$(INC) -o bin/bfi obj/mem.o obj/bfi.o

clean:
	rm -f obj/*.o bin/*
