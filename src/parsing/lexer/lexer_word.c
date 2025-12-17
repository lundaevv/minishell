/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:37:24 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/03 19:28:43 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Read a WORD token starting at *i.
** Keeps quotes inside the token for now.
** Stops on space/tab/operator when not inside quotes.
** Advances *i to the first character after the word.
*/
t_token	*lexer_read_word(const char *line, int *i)
{
	int	start;
	int	in_single;
	int	in_double;

	start = *i;
	in_single = 0;
	in_double = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[*i] == '\"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double
			&& (is_space(line[*i]) || line[*i] == '|'
				|| line[*i] == '<' || line[*i] == '>'))
			break ;
		(*i)++;
	}
	return (token_new(ft_substr(line, start, *i - start), TOKEN_WORD));
}
