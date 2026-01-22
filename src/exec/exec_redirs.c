/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperedny <gperedny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:07:34 by vlundaev          #+#    #+#             */
/*   Updated: 2026/01/22 19:24:52 by gperedny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redirections(t_shell *sh, t_cmd *cmd)
{
	int	i;
	int	r;

	if (!cmd || cmd->redir_count <= 0 || !cmd->redirs)
		return (0);
	i = 0;
	while (i < cmd->redir_count)
	{
		r = apply_one_redir(sh, &cmd->redirs[i]);
		if (r != 0)
			return (r);
		i++;
	}
	return (0);
}
