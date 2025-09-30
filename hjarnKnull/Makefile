CC := clang
CFLAGS := -DDEBUG
LINKER := -fuse-ld=mold
INC := inc

all: build_objects compile

build_objects: src/coolStack.c inc/coolStack.h src/mem.c inc/mem.h
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/coolStack.o src/coolStack.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/coolStackTest.o src/coolStackTest.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/main.o src/main.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/bfi.o src/bfi.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/mem.o src/mem.c

compile: src/main.c src/bfi.c
	$(CC) $(CFLAGS) $(LINKER) -I$(INC) -o bin/main obj/main.o obj/coolStack.o obj/coolStackTest.o obj/mem.o
	$(CC) $(CFLAGS) $(LINKER) -I$(INC) -o bin/bfi obj/mem.o obj/bfi.o

clean:
	rm -f obj/*.o bin/*
