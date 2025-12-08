CC := clang
CFLAGS := -Wall -Werror -Wpedantic -m32
LINKER := -fuse-ld=mold
INC := inc

AS := nasm
ASFLAGS := -felf32

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

INST_DIR := $(SRC_DIR)/instructions
OBJ_INST_DIR := $(OBJ_DIR)/instructions

ASM_DIR := $(SRC_DIR)/x86_32
OBJ_ASM_DIR := $(OBJ_DIR)/x86_32

DIRS := $(OBJ_DIR) $(OBJ_INST_DIR) $(OBJ_ASM_DIR) $(BIN_DIR)

CORE_SRCS := $(wildcard $(SRC_DIR)/*.c)
CORE_OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CORE_SRCS))

INST_SRCS := $(wildcard $(INST_DIR)/*.c)
INST_OBJS := $(patsubst $(INST_DIR)/%.c,$(OBJ_INST_DIR)/%.o,$(INST_SRCS))

ASM_SRCS := $(wildcard $(ASM_DIR)/*.asm)
ASM_OBJS := $(patsubst $(ASM_DIR)/%.asm,$(OBJ_ASM_DIR)/%.o,$(ASM_SRCS))

BF_OBJS := $(CORE_OBJS) $(INST_OBJS)

.PHONY: all clean compile_asm

all: $(BIN_DIR)/bf

$(BIN_DIR)/bf: $(BF_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(LINKER) -I$(INC) -o $@ $(BF_OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC) -c -o $@ $<

$(OBJ_INST_DIR)/%.o: $(INST_DIR)/%.c | $(OBJ_INST_DIR)
	$(CC) $(CFLAGS) -I$(INC) -c -o $@ $<

compile_asm: $(ASM_OBJS)

$(OBJ_ASM_DIR)/%.o: $(ASM_DIR)/%.asm | $(OBJ_ASM_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(DIRS):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/bf
