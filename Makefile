# Variables
CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -g

# Names
NAME		= minishell
LIBFT		= libft.a

# Includes & Links
INCLUDE		= -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include
LINK		= -Llibft -lft -lreadline

# Folders
INCLUDE_DIR = include
SRC_DIR		= src
BUILD_DIR	= build
LIBFT_DIR	= libft

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

# Files
# SRCS		= $(SRC_DIR)/pipex.c $(SRC_DIR)/utils.c
# SRCS_BONUS	= $(SRC_DIR)/pipex_bonus.c $(SRC_DIR)/utils.c
SRCS		= $(wildcard $(SRC_DIR)/*.c)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LINK) -o $(NAME)
	@printf "$(GREEN)$@ compiled! $(DEF_COLOR)\n"

$(LIBFT):
	@printf "$(CYAN)Compiling libft... $< $(DEF_COLOR)\n"
	@make -C $(LIBFT_DIR) all

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@printf "$(YELLOW)Compiling: $< $(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BUILD_DIR):
	@printf "$(MAGENTA)Build dir not found. Creating...$(DEF_COLOR)\n"
	@mkdir -p $(BUILD_DIR)
	
clean:
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean
	@printf "$(GREEN)$(NAME) object files cleaned!$(DEF_COLOR)\n"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@printf "$(GREEN)libft.a cleaned!$(DEF_COLOR)\n"
	@printf "$(GREEN)$(NAME) binaries cleaned!$(DEF_COLOR)\n"

re: fclean all
	@printf "$(GREEN)Cleaned and rebuilt!$(DEF_COLOR)\n"

# Phony
.PHONY: clean fclean bonus re all
