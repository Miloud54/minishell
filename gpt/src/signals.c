#include "../inc/minishell.h"

volatile sig_atomic_t g_last_signal = 0;

void sigint_handler(int signo)
{
    (void)signo;
    g_last_signal = SIGINT;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void sigquit_handler(int signo)
{
    (void)signo;
    /* Bash ignores SIGQUIT in interactive mode; keep prompt clean */
    rl_on_new_line();
    rl_redisplay();
}

void setup_signal_handlers(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = sigquit_handler;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa_quit, NULL);
}
