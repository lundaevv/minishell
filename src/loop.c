/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:12:40 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/05 15:56:38 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Return 1 if the line should be treated as an "exit" command.
* For now we handle:
*   - "exit"
*   - "exit" followed by a space and anything else.
*/
static int	is_exit_command(const char *line)
{
	if (!line || line[0] == '\0')
		return (0);
	if (ft_strncmp(line, "exit", 4) != 0)
		return (0);
	if (line[4] != '\0' && line[4] != ' ')
		return (0);
	return (1);
}

/*
** Readline:
** - Prints the prompt
** - Returns the line (malloc'ed at the &line)
** 			- or NULL (if only EOF (Ctrl+D) && empty line)
** - If NULL - prints exit and returns NULL
*/
static char	*read_line_with_prompt(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (NULL);
	}
	return (line);
}

/*
** Process a single input line:
** - history
** - "exit" command
** - debug print
** - tokenize, expand, debug tokens
*/
static int	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;

	if (line[0] != '\0')
		add_history(line);
	if (is_exit_command(line)) // exit handling - should be in exec??
	{
		free(line);
		shell->exit_status = 0;
		return (1);
	}
	ft_putstr_fd("You typed: ", STDOUT_FILENO); // debug
	ft_putendl_fd(line, STDOUT_FILENO); // debug
	tokens = lexer_tokenize(line);
	if (!tokens)
	{
		free(line);
		return (0);
	}
	expand_tokens(tokens, shell->env, shell->exit_status);
	token_list_print(tokens); // debug
	token_list_clear(&tokens); // free
	free(line);
	return (0);
}

/*
** Main shell loop:
** - Gets the input line (if NULL - stops)
** - Starts to process it
*/
void	shell_loop(t_shell *shell)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = read_line_with_prompt();
		if (!line)
			break ;
		if (process_line(shell, line)) // can be freed here instead of the function
			break ;
	}
}
