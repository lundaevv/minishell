/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_unquote_run.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 23:04:57 by lundaevv          #+#    #+#             */
/*   Updated: 2026/01/19 15:52:27 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_copy_str(char *dst, int *j, const char *src)
{
	int	k;

	k = 0;
	while (src && src[k])
	{
		dst[*j] = src[k];
		(*j)++;
		k++;
	}
}

static void	ms_copy_status(char *dst, int *j, void **ctx)
{
	char	*s;
	int		st;

	st = *(int *)ctx[1];
	s = ft_itoa(st);
	if (!s)
		return ;
	ms_copy_str(dst, j, s);
	free(s);
}

static void	ms_copy_dollar(char *dst, int *j, const char **p, void **ctx)
{
	int		len;
	char	*val;

	if ((*p)[1] == '?')
		return (*p += 2, ms_copy_status(dst, j, ctx));
	if (ms_is_var_start((*p)[1]))
	{
		len = ms_var_name_len((*p) + 1);
		val = ms_get_env_value((*p) + 1, len, (char **)ctx[0]);
		*p += 1 + len;
		if (val)
			ms_copy_str(dst, j, val);
		return ;
	}
	dst[(*j)++] = *(*p)++;
}

static int	ms_quote_step(const char **p, char *q)
{
	if (*q == 0 && (**p == '\'' || **p == '"'))
	{
		*q = **p;
		(*p)++;
		return (1);
	}
	if (*q == '\'' && **p == '\'')
	{
		*q = 0;
		(*p)++;
		return (1);
	}
	if (*q == '"' && **p == '"')
	{
		*q = 0;
		(*p)++;
		return (1);
	}
	return (0);
}

int	ms_expand_run(char *dst, const char *src, void **ctx)
{
	const char	*p;
	int			j;
	char		q;

	p = src;
	j = 0;
	q = 0;
	while (p && *p)
	{
		if (ms_quote_step(&p, &q))
			continue ;
		if (*p == '$' && q != '\'')
			ms_copy_dollar(dst, &j, &p, ctx);
		else
		{
			dst[j] = *p;
			j++;
			p++;
		}
	}
	return (j);
}
