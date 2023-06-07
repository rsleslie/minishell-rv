/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:40:24 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/07 16:24:05 by rleslie-         ###   ########.fr       */
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

void	close_pid(pid_t *pid, t_config *data)
{
	int i = -1;
	int status = 0;
	waitpid(pid[pipe_counter(data->tokens) - 1], &status, 0);
	if (WIFEXITED(status))
		g_status_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status_code = WEXITSTATUS(status) + 128;
	while (++i < (pipe_counter(data->tokens)))
		wait(NULL);
}

void	executor(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;
	t_exec		*aux;
	pid_t		*pid;
	
	aux = exec;
	vars.i = -1;
	pid = (pid_t *)ft_calloc(sizeof(pid_t), pipe_counter(data->tokens) + 1);
	while (++vars.i <= aux->index)
	{
		pid[vars.i] = fork();
		if (pid[vars.i] == 0)
		{
			signal_handler_child();
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
	close_pid(pid, data);
	free(pid);
}

//fazer um vetor de pid
//exi arrumar