CC=gcc
CFLAGS= -Wall

SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/day*.c)

BUILD_DIR := build
BIN_FILES := $(subst $(SRC_DIR), $(BUILD_DIR), $(subst .c,,$(SRC_FILES)))

all: $(BIN_FILES)

$(BUILD_DIR)/day%: $(SRC_DIR)/day%.c $(SRC_DIR)/common.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(SRC_DIR)/common.c $< -o $@

clean:
	$(RM) -R $(BUILD_DIR)