/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:37:24 by vlundaev          #+#    #+#             */
/*   Updated: 2026/01/19 12:10:54 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lex_word_advance(const char *line, int *i, int *has_quotes)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	*has_quotes = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[*i] == '\"' && !in_single)
			in_double = !in_double;
		if (line[*i] == '\'' || line[*i] == '\"')
			*has_quotes = 1;
		else if (!in_single && !in_double
			&& (is_space(line[*i]) || line[*i] == '|'
				|| line[*i] == '<' || line[*i] == '>'))
			break ;
		(*i)++;
	}
	return (0);
}

/*
** Read a WORD token starting at *i.
** Keeps quotes inside the token for now.
** Stops on space/tab/operator when not inside quotes.
** Advances *i to the first character after the word.
*/
t_token	*lexer_read_word(const char *line, int *i)
{
	int		start;
	int		has_quotes;
	t_token	*tok;

	start = *i;
	lex_word_advance(line, i, &has_quotes);
	tok = token_new(ft_substr(line, start, *i - start), TOKEN_WORD);
	if (!tok)
		return (NULL);
	tok->has_quotes = (has_quotes != 0);
	return (tok);
}
