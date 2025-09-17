#include "../inc/minishell.h"

/* join path + "/" + bin (allocates a new string) */
static char *join_path_bin(const char *path, const char *bin)
{
    size_t a = strlen(path), b = strlen(bin);
    char *r = malloc(a + 1 + b + 1);
    if (!r) return NULL;
    memcpy(r, path, a);
    r[a] = '/';
    memcpy(r + a + 1, bin, b);
    r[a + 1 + b] = '\0';
    return r;
}

/* If argv[0] contains '/', try it directly; otherwise search PATH */
int find_and_exec(char **argv, char **envp)
{
    if (!argv || !argv[0]) return -1;

    /* If path contains '/', attempt direct exec */
    if (strchr(argv[0], '/'))
    {
        execve(argv[0], argv, envp);
        return -1; /* execve only returns on error */
    }

    char *path_env = getenv("PATH");
    if (!path_env) return -1;

    char *paths = strdup(path_env);
    if (!paths) return -1;

    char *save = NULL;
    char *token = strtok_r(paths, ":", &save);
    while (token)
    {
        char *candidate = join_path_bin(token, argv[0]);
        if (candidate)
        {
            if (access(candidate, X_OK) == 0)
            {
                free(paths);
                execve(candidate, argv, envp);
                free(candidate);
                return -1;
            }
            free(candidate);
        }
        token = strtok_r(NULL, ":", &save);
    }
    free(paths);
    return -1;
}
