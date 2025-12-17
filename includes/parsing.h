/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:44:33 by lundaevv          #+#    #+#             */
/*   Updated: 2025/12/17 21:51:14 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <stdlib.h>

/*
** =========================
** Token layer (lexer output)
** =========================
*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/*
** =========================
** Parser output (execution input)
** =========================
*/
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	t_redir	*redirs;
	int		redir_count;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd	*cmds;
	int		cmd_count;
}	t_pipeline;

/*
** =========================
** Lexer (public)
** =========================
*/
t_token		*lexer_tokenize(const char *line);

/*
** Token utils (used by lexer and other parsing code)
*/
t_token		*token_new(char *value, t_token_type type);
void		token_add_back(t_token **list, t_token *new_node);
void		token_list_print(t_token *list);
void		token_list_clear(t_token **list);
int			is_space(char c);

/*
** Lexer helpers (non-static in your project)
*/
t_token		*lexer_read_operator(const char *line, int *i);
t_token		*lexer_read_word(const char *line, int *i);

/*
** =========================
** Expander
** =========================
*/
int			expand_tokens(t_token *list, char **envp, int last_status);
char		*expand_variables_in_value(const char *value, char **envp);

/*
** =========================
** Syntax validation
** =========================
*/
int			validate_syntax(t_token *token);

/*
** =========================
** Parser (public)
** =========================
*/
t_pipeline	*parse_pipeline(t_token *tokens);
void		free_pipeline(t_pipeline *p);

/*
** Parser utils
*/
int			count_commands(t_token *tokens);
void		init_cmd_array(t_cmd *cmds, int count);
int			count_words_simple(t_token *tokens);

/*
** argv building
*/
char		**build_argv_simple(t_token *tokens);
int			is_redir_token(t_token_type type);
int			count_words_no_redirs(t_token *tokens);
void		skip_redir_pair(t_token **cur);
int			free_argv_partial(char **argv, int filled);

/*
** redir building
*/
int			count_redirs_simple(t_token *tokens);
int			token_to_redir_type(t_token_type t, t_redir_type *out);
t_redir		*build_redirs_simple(t_token *tokens, int *out_count);

/*
** pipeline builder (fills cmds[])
*/
int			build_pipeline_cmds(t_pipeline *p, t_token *tokens);

/*
** =========================
** Debug
** =========================
** Чтобы избежать циклической зависимости, используем forward-declare t_shell.
*/
struct s_shell;
void		ms_debug_state(struct s_shell *shell, const char *line,
				t_token *tokens, t_pipeline *p);
void		ms_debug_counts(t_token *tokens);

#endif