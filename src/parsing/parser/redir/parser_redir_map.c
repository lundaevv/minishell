/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:45:16 by lundaevv          #+#    #+#             */
/*   Updated: 2026/01/21 16:50:10 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_to_redir_type(t_token_type t, t_redir_type *out)
{
	if (!out)
		return (1);
	if (t == TOKEN_REDIR_IN)
		*out = REDIR_IN;
	else if (t == TOKEN_REDIR_OUT)
		*out = REDIR_OUT;
	else if (t == TOKEN_REDIR_APPEND)
		*out = REDIR_APPEND;
	else if (t == TOKEN_HEREDOC)
		*out = REDIR_HEREDOC;
	else
		return (1);
	return (0);
}
