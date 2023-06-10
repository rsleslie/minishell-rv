/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:19:59 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/10 17:29:42 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	handler_child(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		g_status_code = 130;
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 		rl_replace_line("", 0);
// 	}
// 	if (signal == SIGQUIT)
// 	{
// 		g_status_code = 131;
// 		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
// 		rl_replace_line("", 0);
// 	}
// }

// void	signal_handler_child(void)
// {
// 	signal(SIGINT, handler_child);
// 	signal(SIGQUIT, handler_child);
// }

// void	handle_heredoc_sigint(int signal)
// {
// 	(void)signal;
	
// 	// ft_putchar_fd('\n', 1);
// 	exit(130);	
// }

void	handler_child(int signal)
{
	if (signal == SIGINT)
	{
		g_status_code = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
	}
	if (signal == SIGQUIT)
	{
		g_status_code = 131;
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		rl_replace_line("", 0);
	}
}

void	handler_child_heredoc(int signal)
{
	if (signal == SIGINT)
		g_status_code = 130;
}

void	signal_handler_child(void)
{
	signal(SIGINT, &handler_child);
	signal(SIGQUIT, &handler_child);
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
	// ft_putchar_fd('\n', 1);
	exit(130);	
}

void	handle_sigint(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	struct sigaction	sigact;
	sigset_t			set;

	sigact = (struct sigaction){0};
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = handle_sigint;
	sigaction(SIGINT, &sigact, NULL);
	sigemptyset(&sigact.sa_mask);
	sigemptyset(&set);
	sigaddset(&set, SIGQUIT);
	sigprocmask(SIG_BLOCK, &set, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
}
