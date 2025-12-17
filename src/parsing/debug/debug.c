/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:18:50 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/17 18:57:08 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*redir_name(t_redir_type t)
{
	if (t == REDIR_IN) return ("<");
	if (t == REDIR_OUT) return (">");
	if (t == REDIR_APPEND) return (">>");
	if (t == REDIR_HEREDOC) return ("<<");
	return ("?");
}

static void	ms_debug_redirs(t_cmd *cmd)
{
	int	i;

	printf("  redir_count = %d\n", cmd->redir_count);
	if (!cmd->redirs)
		return ;
	i = 0;
	while (i < cmd->redir_count)
	{
		printf("  redir[%d]: op=%s target='%s'\n",
			i, redir_name(cmd->redirs[i].type),
			cmd->redirs[i].target);
		i++;
	}
}

/*
** Debug print of tokens
*/
void	token_list_print(t_token *list)
{
	while (list)
	{
		if (list->type == TOKEN_WORD)
			ft_printf("WORD					: '%s'\n", list->value);
		else if (list->type == TOKEN_PIPE)
			ft_printf("PIPE					: '%s'\n", list->value);
		else if (list->type == TOKEN_REDIR_IN)
			ft_printf("REDIR_IN				: '%s'\n", list->value);
		else if (list->type == TOKEN_REDIR_OUT)
			ft_printf("REDIR_OUT				: '%s'\n", list->value);
		else if (list->type == TOKEN_REDIR_APPEND)
			ft_printf("REDIR_APPEND				: '%s'\n", list->value);
		else if (list->type == TOKEN_HEREDOC)
			ft_printf("HEREDOC					: '%s'\n", list->value);
		list = list->next;
	}
}

static void	ms_debug_line(const char *line)
{
	if (!line)
		return ;
	ft_putstr_fd("You typed: ", STDOUT_FILENO);
	ft_putendl_fd((char *)line, STDOUT_FILENO);
}

static void	ms_debug_tokens(t_token *tokens)
{
	if (!tokens)
		return ;
	token_list_print(tokens);
}

/*
** Print argv for each command in the pipeline (if present).
** Limit to 50 args to avoid infinite loop if argv is not NULL-terminated.
*/
static void	ms_debug_pipeline(t_pipeline *p)
{
	int	i;
	int	j;

	if (!p || p->cmd_count <= 0)
		return ;
	j = 0;
	while (j < p->cmd_count)
	{
		printf("CMD[%d] argv:\n", j);
		if (p->cmds[j].argv)
		{
			i = 0;
			while (p->cmds[j].argv[i] && i < 50)
			{
				printf("  argv[%d] = '%s'\n", i, p->cmds[j].argv[i]);
				i++;
			}
			if (i == 50 && p->cmds[j].argv[i] != NULL)
				printf("  (stop: argv not NULL-terminated?)\n");
		}

		printf("CMD[%d] redirs:\n", j);
		ms_debug_redirs(&p->cmds[j]);

		j++;
	}
}

/*
** Global debug entry point. Call this once per line.
*/
void	ms_debug_state(t_shell *shell, const char *line,
			t_token *tokens, t_pipeline *p)
{
	(void)shell;
	ms_debug_line(line);
	ms_debug_tokens(tokens);
	ms_debug_pipeline(p);
}

void	ms_debug_counts(t_token *tokens)
{
	printf("DEBUG words_no_redirs=%d\n", count_words_no_redirs(tokens));
	printf("DEBUG redirs=%d\n", count_redirs_simple(tokens));
}
