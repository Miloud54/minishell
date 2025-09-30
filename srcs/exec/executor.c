#include "minishell.h"

int execute_commands(t_cmd **commands, int cmd_count, t_data *data)
{
    int exit_code = 0;

    if (!commands || cmd_count == 0)
        return (0);
    /* Pour l'instant, une seule commande (pas de pipes) */
    if (cmd_count == 1)
    {
        exit_code = execute_single_command(commands[0], data);
    }
    else
    {
        /* A faire: Phase 6 - Pipes */
        ft_putendl_fd("minishell: pipes not implemented yet", 2);
        data->exit_status = 1;
        exit_code = 1;
    }

    return (exit_code);
}
