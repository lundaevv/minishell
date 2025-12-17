/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lundaevv <lundaevv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:43:14 by lundaevv          #+#    #+#             */
/*   Updated: 2025/12/17 18:40:27 by lundaevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redir_token(t_token_type type)
{
    return (type == TOKEN_REDIR_IN
        || type == TOKEN_REDIR_OUT
        || type == TOKEN_REDIR_APPEND
        || type == TOKEN_HEREDOC);
}
