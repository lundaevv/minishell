/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:57:02 by lundaevv          #+#    #+#             */
/*   Updated: 2026/01/23 13:36:36 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Count arguments and malloc for argv
*/
static char	**alloc_argv_simple(t_token *tokens, int *count)
{
	char	**argv;

	*count = count_words_no_redirs(tokens);
	argv = (char **)malloc(sizeof(char *) * (size_t)(*count + 1));
	if (!argv)
		return (NULL);
	return (argv);
}

/*
** Fills argv with strings
*/
static int	fill_argv_simple(char **argv, t_token *t)
{
	int	i;

	i = 0;
	while (t && t->type != TOKEN_PIPE)
	{
		if (is_redir_token(t->type))
			skip_redir_pair(&t);
		else if (t->type == TOKEN_WORD && (t->has_quotes || t->value[0]))
		{
			argv[i] = ft_strdup(t->value);
			if (!argv[i])
				return (free_argv_partial(argv, i));
			i++;
			t = t->next;
		}
		else
			t = t->next;
	}
	argv[i] = NULL;
	return (0);
}

/*
** Combine 2: count and initialize the array + fill it
** returns argv
*/
char	**build_argv_simple(t_token *tokens)
{
	char	**argv;
	int		count;

	argv = alloc_argv_simple(tokens, &count);
	if (!argv)
		return (NULL);
	if (fill_argv_simple(argv, tokens))
	{
		free(argv);
		return (NULL);
	}
	return (argv);
}
