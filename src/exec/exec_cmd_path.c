/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperedny <gperedny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:47:59 by gperedny          #+#    #+#             */
/*   Updated: 2026/01/22 14:48:59 by gperedny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_with_path(t_cmd *cmd, char **envp)
{
	char	*path;

	path = resolve_path(cmd->argv[0], envp);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(MS_CMD_NOT_FOUND);
	}
	execve(path, cmd->argv, envp);
	perror(cmd->argv[0]);
	free(path);
	exit(ms_exec_error_code());
}
