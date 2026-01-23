/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:07:50 by vlundaev          #+#    #+#             */
/*   Updated: 2026/01/23 14:02:32 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec_error_code(void)
{
	if (errno == EACCES || errno == EISDIR)
		return (MS_CMD_NOT_EXECUTABLE);
	return (MS_CMD_NOT_FOUND);
}

static int	ms_has_slash(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int	ms_is_dir(const char *path)
{
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

static void	exec_with_slash(t_cmd *cmd, char **envp)
{
	if (ms_is_dir(cmd->argv[0]))
	{
		errno = EISDIR;
		perror(cmd->argv[0]);
		exit(MS_CMD_NOT_EXECUTABLE);
	}
	execve(cmd->argv[0], cmd->argv, envp);
	perror(cmd->argv[0]);
	exit(ms_exec_error_code());
}

void	exec_cmd(t_cmd *cmd, char **envp)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(MS_SUCCESS);
	if (cmd->argv[0][0] == '\0')
	{
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(MS_CMD_NOT_FOUND);
	}
	if (ms_has_slash(cmd->argv[0]))
		exec_with_slash(cmd, envp);
	ms_exec_with_path(cmd, envp);
}
