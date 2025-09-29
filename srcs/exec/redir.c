#include "minishell.h"

int setup_redirections(t_cmd *cmd, t_data *data)
{
    int i;
    int fd;

    if (!cmd || !cmd->redirects)
        return (0);

    i = 0;
    while (i < cmd->redirect_count)
    {
        if (cmd->redirects[i].type == TOKEN_REDIR_IN) // <
        {
            fd = open(cmd->redirects[i].file, O_RDONLY);
            if (fd == -1)
            {
                perror(cmd->redirects[i].file);
                data->exit_status = 1;
                return (-1);
            }
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                perror("dup2");
                close(fd);
                return (-1);
            }
            close(fd);
        }
        else if (cmd->redirects[i].type == TOKEN_REDIR_OUT) // >
        {
            fd = open(cmd->redirects[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror(cmd->redirects[i].file);
                data->exit_status = 1;
                return (-1);
            }
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                close(fd);
                return (-1);
            }
            close(fd);
        }
        else if (cmd->redirects[i].type == TOKEN_REDIR_APPEND) // >>
        {
            fd = open(cmd->redirects[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror(cmd->redirects[i].file);
                data->exit_status = 1;
                return (-1);
            }
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                close(fd);
                return (-1);
            }
            close(fd);
        }
        i++;
    }
    return (0);
}

void restore_std_fds(t_data *data)
{
    if (data->stdin_backup != -1)
    {
        dup2(data->stdin_backup, STDIN_FILENO);
        close(data->stdin_backup);
        data->stdin_backup = -1;
    }
    if (data->stdout_backup != -1)
    {
        dup2(data->stdout_backup, STDOUT_FILENO);
        close(data->stdout_backup);
        data->stdout_backup = -1;
    }
}

int backup_std_fds(t_data *data)
{
    data->stdin_backup = dup(STDIN_FILENO);
    data->stdout_backup = dup(STDOUT_FILENO);

    if (data->stdin_backup == -1 || data->stdout_backup == -1)
    {
        perror("backup fds");
        return (-1);
    }
    return (0);
}
