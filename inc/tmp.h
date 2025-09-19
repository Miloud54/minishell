#include "../libft/inc/libft.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TOKEN_WORD 1
#define TOKEN_PIPE 2
#define TOKEN_REDIR_IN 3
#define TOKEN_REDIR_OUT 4
#define TOKEN_APPEND 5


typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			**args;
	char			*input_file;
	char			*output_file;
	int				append; /*1 si >>, 0 si >*/
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_ms
{
	int				last_status;
}					t_ms;