/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:19:59 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/25 21:02:12 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
