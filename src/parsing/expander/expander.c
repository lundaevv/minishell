/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:08:14 by vlundaev          #+#    #+#             */
/*   Updated: 2026/01/21 16:50:59 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Expand all tokens before parsing.
** "$?" and VAR in WORD tokens.
**
** IMPORTANT:
** Do NOT expand heredoc limiter:
**   cat << $EOF
** limiter must stay literal (bash behavior).
*/
int	expand_tokens(t_token *list, char **envp, int last_exit_status)
{
	char	*new_value;

	while (list)
	{
		if (list->type == TOKEN_HEREDOC)
		{
			if (list->next && list->next->type == TOKEN_WORD)
				list = list->next;
			list = list->next;
			continue ;
		}
		if (list->type == TOKEN_WORD)
		{
			new_value = ms_expand_unquote(list->value, envp, last_exit_status);
			if (!new_value)
				return (1);
			free(list->value);
			list->value = new_value;
		}
		list = list->next;
	}
	return (0);
}
