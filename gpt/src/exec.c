#include "../inc/minishell.h"

int execute_pipeline(char **argv, char **envp)
{
    pid_t pid;
    int status;

    if (is_builtin(argv))
    {
        /* builtins executed in parent for this simple starter */
        return run_builtin(argv);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        /* child */
        if (find_and_exec(argv, envp) == -1)
        {
            /* exec failed */
            fprintf(stderr, "%s: command not found\n", argv[0]);
            _exit(127);
        }
    }
    /* parent */
    if (waitpid(pid, &status, 0) == -1)
    {
        perror("waitpid");
        return 1;
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 1;
}
