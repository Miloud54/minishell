# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/21 17:41:30 by bde-la-p          #+#    #+#              #
#    Updated: 2025/09/25 12:27:26 by bde-la-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
INCLUDE_DIRS	= -I./inc -I./libft/inc
READLINE_FLAGS	= -lreadline

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a

SRC_DIR			= srcs
SRCS			= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parsing/expansion/expansion.c \
	$(SRC_DIR)/parsing/expansion/expansion_process.c \
	$(SRC_DIR)/parsing/expansion/expansion_size.c \
	$(SRC_DIR)/parsing/expansion/expansion_vars.c \
	$(SRC_DIR)/parsing/lexer/lexer.c \
	$(SRC_DIR)/parsing/lexer/lexer_utils.c \
	$(SRC_DIR)/parsing/parser/parser.c \
	$(SRC_DIR)/parsing/parser/parser_args.c \
	$(SRC_DIR)/parsing/parser/parser_counter.c \
	$(SRC_DIR)/parsing/parser/parser_memory.c \
	$(SRC_DIR)/parsing/parser/parser_processing.c \
	$(SRC_DIR)/parsing/parser/parser_validation.c \
	$(SRC_DIR)/parsing/quotes.c \
	$(SRC_DIR)/parsing/tokens.c \
	$(SRC_DIR)/parsing/tokens_utils.c \
	$(SRC_DIR)/parsing/validations/validation.c \
	$(SRC_DIR)/parsing/validations/validation_pipe.c \
	$(SRC_DIR)/parsing/validations/validation_redirection.c \
	$(SRC_DIR)/utils/cleanup1.c \
	$(SRC_DIR)/utils/cleanup2.c \
	$(SRC_DIR)/utils/exits.c \
	$(SRC_DIR)/utils/globals.c \
	$(SRC_DIR)/utils/init_data.c \
	$(SRC_DIR)/utils/init_signals.c \
	$(SRC_DIR)/builtins/builtins.c \
	$(SRC_DIR)/builtins/cd.c \
	$(SRC_DIR)/builtins/cd_utils.c \
	$(SRC_DIR)/builtins/env.c \
	$(SRC_DIR)/builtins/exit.c \
	$(SRC_DIR)/builtins/exit_utils.c \
	$(SRC_DIR)/builtins/pwd.c \
	$(SRC_DIR)/builtins/echo.C \
	$(SRC_DIR)/builtins/unset.c \
	$(SRC_DIR)/builtins/export.c \
	$(SRC_DIR)/builtins/export_utils.c

OBJS			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

OBJ_DIR			= objs
OBJ_DIRS		= $(OBJ_DIR)/$(SRC_DIR) \
				  $(OBJ_DIR)/$(SRC_DIR)/parsing \
				  $(OBJ_DIR)/$(SRC_DIR)/parsing/expansion \
				  $(OBJ_DIR)/$(SRC_DIR)/parsing/lexer \
				  $(OBJ_DIR)/$(SRC_DIR)/parsing/parser \
				  $(OBJ_DIR)/$(SRC_DIR)/parsing/validations \
				  $(OBJ_DIR)/$(SRC_DIR)/utils \
				  $(OBJ_DIR)/$(SRC_DIR)/builtins

# Colors
GREEN			= \033[0;32m
RED				= \033[0;31m
BLUE			= \033[0;34m
YELLOW			= \033[0;33m
RESET			= \033[0m

all: $(NAME)

objs:
	@mkdir -p $(OBJ_DIRS)

$(OBJ_DIR)/%.o: %.c | objs
	@echo "$(BLUE)Compiling: $(YELLOW)$<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)Linking: $(YELLOW)$(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

test: $(NAME)
	@echo "$(BLUE)Running basic test...$(RESET)"
	@echo "echo hello" | ./$(NAME)

test_all: $(NAME)
	@echo "$(BLUE)Running complete test suite...$(RESET)"
	@chmod +x test_minishell.sh
	@./test_minishell.sh

test_stress: $(NAME)
	@echo "$(BLUE)Running stress tests...$(RESET)"
	@chmod +x stress_test.sh
	@./stress_test.sh

test_signals:
	@echo "$(BLUE)Testing signals...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) test_signals.c $(SRC_DIR)/utils/init_signals.c $(SRC_DIR)/utils/globals.c $(LIBFT) $(READLINE_FLAGS) -o test_signals
	@./test_signals
	@rm -f test_signals

valgrind: $(NAME)
	@echo "$(BLUE)Running with valgrind...$(RESET)"
	@echo "echo hello" | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

debug: CFLAGS += -fsanitize=address
debug: $(NAME)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@echo "Current directory contents:"
	@ls -la | grep -E "(objs|obj)"
	@echo "Removing directory: $(OBJ_DIR)"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@rm -rf objs
	@rm -rf obj
	@find . -name "*.o" -delete 2>/dev/null || true
	@echo "Cleanup complete"

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "Executable removed"

re: fclean all

.PHONY: all clean fclean re objs test test_all test_stress test_signals debug valgrind