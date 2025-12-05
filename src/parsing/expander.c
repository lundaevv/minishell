/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:08:14 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/05 15:56:42 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Count how many times "$?" appears in the string.
*/
static int	count_status_markers(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] == '?')
			count++;
		i++;
	}
	return (count);
}

/*
** Copy status_str into dst, advancing *j.
*/
static void	copy_status_str(char *dst, int *j, const char *status_str)
{
	int	k;

	k = 0;
	while (status_str[k] != '\0')
	{
		dst[*j] = status_str[k];
		(*j)++;
		k++;
	}
}

/*
** Allocate a new string where all "$?" are replaced
** by status_str. 'count' is the number of "$?" in src.
*/
static char	*replace_status_markers(
	const char *src, const char *status_str, int count)
{
	int		len_src;
	int		len_status;
	char	*dst;
	int		i;
	int		j;

	len_src = ft_strlen(src);
	len_status = ft_strlen(status_str);
	dst = (char *)malloc(len_src + count * (len_status - 2) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '$' && src[i + 1] == '?')
		{
			copy_status_str(dst, &j, status_str);
			i += 2;
		}
		else
			dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (dst);
}

/*
** Expand "$?" inside a single token value.
** Returns a newly allocated string, or NULL on error.
*/
static char	*expand_status_in_value(const char *value, int status)
{
	char	*status_str;
	int		count;
	char	*result;

	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	count = count_status_markers(value);
	if (count == 0)
	{
		free(status_str);
		return (ft_strdup(value)); // protect?
	}
	result = replace_status_markers(value, status_str, count);
	free(status_str);
	return (result);
}

/*
** Expand all tokens before parsing.
** For now: only "$?" in WORD tokens.
*/
int	expand_tokens(t_token *list, char **envp, int last_status)
{
	char	*new_val;

	(void)envp;
	while (list)
	{
		if (list->type == TOKEN_WORD)
		{
			new_val = expand_status_in_value(list->value, last_status);
			if (!new_val)
				return (1);
			free(list->value);
			list->value = new_val;
		}
		list = list->next;
	}
	return (0);
}
