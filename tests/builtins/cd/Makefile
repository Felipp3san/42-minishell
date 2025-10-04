# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 11:16:48 by fde-alme          #+#    #+#              #
#    Updated: 2025/10/04 17:55:20 by jfernand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# tests/Makefile

# Variables
CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -g
MAKEFLAGS	= --no-print-directory

# Names
LIBFT		= libft.a

# Folders
INCLUDE_DIR = ../../../include
SRC_DIR		= ../../../src
LIBFT_DIR	= ../../../libft
BUILD_DIR	= build

# Includes & Links
INCLUDE		= -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include
LINK		= -L../../../libft -lft

# Colors
DEF_COLOR	= \033[0;39m
GRAY		= \033[0;90m
RED			= \033[0;91m
GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

# Sources
SRCS		= $(SRC_DIR)/builtins/builtin_cd.c \
			  $(SRC_DIR)/utils/errors.c

TEST_SRC	= cd_test

# Objects
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) \
			  $(TEST_SRC:%=$(BUILD_DIR)/%.o)

# Binary
NAME		= cd_test

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LINK) -o $@
	@printf "$(GREEN)$@ compiled!$(DEF_COLOR)\n"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) $(MAKEFLAGS) all

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling: $< $(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling: $< $(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@printf "$(GREEN)$(NAME) build files cleaned!$(DEF_COLOR)\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "$(GREEN)$(NAME) binaries cleaned!$(DEF_COLOR)\n"

.PHONY: all run clean
