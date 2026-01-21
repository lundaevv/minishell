/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:17:45 by lundaevv          #+#    #+#             */
/*   Updated: 2026/01/21 16:50:29 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Skip one redirection token and its WORD target if present. */
void	skip_redir_pair(t_token **cur)
{
	if (!cur || !*cur)
		return ;
	*cur = (*cur)->next;
	if (*cur && (*cur)->type == TOKEN_WORD)
		*cur = (*cur)->next;
}

int	free_argv_partial(char **argv, int filled)
{
	while (filled > 0)
	{
		filled--;
		free(argv[filled]);
	}
	return (1);
}
