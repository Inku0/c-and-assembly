CC := clang
CFLAGS := -Wall -Werror -Wpedantic -m32
LINKER := -fuse-ld=mold
INC := inc

AS := nasm
ASFLAGS := -felf32

INST_SRCS := $(wildcard src/instructions/*.c)
INST_OBJS := $(patsubst src/instructions/%.c,obj/instructions/%.o,$(INST_SRCS))

BF_OBJS := obj/bf.o obj/bfi.o obj/bfc.o obj/mem.o obj/simpleStack.o $(INST_OBJS)

.PHONY: clean all build_objects compile

all: build_objects collatz compile

collatz:
	$(AS) $(ASFLAGS) -o obj/x86_32/collatz.o src/x86_32/collatz.asm
	$(CC) $(CFLAGS) -o bin/collatz obj/x86_32/collatz.o src/asmcollatz.c

build_objects: $(wildcard src/*.c) $(wildcard inc/*.h)
	for src in src/*.c; do \
		obj=$$(basename $$src .c); \
		$(CC) $(CFLAGS) -I$(INC) -c -o obj/$$obj.o $$src; \
	done

	mkdir -p obj/instructions
	for src in src/instructions/*.c; do \
		obj=$$(basename $$src .c); \
		$(CC) $(CFLAGS) -I$(INC) -c -o obj/instructions/$$obj.o $$src; \
	done

compile: $(wildcard src/*.c) $(wildcard inc/*.h)
	$(CC) $(CFLAGS) $(LINKER) -I$(INC) -o bin/bf $(BF_OBJS)

clean:
	rm -f obj/*.o obj/instructions/*.o bin/*
