/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:40:24 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/06 19:04:22 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fd(t_exec *aux, t_exec *exec, t_config vars)
{
	if (aux->index == 0)
		close(exec->fd[vars.i][1]);
	else if (aux->next == NULL)
		close(exec->fd[vars.i - 1][0]);
	else
	{
		close(exec->fd[vars.i][1]);
		close(exec->fd[vars.i - 1][0]);
	}
}

void	close_pid(t_config vars, t_exec *aux)
{
	vars.i = -1;
	vars.status = 0;
	while (++vars.i <= aux->index)
	{
		waitpid(vars.pid, &vars.status, 0);
		if (WIFEXITED(vars.status))
			g_status_code = WEXITSTATUS(vars.status);
	}
}
void	executor(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;
	t_exec		*aux;

	aux = exec;
	vars.i = -1;
	while (++vars.i <= aux->index)
	{
		vars.pid = fork();
		signal_handler_child();
		if (vars.pid == 0)
		{
			pipex(aux, exec->fd, vars.i);
			if (pipeless(aux, data, env, export) == 1)
				free_pipelees(exec, data, env, export);
			if (op_builtins(aux->cmd[0]) != 0)
			{
				ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
				free_var(env, export, data, exec);
				exit(g_status_code);
			}
		}
		close_fd(aux, exec, vars);
		if (aux->next != NULL)
			aux = aux->next;
	}
	close_pid(vars, aux);
}

//fazer um vetor de pid