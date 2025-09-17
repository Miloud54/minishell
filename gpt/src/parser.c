#include "../inc/minishell.h"

/* Simple tokenizer:
   - split on spaces
   - supports "double quotes" and 'single quotes' (no escape handling)
   - returns NULL-terminated array of strings (malloc'd)
*/

static char *substr_dup(const char *s, size_t len)
{
    char *r = malloc(len + 1);
    if (!r) return NULL;
    memcpy(r, s, len);
    r[len] = '\0';
    return r;
}

char **tokenize(const char *line)
{
    size_t cap = 8;
    size_t count = 0;
    char **arr = malloc(sizeof(char*) * cap);
    if (!arr) return NULL;

    const char *p = line;
    while (*p)
    {
        while (isspace((unsigned char)*p)) p++;
        if (!*p) break;

        const char *start = p;
        if (*p == '\'' || *p == '"')
        {
            char quote = *p++;
            start = p;
            while (*p && *p != quote) p++;
            arr[count++] = substr_dup(start, p - start);
            if (*p == quote) p++;
        }
        else
        {
            start = p;
            while (*p && !isspace((unsigned char)*p) && *p != '\'' && *p != '"') p++;
            arr[count++] = substr_dup(start, p - start);
        }

        if (count + 1 >= cap)
        {
            cap *= 2;
            char **tmp = realloc(arr, sizeof(char*) * cap);
            if (!tmp) { /* leak on error, keep simple for this starter */ break; }
            arr = tmp;
        }
    }
    arr[count] = NULL;
    return arr;
}

void free_tokens(char **tokens)
{
    if (!tokens) return;
    for (size_t i = 0; tokens[i]; ++i)
        free(tokens[i]);
    free(tokens);
}
