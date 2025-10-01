#ifndef HEREDOC_UTILS_H
# define HEREDOC_UTILS_H

# include "minishell.h"

int is_delimiter(char *line, char *delimiter);
void write_heredoc_line(int fd, char *line, t_data *data);
void read_heredoc_input(int write_fd, char *delimiter, t_data *data);

#endif
