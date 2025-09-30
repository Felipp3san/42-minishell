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
TEST_SRC_DIR	= src

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
BUFFER_SRC     = $(SRC_DIR)/buffer/buffer.c
BUFFER_TEST    = $(TEST_SRC_DIR)/buffer_test.c

TOKENIZER_SRC     = $(SRC_DIR)/tokenizer/tokenizer.c \
                    $(SRC_DIR)/tokenizer/tokenizer_modes.c \
                    $(SRC_DIR)/tokenizer/tokenizer_utils.c
TOKENIZER_TEST    = $(TEST_SRC_DIR)/tokenizer_test.c

PARSER_SRC          = $(SRC_DIR)/parser/parser.c 
PARSER_TEST         = $(TEST_SRC_DIR)/parser_test.c

# Objects

BUFFER_OBJS    = $(BUILD_DIR)/buffer/buffer.o
BUFFER_TEST    = $(BUILD_DIR)/buffer_test.o
# ====

TOKENIZER_OBJS = $(BUILD_DIR)/tokenizer/tokenizer.o \
                 $(BUILD_DIR)/tokenizer/tokenizer_modes.o \
                 $(BUILD_DIR)/tokenizer/tokenizer_utils.o
TOKENIZER_TEST = $(BUILD_DIR)/tokenizer_test.o
# ====

PARSER_OBJS    = $(BUILD_DIR)/parser/parser.o 
PARSER_TEST    = $(BUILD_DIR)/parser_test.o

# Binary
BUFFER_BIN        = buffer_test
TOKENIZER_BIN     = tokenizer_test
PARSER_BIN        = parser_test

all: $(BUFFER_BIN) $(TOKENIZER_BIN) $(PARSER_BIN)

$(BUFFER_BIN): $(BUFFER_OBJS) $(BUFFER_TEST) $(LIBFT)
	@$(CC) $(CFLAGS) $(BUFFER_OBJS) $(BUFFER_TEST) $(LINK) -o $@
	@printf "$(GREEN)$@ compiled!$(DEF_COLOR)\n"

$(TOKENIZER_BIN): $(TOKENIZER_TEST) $(TOKENIZER_OBJS) $(BUFFER_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(TOKENIZER_TEST) $(TOKENIZER_OBJS) $(BUFFER_OBJS) $(LINK) -o $@
	@printf "$(GREEN)$@ compiled!$(DEF_COLOR)\n"

$(PARSER_BIN): $(PARSER_TEST) $(PARSER_OBJS) $(TOKENIZER_OBJS) $(BUFFER_OBJS) $(TOKENS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(PARSER_TEST) $(PARSER_OBJS) $(TOKENIZER_OBJS) $(BUFFER_OBJS) $(TOKENS_OBJS) $(LINK) -o $@
	@printf "$(GREEN)$@ compiled!$(DEF_COLOR)\n"

# Compile libft if missing
$(LIBFT):
	@printf "$(CYAN)Compiling libft...$(DEF_COLOR)\n"
	@make -C $(LIBFT_DIR) all

# Rule for src/ files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling: $< $(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Rule for test files
$(BUILD_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling: $< $(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(BUFFER_BIN) $(TOKENS_BIN)

fclean: clean
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
