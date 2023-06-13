/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:40:24 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/13 12:50:42 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fd(int **fd, t_config *data)
{
	int	i;

	i = -1;
	while (++i < pipe_counter(data->tokens))
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

void	close_pid(pid_t *pid, t_config *data)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	waitpid(pid[pipe_counter(data->tokens)], &status, 0);
	if (WIFEXITED(status))
		data->status_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->status_code = WEXITSTATUS(status) + 128;
	while (++i <= (pipe_counter(data->tokens) - 1))
		wait(NULL);
}

void	norm_aux_exec_pipe(t_exec *aux, t_config *data)
{
	if (op_builtins(aux->cmd[0]) != 0)
	{
		ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
		free_var(data->node_env,
			data->node_export, data, data->node_exec);
		exit (data->status_code);
	}
}

void	executor_pipe(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;
	t_exec		*aux;
	pid_t		*pid;

	aux = exec;
	vars.i = -1;
	pid = (pid_t *)ft_calloc(sizeof(pid_t), pipe_counter(data->tokens) + 1);
	signal(SIGINT, SIG_IGN);
	signal_handler_child();
	while (++vars.i <= aux->index)
	{
		pid[vars.i] = fork();
		if (pid[vars.i] == 0)
		{
			pipex(aux, data->fd_pipe, vars.i, data);
			executor(aux, data, env, export);
			norm_aux_exec_pipe(aux, data);
		}
		if (aux->next != NULL)
			aux = aux->next;
	}
	close_fd(data->fd_pipe, data);
	close_pid(pid, data);
	free(pid);
}
