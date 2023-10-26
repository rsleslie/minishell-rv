/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:38:36 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/13 15:22:18 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handler_child_heredoc(int signal)
{
	if (signal == SIGINT)
		g_data.status_code = 130;
}

void	signal_handler_child_heredoc(void)
{
	signal(SIGINT, &handler_child_heredoc);
	signal(SIGQUIT, &handler_child);
}

void	handle_heredoc_sigint(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	close(g_data.fd);
	ft_free_tab_int(g_data.fd_pipe, pipe_counter(g_data.tokens));
	free_var(g_data.node_env, g_data.node_export, &g_data, g_data.node_exec);
	exit (130);
}
