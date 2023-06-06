/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/06 15:49:41 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	aux_only_command(t_exec *exec, t_config *data)
{
	if (get_fd(exec, data) == 1)
	{
		g_status_code = 1;
		return (1);
	}
	if (validation_cmd(exec, data) != 0)
		return (1);
	return (0);
}

void	only_command(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;

	if (aux_only_command(exec, data) == 1)
		return ;
	if (op_builtins(exec->cmd[0]) != 0)
	{
		if (pipeless(exec, data, env, export) == 1)
			free_pipelees(exec, data, env, export);
	}
	else
	{
		vars.pid = fork();
		if (vars.pid == 0)
		{
			if (pipeless(exec, data, env, export) == 1)
				free_pipelees(exec, data, env, export);
		}
		vars.status = 0;
		waitpid(vars.pid, &vars.status, 0);
		if (WIFEXITED(vars.status))
			g_status_code = WEXITSTATUS(vars.status);
	}
}

void	init_exec(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	int			i;

	exec->fd = NULL;
	if (exec->next == NULL)
	{
		only_command(exec, data, env, export);
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
		executor(exec, data, env, export);
	}
	ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
}
