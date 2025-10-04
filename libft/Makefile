# Variables
CC			= cc
AR			= ar rcs
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -g
NAME		= libft.a

# Folders
INCLUDE_DIR	= include
SRC_DIR		= src
BUILD_DIR	= build

# Colors
DEF_COLOR 	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE 		= \033[0;94m
MAGENTA 	= \033[0;95m
CYAN 		= \033[0;96m
WHITE 		= \033[0;97m

# Files
SRCS		:= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS		:= $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, $(SRCS))

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@printf "$(GREEN)$(subst .a,,$(NAME)) compiled! $(DEF_COLOR)\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling: $< $(DEF_COLOR) \n"
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@printf "$(CYAN)$(subst .a,,$(NAME)) build files cleaned!$(DEF_COLOR)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(CYAN)$(subst .a,,$(NAME)) binaries cleaned!$(DEF_COLOR)\n"

re: fclean all
	@printf "$(GREEN)Cleaned and rebuilt!$(DEF_COLOR)\n"

# Phony
.PHONY: clean fclean bonus re all
