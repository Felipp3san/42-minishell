# tests/Makefile

# Variables
CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -g

# Names
LIBFT		= libft.a

# Folders
INCLUDE_DIR 	= ../include
SRC_DIR			= ../src
LIBFT_DIR		= ../libft
BUILD_DIR		= build

# Includes & Links
INCLUDE	= -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include
LINK	= -L../libft -lft

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Sources
BUFFER_SRC     = $(SRC_DIR)/tokenizer/buffer.c
BUFFER_TEST    = buffer_test.c

TOKENS_SRC     = $(SRC_DIR)/tokenizer/tokens.c
TOKENS_TEST    = tokens_test.c

# Objects
BUFFER_OBJS    = $(BUILD_DIR)/tokenizer/buffer.o \
                 $(BUILD_DIR)/buffer_test.o

TOKENS_OBJS    = $(BUILD_DIR)/tokenizer/tokens.o \
                 $(BUILD_DIR)/tokens_test.o

# Binary
BUFFER_BIN     = buffer_test
TOKENS_BIN     = tokens_test

all: $(BUFFER_BIN) $(TOKENS_BIN)

buffer: $(BUFFER_BIN)

tokens: $(TOKENS_BIN)

$(BUFFER_BIN): $(BUFFER_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(BUFFER_OBJS) $(LINK) -o $@
	@printf "$(GREEN)$@ compiled!$(DEF_COLOR)\n"

$(TOKENS_BIN): $(TOKENS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(TOKENS_OBJS) $(LINK) -o $@
	@printf "$(GREEN)$@ compiled!$(DEF_COLOR)\n"

# Compile libft if missing
$(LIBFT):
	@printf "$(CYAN)Compiling libft...$(DEF_COLOR)\n"
	@make -C $(LIBFT_DIR) all

# Rule for src/ files
$(BUILD_DIR)/tokenizer/%.o: $(SRC_DIR)/tokenizer/%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling: $<$(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Rule for test files
$(BUILD_DIR)/%.o: ./%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling: $< $(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

run: $(BUFFER_BIN)
	./$(BUFFER_BIN)

clean:
	rm -f $(BUFFER_BIN)

.PHONY: all run clean
