/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:43:22 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/04 15:56:27 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static int	var_name_len(const char *s)
{
	int	len;

	len = 0;
	while (s[len] && (ft_isalnum(s[len]) || s[len] == '_'))
		len++;
	return (len);
}

static char	*get_env_value(const char *name, int len, char **envp)
{
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

/*
** Expand a single $VAR at position *i.
** Returns malloc'ed string or empty strdup("").
** Advances *i past the variable name.
*/
static char	*expand_single_var(const char *value, int *i, char **envp)
{
	int		len;
	char	*env_val;

	(*i)++; // skip '$'
	len = var_name_len(&value[*i]);
	env_val = get_env_value(&value[*i], len, envp);
	*i += len;
	if (!env_val)
		return (ft_strdup(""));
	return (ft_strdup(env_val));
}

/*
** Expand all $VAR occurrences. No quote handling yet.
*/
char	*expand_variables_in_value(const char *value, char **envp)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && is_var_start(value[i + 1]))
		{
			tmp = expand_single_var(value, &i, envp);
		}
		else
		{
			tmp = ft_substr(value, i, 1);
			i++;
		}
		result = ft_strjoin(result, tmp);
		free(tmp);
		if (!result)
			return (NULL);
	}
	return (result);
}
