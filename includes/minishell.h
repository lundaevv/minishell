/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:52:15 by vlundaev          #+#    #+#             */
/*   Updated: 2025/12/03 18:59:03 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"

// Main shell state
// More fields will be added later (env list, tokens, commands, etc.)
typedef struct s_shell
{
	int		exit_status;
	char	**env;
}	t_shell;

// Token types
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

// Single token in a linked list
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// Main minishell loop
void	shell_loop(t_shell *shell);

// Lexer main: split an anput line into a linked list of tokens
t_token	*lexer_tokenize(const char *line);

// Token utils:
t_token	*token_new(char *value, t_token_type type);
void	token_add_back(t_token **list, t_token *new_node);
void	token_list_print(t_token *list);
void	token_list_clear(t_token **list);
int		is_space(char c);

// Lexer helpers:
t_token	*lexer_read_operator(const char *line, int *i);
t_token	*lexer_read_word(const char *line, int *i);

#endif