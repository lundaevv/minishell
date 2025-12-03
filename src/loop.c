/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:12:40 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/02 19:59:04 by vlundaev         ###   ########.fr       */
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
* Main interactive loop:
*   - show prompt
*   - read an input line
*   - add non-empty lines to history
*   - exit on "exit" ot Ctrl+D
*
*   -- for now just echo the input line (ft_putstr_fd, ft_putendl_fd...)
*/

void	shell_loop(t_shell *shell)
{
	char	*line;
	t_token	*tokens;

	line = NULL;
	tokens = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (line[0] != '\0')
			add_history(line);
		if (is_exit_command(line))
		{
			free(line);
			shell->exit_status = 0;
			break ;
		}
		ft_putstr_fd("You typed: ", STDOUT_FILENO);
		ft_putendl_fd(line, STDOUT_FILENO);
		tokens = lexer_tokenize(line);
		token_list_print(tokens);
		token_list_clear(&tokens);
		free(line);
	}
}
