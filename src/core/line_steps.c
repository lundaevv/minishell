/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:06:45 by lundaevv          #+#    #+#             */
/*   Updated: 2025/12/17 21:11:07 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	step_lex(char *line, t_token **tokens)
{
	*tokens = lexer_tokenize(line);
	if (!*tokens)
	{
		free(line);
		return (2);
	}
	return (0);
}

static int	step_expand(t_shell *shell, char *line, t_token **tokens)
{
	if (expand_tokens(*tokens, shell->env, shell->exit_status) != 0)
		return (handle_expand_error(tokens, line)); /* returns 0 */
	return (0);
}

static int	step_syntax(t_shell *shell, char *line, t_token **tokens)
{
	if (!validate_syntax(*tokens))
		return (0);
	shell->exit_status = 2;
	token_list_clear(tokens);
	free(line);
	return (2);
}

static void	step_parse_and_debug(t_shell *shell, char *line,
				t_token *tokens, t_pipeline **p)
{
	*p = parse_pipeline(tokens);
	ms_debug_counts(tokens);
	ms_debug_state(shell, line, tokens, *p);
}

int	line_build_state(t_shell *shell, char *line, t_token **out_tokens,
			t_pipeline **out_p)
{
	t_token		*tokens;
	t_pipeline	*p;
	int			rc;

	*out_tokens = NULL;
	*out_p = NULL;
	rc = step_lex(line, &tokens);
	if (rc != 0)
		return (rc);
	rc = step_expand(shell, line, &tokens);
	if (rc != 0)
		return (rc);
	rc = step_syntax(shell, line, &tokens);
	if (rc != 0)
		return (rc);
	step_parse_and_debug(shell, line, tokens, &p);
	*out_tokens = tokens;
	*out_p = p;
	return (0);
}
