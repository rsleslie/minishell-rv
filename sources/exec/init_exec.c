/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/12 14:49:42 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_exec(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	int			i;

	data->node_env = env;
	data->node_export = export;
	data->node_exec = exec;
	data->fd_pipe = NULL;
	get_redirect(exec, data);
	if (exec->next == NULL)
	{
		pipeless(exec, data, env, export);
		unlink("heredoc");
		return ;
	}
	else
	{
		i = -1;
		data->fd_pipe = (int **)ft_calloc(sizeof(int [2]),
				pipe_counter(data->tokens));
		while (++i < pipe_counter(data->tokens))
		{
			data->fd_pipe[i] = (int *)ft_calloc(sizeof(int), 2);
			pipe(data->fd_pipe[i]);
		}
		executor_pipe(exec, data, env, export);
	}
	unlink("heredoc");
	ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
}
