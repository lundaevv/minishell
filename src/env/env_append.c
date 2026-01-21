/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:17:52 by vlundaev          #+#    #+#             */
/*   Updated: 2026/01/21 16:18:01 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_count(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

static void	env_copy_ptrs(char **dst, char **src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

int	env_append_kv(t_shell *sh, char *kv)
{
	int		count;
	char	**newenv;

	if (!sh || !sh->envp || !kv)
		return (1);
	count = env_count(sh->envp);
	newenv = (char **)malloc(sizeof(char *) * (count + 2));
	if (!newenv)
		return (1);
	env_copy_ptrs(newenv, sh->envp, count);
	newenv[count] = kv;
	newenv[count + 1] = NULL;
	free(sh->envp);
	sh->envp = newenv;
	return (0);
}
