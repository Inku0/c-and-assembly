INC := inc

all: build_objects compile

build_objects: src/coolStack.c inc/coolStack.h
	clang -I$(INC) -c -o obj/coolStack.o src/coolStack.c
	clang -I$(INC) -c -o obj/coolStackTest.o src/coolStackTest.c
	clang -I$(INC) -c -o obj/main.o src/main.c

compile: src/main.c
	clang -I$(INC) -o bin/main obj/main.o obj/coolStack.o obj/coolStackTest.o
