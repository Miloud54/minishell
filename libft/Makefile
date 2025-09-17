# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edidier <edidier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/24 16:51:42 by edidier           #+#    #+#              #
#    Updated: 2025/07/22 16:52:56 by edidier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs

SRC_DIR		= srcs
OBJ_DIR		= objs
INCLUDE_DIR	= inc

SRCS		= $(SRC_DIR)/ft_atoi.c $(SRC_DIR)/ft_bzero.c $(SRC_DIR)/ft_calloc.c $(SRC_DIR)/ft_free_split.c \
             $(SRC_DIR)/ft_isalnum.c $(SRC_DIR)/ft_isalpha.c $(SRC_DIR)/ft_isascii.c $(SRC_DIR)/ft_isdigit.c \
             $(SRC_DIR)/ft_isprint.c $(SRC_DIR)/ft_isspace.c $(SRC_DIR)/ft_itoa.c \
             $(SRC_DIR)/ft_lstadd_back_bonus.c $(SRC_DIR)/ft_lstadd_front_bonus.c $(SRC_DIR)/ft_lstclear_bonus.c \
             $(SRC_DIR)/ft_lstdelone_bonus.c $(SRC_DIR)/ft_lstiter_bonus.c $(SRC_DIR)/ft_lstlast_bonus.c \
             $(SRC_DIR)/ft_lstmap_bonus.c $(SRC_DIR)/ft_lstnew_bonus.c $(SRC_DIR)/ft_lstsize_bonus.c \
             $(SRC_DIR)/ft_memchr.c $(SRC_DIR)/ft_memcmp.c $(SRC_DIR)/ft_memcpy.c $(SRC_DIR)/ft_memmove.c \
             $(SRC_DIR)/ft_memset.c $(SRC_DIR)/ft_putchar_fd.c $(SRC_DIR)/ft_putendl_fd.c $(SRC_DIR)/ft_putnbr_fd.c \
             $(SRC_DIR)/ft_putstr_fd.c $(SRC_DIR)/ft_split.c $(SRC_DIR)/ft_strchr.c $(SRC_DIR)/ft_strcmp.c $(SRC_DIR)/ft_strdup.c \
             $(SRC_DIR)/ft_striteri.c $(SRC_DIR)/ft_strjoin.c $(SRC_DIR)/ft_strlcat.c $(SRC_DIR)/ft_strlcpy.c \
             $(SRC_DIR)/ft_strlen.c $(SRC_DIR)/ft_strmapi.c $(SRC_DIR)/ft_strncmp.c $(SRC_DIR)/ft_strnstr.c \
             $(SRC_DIR)/ft_strrchr.c $(SRC_DIR)/ft_strtrim.c $(SRC_DIR)/ft_substr.c $(SRC_DIR)/ft_tolower.c \
             $(SRC_DIR)/ft_toupper.c $(SRC_DIR)/get_next_line.c $(SRC_DIR)/get_next_line_utils.c \
             $(SRC_DIR)/ft_printf.c $(SRC_DIR)/ft_printchar.c $(SRC_DIR)/ft_printstring.c $(SRC_DIR)/ft_printptr.c \
             $(SRC_DIR)/ft_printint.c $(SRC_DIR)/ft_printunsigned.c $(SRC_DIR)/ft_printhex.c $(SRC_DIR)/ft_printf_utils.c
			

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
