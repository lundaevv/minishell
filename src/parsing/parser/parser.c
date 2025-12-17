/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:50:40 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/17 18:49:06 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Alloc and init t_pipeline
*/
static t_pipeline	*alloc_pipeline_struct(int cmd_count)
{
	t_pipeline	*p;

	p = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!p)
		return (NULL);
	p->cmd_count = cmd_count;
	p->cmds = (t_cmd *)malloc(sizeof(t_cmd) * (size_t)cmd_count);
	if (!p->cmds)
	{
		free(p);
		return (NULL);
	}
	init_cmd_array(p->cmds, cmd_count);
	return (p);
}

/*
** Build a simple pipeline structure from a token list.
** For now:
**  - count commands separated by PIPE
**  - allocate t_pipeline and its cmds array
**  - do not fill argv or redirections yet
*/
t_pipeline	*parse_pipeline(t_token *tokens)
{
	t_pipeline	*p;
	int			cmd_count;

	if (!tokens)
		return (NULL);
	cmd_count = count_commands(tokens);
	p = alloc_pipeline_struct(cmd_count);
	if (!p)
		return (NULL);
	if (build_pipeline_cmds(p, tokens) != 0)
	{
		free_pipeline(p);
		return (NULL);
	}
	return (p);
}
