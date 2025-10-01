/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:30:00 by bde-la-p         #+#    #+#             */
/*   Updated: 2025/09/30 11:30:00 by bde-la-p        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <fcntl.h>

static int	create_pipe_if_needed(int i, int cmd_count, int pipe_fd[2])
{
	if (i < cmd_count - 1)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

static void	setup_pipe_input(int cmd_index, int prev_pipe)
{
	if (cmd_index == 0)
		return ;
	if (dup2(prev_pipe, STDIN_FILENO) == -1)
	{
		perror("dup2 prev_pipe");
		exit(127);
	}
	close(prev_pipe);
}

static void	setup_pipe_output(int cmd_index, int cmd_count, int pipe_fd[2])
{
	if (cmd_index == cmd_count - 1)
		return ;
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 pipe_fd[1]");
		exit(127);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static void	execute_piped_command(t_cmd *cmd, t_pipe_data *data,
		t_data *shell_data)
{
	char	*path;

	setup_pipe_input(data->cmd_index, data->prev_pipe);
	setup_pipe_output(data->cmd_index, data->cmd_count, data->pipe_fd);
	// Gerer les redirections de la commande (< > >>)
	if (setup_redirections(cmd, shell_data) == -1)
		exit(1);
	// Executer builtin ou commande externe
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(shell_data, cmd);
		exit(shell_data->exit_status);
	}
	else
	{
		path = find_executable(cmd->args[0], shell_data->envp);
		if (!path)
		{
			printf("minishell: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
		if (execve(path, cmd->args, shell_data->envp) == -1)
		{
			perror("execve");
			free(path);
			exit(127);
		}
		free(path);
	}
}

static int	handle_parent_process(int pipe_fd[2], int prev_pipe,
		int is_last_cmd)
{
	if (prev_pipe != -1)
		close(prev_pipe);
	if (!is_last_cmd)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	return (-1);
}

static int	wait_all_pipeline_children(int cmd_count)
{
	int	status;
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		wait(&status);
		last_status = status;
		i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (1);
}

static int	setup_pipeline_heredocs(t_cmd **commands, int cmd_count,
		t_data *data)
{
	int		i;
	int		j;
	int		temp_fd;
	char	*temp_filename;
	char	*pid_str;

	// Pour les pipelines, on utilise des fichiers temporaires
	i = 0;
	while (i < cmd_count)
	{
		j = 0;
		while (j < commands[i]->redirect_count)
		{
			if (commands[i]->redirects[j].type == TOKEN_REDIR_HEREDOC)
			{
				// Créer un fichier temporaire unique
				pid_str = ft_itoa(getpid());
				temp_filename = ft_strjoin("/tmp/minishell_heredoc_", pid_str);
				free(pid_str);
				if (!temp_filename)
					return (-1);
				temp_fd = open(temp_filename, O_CREAT | O_WRONLY | O_TRUNC,
						0600);
				if (temp_fd == -1)
				{
					free(temp_filename);
					return (-1);
				}
				// Lire le heredoc et l'écrire dans le fichier temporaire
				if (write_heredoc_to_file(temp_fd,
						commands[i]->redirects[j].file, data) == -1)
				{
					close(temp_fd);
					unlink(temp_filename);
					free(temp_filename);
					return (-1);
				}
				close(temp_fd);
				// Ouvrir le fichier en lecture et stocker le fd
				commands[i]->redirects[j].heredoc_fd = open(temp_filename,
						O_RDONLY);
				// Supprimer le fichier temporaire (mais le fd reste ouvert)
				unlink(temp_filename);
				free(temp_filename);
				if (commands[i]->redirects[j].heredoc_fd == -1)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	execute_pipeline(t_cmd **commands, int cmd_count, t_data *data)
{
	int			pipe_fd[2];
	int			prev_pipe;
	pid_t		pid;
	t_pipe_data	pipe_data;
	int			i;

	prev_pipe = -1;
	i = 0;
	// Traiter tous les heredocs AVANT les pipes
	if (setup_pipeline_heredocs(commands, cmd_count, data) == -1)
		return (-1);
	while (i < cmd_count)
	{
		if (create_pipe_if_needed(i, cmd_count, pipe_fd) == -1)
			return (-1);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		if (pid == 0) // Processus enfant
		{
			pipe_data.cmd_index = i;
			pipe_data.pipe_fd = pipe_fd;
			pipe_data.prev_pipe = prev_pipe;
			pipe_data.cmd_count = cmd_count;
			execute_piped_command(commands[i], &pipe_data, data);
		}
		// Processus parent
		prev_pipe = handle_parent_process(pipe_fd, prev_pipe, (i == cmd_count
					- 1));
		i++;
	}
	return (wait_all_pipeline_children(cmd_count));
}
