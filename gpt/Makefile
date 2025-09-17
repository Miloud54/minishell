NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
SRCS = src/main.c src/signals.c src/parser.c src/exec.c src/builtin.c src/utils.c
OBJS = $(SRCS:.c=.o)
INC = -I include

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(INC) $(SRCS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
