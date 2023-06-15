/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 18:04:23 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ref_list(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	data->node_env = env;
	data->node_export = export;
	data->node_exec = exec;
	data->fd_pipe = NULL;
	get_redirect(exec, data);
}

void	close_redirect(t_exec *exec)
{
	t_exec	*aux;

	aux = exec;
	while (aux != NULL)
	{
		if (aux->fd_input != 0 && aux->fd_input != -1)
			close(aux->fd_input);
		if (aux->fd_output != 0 && aux->fd_output != -1)
			close(aux->fd_output);
		aux = aux->next;
	}
}

void	init_exec(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	int	i;

	ref_list(exec, data, env, export);
	if (exec->next == NULL && exec->cmd)
	{
		pipeless(exec, data, env, export);
		close_redirect(exec);
		unlink("heredoc");
		return ;
	}
	else if (exec->next != NULL && exec->cmd)
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
	close_redirect(exec);
	unlink("heredoc");
	ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
}
