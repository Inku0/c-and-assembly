CC := clang
CFLAGS := -Wall -Werror -Wpedantic
LINKER := -fuse-ld=mold
INC := inc

all: build_objects compile

build_objects: src/coolStack.c inc/coolStack.h src/mem.c inc/mem.h
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/coolStack.o src/coolStack.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/bfi.o src/bfi.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/mem.o src/mem.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/inst_inc.o src/inst_inc.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/inst_move.o src/inst_move.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/inst_read.o src/inst_read.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/inst_write.o src/inst_write.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/inst_beginLoop.o src/inst_beginLoop.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/inst_endLoop.o src/inst_endLoop.c
	$(CC) $(CFLAGS) -I$(INC) -c -o obj/inst_free.o src/inst_free.c

compile: src/bfi.c
	$(CC) $(CFLAGS) $(LINKER) -I$(INC) -o bin/bfi obj/mem.o obj/bfi.o obj/coolStack.o obj/inst_inc.o obj/inst_move.o obj/inst_read.o obj/inst_write.o obj/inst_endLoop.o obj/inst_beginLoop.o obj/inst_free.o

clean:
	rm -f obj/*.o bin/*
