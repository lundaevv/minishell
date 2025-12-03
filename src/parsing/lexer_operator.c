/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:09:51 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/03 19:01:35 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*lexer_read_less(const char *line, int *i)
{
	if (line[*i + 1] == '<')
	{
		*i += 2;
		return (token_new(ft_strdup("<<"), TOKEN_HEREDOC));
	}
	(*i)++;
	return (token_new(ft_strdup("<"), TOKEN_REDIR_IN));
}

static t_token	*lexer_read_greater(const char *line, int *i)
{
	if (line[*i + 1] == '>')
	{
		*i += 2;
		return (token_new(ft_strdup(">>"), TOKEN_REDIR_APPEND));
	}
	(*i)++;
	return (token_new(ft_strdup(">"), TOKEN_REDIR_OUT));
}

/*
** Read an operator token at position *i:
**  |   -> TOKEN_PIPE
**  <   -> TOKEN_REDIR_IN or TOKEN_HEREDOC
**  >   -> TOKEN_REDIR_OUT or TOKEN_REDIR_APPEND
** Advances *i to the first character after the operator.
*/
t_token	*lexer_read_operator(const char *line, int *i)
{
	if (line[*i] == '|')
	{
		(*i)++;
		return (token_new(ft_strdup("|"), TOKEN_PIPE));
	}
	if (line[*i] == '<')
		return (lexer_read_less(line, i));
	if (line[*i] == '>')
		return (lexer_read_greater(line, i));
	return (NULL);
}
