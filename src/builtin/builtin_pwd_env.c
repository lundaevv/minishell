/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:05:48 by vlundaev          #+#    #+#             */
/*   Updated: 2026/01/21 16:05:49 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(void)
{
	char	buf[4096];

	if (!getcwd(buf, sizeof(buf)))
	{
		perror("pwd");
		return (1);
	}
	write(STDOUT_FILENO, buf, ft_strlen(buf));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	bi_env(t_shell *sh)
{
	if (!sh)
		return (1);
	env_print(sh->envp);
	return (0);
}
