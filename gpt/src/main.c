#include "../inc/minishell.h"

/* Declaration of setup function from signals.c */
void setup_signal_handlers(void);

int main(int argc, char **argv, char **envp)
{
    char *line;
    (void)argc; (void)argv;

    setup_signal_handlers();

    while (1)
    {
        line = readline("minishell$ ");
        if (!line) /* Ctrl-D */
        {
            printf("exit\n");
            break;
        }

        if (*line)
            add_history(line);

        char **tokens = tokenize(line);
        if (tokens && tokens[0])
        {
            int rc = execute_pipeline(tokens, envp);
            (void)rc; /* store to $? later */
        }
        free_tokens(tokens);
        free(line);
    }
    return 0;
}
