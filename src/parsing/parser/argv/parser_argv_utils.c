/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:17:45 by lundaevv          #+#    #+#             */
/*   Updated: 2025/12/17 18:20:50 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Skip one redirection token and its WORD target if present. */
void    skip_redir_pair(t_token **cur)
{
	if (!cur || !*cur)
		return ;
	*cur = (*cur)->next;
	if (*cur && (*cur)->type == TOKEN_WORD)
		*cur = (*cur)->next;
}
int free_argv_partial(char **argv, int filled)
{
	while (filled > 0)
	{
		filled--;
		free(argv[filled]);
	}
	return (1);
}
