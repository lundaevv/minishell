/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:29 by vlundaev          #+#    #+#             */
/*   Updated: 2026/01/20 15:16:48 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_unclosed_quotes(const char *line)
{
	int		i;
	char	q;

	i = 0;
	q = 0;
	while (line && line[i])
	{
		if (!q && (line[i] == '\'' || line[i] == '"'))
			q = line[i];
		else if (q && line[i] == q)
			q = 0;
		i++;
	}
	return (q != 0);
}

int	handle_unclosed_quotes(t_shell *shell, char *line)
{
	if (!has_unclosed_quotes(line))
		return (0);
	ft_putendl_fd("minishell: syntax error: unclosed quotes", STDERR_FILENO);
	shell->exit_status = 2;
	return (1);
}
