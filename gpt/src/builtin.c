#include "../inc/minishell.h"

/* Recognize simple builtins: echo and exit for starter */
int is_builtin(char **argv)
{
    if (!argv || !argv[0]) return 0;
    if (strcmp(argv[0], "echo") == 0) return 1;
    if (strcmp(argv[0], "exit") == 0) return 1;
    return 0;
}

int run_builtin(char **argv)
{
    if (!argv || !argv[0]) return 1;
    if (strcmp(argv[0], "echo") == 0)
    {
        int i = 1, nl = 1;
        if (argv[1] && strcmp(argv[1], "-n") == 0) { nl = 0; i = 2; }
        for (; argv[i]; ++i)
        {
            if (i > (nl ? 1 : 2)) putchar(' ');
            fputs(argv[i], stdout);
        }
        if (nl) putchar('\n');
        return 0;
    }
    if (strcmp(argv[0], "exit") == 0)
    {
        int code = 0;
        if (argv[1]) code = atoi(argv[1]);
        rl_clear_history();
        _exit(code); /* exit the shell process */
    }
    return 1;
}
