/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlundaev <vlundaev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:19 by vlundaev          #+#    #+#             */
/*   Updated: 2026/01/21 16:38:14 by vlundaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hd_str_add_char(char *s, char c)
{
	char	*new;
	size_t	len;

	len = 0;
	if (s)
		len = ft_strlen(s);
	new = malloc(len + 2);
	if (!new)
		return (free(s), NULL);
	if (s)
		ft_memcpy(new, s, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(s);
	return (new);
}

int	hd_write_line(int wfd, char *line)
{
	write(wfd, line, ft_strlen(line));
	free(line);
	return (0);
}
