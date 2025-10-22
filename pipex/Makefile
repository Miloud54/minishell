# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edidier <edidier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 17:24:23 by edidier           #+#    #+#              #
#    Updated: 2025/09/17 18:45:05 by edidier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
NAME_BONUS		= pipex_bonus
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
INCLUDE_DIRS	= -I. -I../libft/inc

LIBFT_DIR		= ../libft

SRC_DIR			= srcs
SRCS			= \
	$(SRC_DIR)/pipex_bonus.c \
	$(SRC_DIR)/frees.c \
	$(SRC_DIR)/heredoc_bonus.c \
	$(SRC_DIR)/exec/exec_bonus.c \
	$(SRC_DIR)/exec/exec_bonus_child.c \
	$(SRC_DIR)/exec/exec_bonus_loop.c \
	$(SRC_DIR)/exec/exec_bonus_utils.c \
	$(SRC_DIR)/exec/exec_bonus_wait.c \
	$(SRC_DIR)/parsing/check_args_bonus.c \
	$(SRC_DIR)/parsing/init_pipex.c \
	$(SRC_DIR)/parsing/parsing_args_bonus.c \
	$(SRC_DIR)/parsing/validation.c \
	$(SRC_DIR)/parsing/parsing_cmds.c \
	$(SRC_DIR)/parsing/parsing_cmds_path.c \
	$(SRC_DIR)/parsing/parsing_cmds_utils.c \

OBJS		= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT			= $(LIBFT_DIR)/libft.a

OBJ_DIR	= objs
OBJ_DIRS = $(OBJ_DIR)/$(SRC_DIR) $(OBJ_DIR)/$(SRC_DIR)/parsing $(OBJ_DIR)/$(SRC_DIR)/exec

all: $(NAME)


objs:
	mkdir -p $(OBJ_DIRS)

$(OBJ_DIR)/%.o: %.c | objs
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

test: $(NAME)
	@echo "Testing basic functionality..."
	@echo "test" | ./pipex /etc/passwd "grep root" "wc -l" output.txt
	@cat output.txt

test_bonus: $(NAME)
	@echo "Testing bonus functionality..."
	@echo "test line\nanother line\ntest again" | ./pipex here_doc EOF "grep test" "wc -l" "cat -n" output.txt
	@cat output.txt

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	./pipex /etc/passwd "grep root" "wc -l" output.txt

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re objs test test_bonus valgrind
