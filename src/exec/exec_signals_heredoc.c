/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperedny <gperedny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:55:55 by gperedny          #+#    #+#             */
/*   Updated: 2026/01/22 14:56:23 by gperedny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
}

void	signals_heredoc(void)
{
	struct sigaction	sa;

	g_signal = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_heredoc;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
