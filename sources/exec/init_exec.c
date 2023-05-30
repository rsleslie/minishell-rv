/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/30 20:24:39 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_exec(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;
	int			i;

	if (exec->next == NULL)
	{
		if (op_builtins(exec->cmd[0]) != 0)
			pipeless(exec, data, env, export);
		else
		{
			vars.pid = fork();
			if (vars.pid == 0)
				pipeless(exec, data, env, export);
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
		exec->fd = (int **)malloc(sizeof(int [2]) * pipe_counter(data->tokens));
		while (++i < pipe_counter(data->tokens))
		{
			exec->fd[i] = (int *)malloc(sizeof(int) * 2);
			pipe(exec->fd[i]);
		}
		executor(exec, data, env, export);
	}
	ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
}
