/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:08:56 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/12 21:10:52 by rleslie-         ###   ########.fr       */
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
