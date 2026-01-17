#include "minishell.h"

/*

This file implements HEREDOC (<< limiter).

Parser gives redirection:
    { REDIR_HEREDOC, "EOF" }

Execution rule:
- When we see REDIR_HEREDOC, we must read user input until a line equals limiter.
- All collected text becomes stdin for the command.
- We implement this using a pipe:
      write-end: we write user lines into it
      read-end : we dup2() it to STDIN later

Important behavior:
- If user presses Ctrl-C during heredoc:
      heredoc stops immediately
      command must NOT execute
      exit status must become 130 (bash style)

I handle Ctrl-C using global g_signal.
signals_interactive() sets SIGINT handler that sets g_signal = SIGINT.
So heredoc can detect Ctrl-C even while reading.

Return convention (very important for apply_redirections):
- heredoc_open() returns:
      >= 0  : fd to use as stdin (pipe read end)
      -130  : heredoc canceled by Ctrl-C (special status)
      -1    : error

 */

/*
Helper: append one char to a string.
Used because we read heredoc input char-by-char.
This is slow but simple and works for minishell.

s can be NULL -> treated like empty string.
Returns new malloc string, frees old s.
*/
static char *str_add_char(char *s, char c)
{
    char    *new;
    size_t  len;

    len = 0;
    if (s)
        len = ft_strlen(s);

    new = malloc(len + 2);
    if (!new)
        return (free(s), NULL);

    if (s)
        ft_memcpy(new, s, len);

    new[len] = c;
    new[len + 1] = '\0';
    free(s);
    return (new);
}

/*
Read one line from stdin manually using read(1 byte).
Stops after '\n' or EOF.

Returns malloc'ed string with '\n' included.
Returns NULL on EOF or error.
*/
static char *read_heredoc_line(void)
{
    char    *line;
    char    c;
    ssize_t r;

    line = NULL;
    while (1)
    {
        r = read(STDIN_FILENO, &c, 1);
        if (r <= 0)
            break;

        line = str_add_char(line, c);
        if (!line)
            return (NULL);

        if (c == '\n')
            break;
    }
    return (line);
}

/*
Check if line equals limiter + '\n'.
Example:
    limiter = "EOF"
    line    = "EOF\n" -> true
*/
static int is_limiter_line(char *line, const char *limiter)
{
    size_t n;

    if (!line || !limiter)
        return (0);
    n = ft_strlen(limiter);
    return (ft_strncmp(line, limiter, n) == 0 && line[n] == '\n');
}

/*
Fill the heredoc pipe with user input until limiter appears.

We write prompt "> " (like bash).
We stop when:
- user typed limiter line
- EOF
- Ctrl-C happened

Return:
    0   -> ok
    130 -> canceled by Ctrl-C
*/
static int heredoc_fill(int wfd, const char *limiter)
{
    char *line;

    while (1)
    {
        /* If Ctrl-C already happened, stop immediately */
        if (g_signal == SIGINT)
            return (130);

        /* heredoc prompt */
        write(STDOUT_FILENO, "> ", 2);

        /* read one line */
        line = read_heredoc_line();
        if (!line)
            break;

        /* If Ctrl-C happened during read, stop */
        if (g_signal == SIGINT)
            return (free(line), 130);

        /* limiter -> finish heredoc */
        if (is_limiter_line(line, limiter))
        {
            free(line);
            break;
        }

        /* normal line -> write into heredoc pipe */
        write(wfd, line, ft_strlen(line));
        free(line);
    }
    return (0);
}

/*
Create heredoc pipe, fill it, and return READ end.

Pipe:
    hd[1] = write end (we write heredoc text here)
    hd[0] = read end  (command will read from here after dup2)

Return:
    >= 0  : fd read end to be used as stdin
    -130  : heredoc canceled by Ctrl-C (special)
    -1    : pipe/error
*/
int heredoc_open(const char *limiter)
{
    int hd[2];
    int ret;

    if (pipe(hd) < 0)
    {
        perror("pipe");
        return (-1);
    }

    /* Reset signal state for heredoc read loop */
    g_signal = 0;

    /* Fill write end with lines */
    ret = heredoc_fill(hd[1], limiter);

    /* Close write end: important so command sees EOF when done reading */
    close(hd[1]);

    /* Ctrl-C: close read end too, return special status */
    if (ret == 130)
    {
        close(hd[0]);
        return (-130);
    }

    /* Success: return read end */
    return (hd[0]);
}
