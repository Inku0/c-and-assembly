AS := nasm
ASFLAGS := -f elf        # use -f elf64 and remove -m32 for 64-bit builds
CC := clang
CFLAGS := -m32

ASM_SRCS := $(wildcard *.asm)
OBJS := $(ASM_SRCS:.asm=.o)

.PHONY: all clean

all: counter

counter: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	$(RM) $(OBJS) counter
