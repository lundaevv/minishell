/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:06:52 by lundaevv          #+#    #+#             */
/*   Updated: 2026/01/21 16:08:09 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipeline(t_shell *sh, t_pipeline *p)
{
	if (!p || p->cmd_count <= 0)
		return (sh->exit_status = 0);
	if (p->cmd_count == 1)
		return (exec_pipeline_single(sh, &p->cmds[0]));
	return (exec_pipeline_multi(sh, p));
}
