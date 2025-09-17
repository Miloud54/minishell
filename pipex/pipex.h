/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:10:12 by edidier           #+#    #+#             */
/*   Updated: 2025/09/17 18:52:29 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_exec_data
{
	int			cmd_index;
	int			*pipe_fd;
	int			prev_pipe;
	char		**envp;
}				t_exec_data;

typedef enum e_bool
{
    BOOL_FALSE,
    BOOL_TRUE
}				t_bool;

typedef struct s_pipex
{
	int			in_fd;
	int			out_fd;
	t_bool		here_doc;
	t_bool		is_invalid_infile;
	char		**cmd_paths;
	char		***cmd_args;
	int			cmd_count;
}				t_pipex;

typedef struct s_child_args
{
	t_pipex		*pipex;
	t_exec_data	*data;
	int			i;
	char		**envp;
	int			pipe_fd[2];
	int			prev_pipe;
}				t_child_args;

/**** COMMON ****/
void			ft_init_pipex(t_pipex *pipex);
char			*get_cmd_path(char *cmd, char **envp);
int				get_cmd_start_index(t_pipex *pipex);
int				get_cmd_count(t_pipex *pipex, int ac);
int				get_array_index(t_pipex *pipex, int i);
void			ft_parse_cmds(t_pipex *pipex, char **av, int ac, char **envp);
void			ft_parse_args(t_pipex *pipex, char **av, int ac);
int				open_file(char *filename, int flags, mode_t mode,
					char *message);
void			free_pipex(t_pipex *pipex);

/**** MANDATORY ****/
void			ft_check_args(int ac, char **av, t_pipex *pipex);
int				validate_output_file(char *filename);
void			validate_files(t_pipex *pipex, char **av, int ac);
void			execute_first_cmd(t_pipex *pipex, int pipe_fd[2], char **envp);
void			execute_second_cmd(t_pipex *pipex, int pipe_fd[2], char **envp);
int				wait_and_exit(pid_t pid1, pid_t pid2, t_pipex *pipex);
void			ft_exec(t_pipex *pipex, char **envp);

/**** BONUS ****/
void			ft_check_args_bonus(int ac, char **av, t_pipex *pipex);
void			ft_parse_args_bonus(t_pipex *pipex, char **av, int ac);
void			handle_heredoc(char **av, t_pipex *pipex);
int				wait_all_children(int children_count);
int				handle_parent(int pipe_fd[2], int prev_pipe, int is_last);
void			execute_cmd(t_pipex *pipex, t_exec_data *data);
int				pipex_loop(t_pipex *pipex, char **envp);
void			pipex_child(t_child_args *args);
void			ft_exec_bonus(t_pipex *pipex, char **envp);

#endif