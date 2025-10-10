#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t g_signal = 0;

void handler(int sig)
{
    (void)sig;
    g_signal = 1;
    write(1, "\nHANDLER\n", 9);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

int main(void)
{
    char *line;

    signal(SIGINT, handler);
    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
            break;
        printf("LINE: %s\n", line);
        free(line);
    }
    return 0;
}
