/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/10 16:55:51 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_exec(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	int			i;

	exec->fd = NULL;
	get_redirect(exec);
	if (exec->next == NULL)
	{
		pipeless(exec, data, env, export);
		unlink("heredoc");
		// if (exec->fd_input != 0)
		// 	close(exec->fd_input);
		// init_signals();
		return ;
	}
	else
	{
		i = -1;
		exec->fd = (int **)ft_calloc(sizeof(int [2]),
				pipe_counter(data->tokens));
		while (++i < pipe_counter(data->tokens))
		{
			exec->fd[i] = (int *)ft_calloc(sizeof(int), 2);
			pipe(exec->fd[i]);
		}
		executor_pipe(exec, data, env, export);
	}
	unlink("heredoc");
	ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
	init_signals();
}
