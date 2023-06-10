/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:40:24 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/10 14:36:18 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fd(int **fd, t_config *data)
{
	int i;
	
	i = -1;
	while (++i < pipe_counter(data->tokens))
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

void	close_pid(pid_t *pid, t_config *data)
{
	int i = -1;
	int status = 0;
	waitpid(pid[pipe_counter(data->tokens)], &status, 0);
	if (WIFEXITED(status))
		g_status_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status_code = WEXITSTATUS(status) + 128;
	while (++i <= (pipe_counter(data->tokens) - 1))
		wait(NULL);
}

void	executor_pipe(t_exec *exec, t_config *data, t_node *env, t_node *export)
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
			pipex(aux, exec->fd, vars.i, data);
			executor(aux, data, env, export);
			if (op_builtins(aux->cmd[0]) != 0)
			{
				ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
				free_var(env, export, data, exec);
				exit(g_status_code);
			}
		}
		if (aux->next != NULL)
		{
			aux = aux->next;
			aux->fd = exec->fd;
		}
	}
	close_fd(exec->fd, data);
	close_pid(pid, data);
	free(pid);
}

//fazer um vetor de pid
//exi arrumar