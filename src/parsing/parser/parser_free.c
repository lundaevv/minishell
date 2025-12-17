/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:15:26 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/17 19:03:56 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	if (cmd->redirs)
	{
		i = 0;
		while (i < cmd->redir_count)
		{
			free(cmd->redirs[i].target);
			i++;
		}
		free(cmd->redirs);
	}
}

void	free_pipeline(t_pipeline *p)
{
	int	i;

	if (!p)
		return ;
	if (!p->cmds)
	{
		free(p);
		return ;
	}
	i = 0;
	while (i < p->cmd_count)
	{
		free_cmd(&p->cmds[i]);
		i++;
	}
	free(p->cmds);
	free(p);
}
