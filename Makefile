# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/21 17:41:30 by bde-la-p          #+#    #+#              #
#    Updated: 2025/09/22 14:28:35 by bde-la-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./inc -I./libft/inc

# Readline flags
READLINE_FLAGS = -lreadline

# Directories
SRC_DIR = srcs
LIBFT_DIR = libft
OBJ_DIR = obj

# Source files
MAIN_SRC = srcs/main.c

# Source files
MAIN_SRC = srcs/main.c

PARSING_SRC =	srcs/parsing/expansion.c\
				srcs/parsing/lexer.c\
				srcs/parsing/lexer_utils.c\
				srcs/parsing/parser.c\
				srcs/parsing/quotes.c\
				srcs/parsing/tokens.c\
				srcs/parsing/validation.c\
				src/parsing/validation_pipe.c\
				src/parsing/validation_redirection.c

UTILS_SRC = 	srcs/utils/cleanup.c\
				srcs/utils/init_data.c\
				srcs/utils/init_signals.c\
				srcs/utils/frees.c\
				srcs/utils/exits.c\
				srcs/utils/globals.c

# All source files
SRCS = $(MAIN_SRC) $(UTILS_SRC) $(PARSING_SRC)

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
RESET = \033[0m

# Main rule
all: $(NAME)

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/srcs/utils
	@mkdir -p $(OBJ_DIR)/srcs/parsing
	@mkdir -p $(OBJ_DIR)/srcs/builtins
	@mkdir -p $(OBJ_DIR)/srcs/execution

#Compile object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(BLUE)Compiling: $(YELLOW)$<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link the program
$(NAME): $(OBJS)
	@echo "$(GREEN)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)Linking: $(YELLOW)$(NAME)$(RESET)"
	@$(CC) $(OBJS) $(LIBFT_DIR)/libft.a $(READLINE_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# # Debug rule (optional)
# debug: CFLAGS += -fsanitize=address
# debug: $(NAME)

# .PHONY: all clean fclean re test debug