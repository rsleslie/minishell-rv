/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/31 15:00:27 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_exec(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;
	int			i;

	exec->fd = NULL;
	if (exec->next == NULL)
	{
		if (get_fd(exec, data) == 1)
		{
			g_status_code = 1;
			return ;
		}
		if (validation_cmd(exec, data) != 0)
				return ;
		if (op_builtins(exec->cmd[0]) != 0)
			pipeless(exec, data, env, export, exec);
		else
		{
			vars.pid = fork();
			if (vars.pid == 0)
				pipeless(exec, data, env, export, exec);
			vars.status = 0;
			waitpid(vars.pid, &vars.status, 0);
			if (WIFEXITED(vars.status))
				g_status_code = WEXITSTATUS(vars.status);
		}
		return ;
	}
	else
	{
		i = -1;
		exec->fd = (int **)ft_calloc(sizeof(int [2]), pipe_counter(data->tokens));
		while (++i < pipe_counter(data->tokens))
		{
			exec->fd[i] = (int *)ft_calloc(sizeof(int), 2);
			pipe(exec->fd[i]);
		}
		executor(exec, data, env, export);
	}
	ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
}
