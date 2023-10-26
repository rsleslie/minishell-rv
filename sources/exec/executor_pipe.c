/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:40:24 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 20:00:11 by rleslie-         ###   ########.fr       */
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
	free(pid);
}

void	free_cmd_invalid(t_config *data, pid_t *pid)
{
	free(pid);
	close_fd(data->fd_pipe, data);
	close_redirect(data->node_exec);
	ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
	free_var(data->node_env,
		data->node_export, data, data->node_exec);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	exit (data->status_code);
}

void	broken_pipe(int signal)
{
	if (signal == SIGPIPE)
	{
		free(g_data.pid_array);
		close_fd(g_data.fd_pipe, &g_data);
		close_redirect(g_data.node_exec);
		ft_free_tab_int(g_data.fd_pipe, pipe_counter(g_data.tokens));
		free_var(g_data.node_env,
			g_data.node_export, &g_data, g_data.node_exec);
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		exit (g_data.status_code);
	}
}

void	executor_pipe(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;
	t_exec		*aux;

	aux = exec;
	vars.i = -1;
	g_data.pid_array = (pid_t *)ft_calloc(sizeof(pid_t),
			pipe_counter(data->tokens) + 1);
	signal(SIGINT, SIG_IGN);
	signal_handler_child();
	while (++vars.i <= aux->index)
	{
		g_data.pid_array[vars.i] = fork();
		if (g_data.pid_array[vars.i] == 0)
		{
			pipex(aux, data->fd_pipe, vars.i, data);
			if (executor(aux, data, env, export) == 1
				|| op_builtins(aux->cmd[0]))
				free_cmd_invalid(data, g_data.pid_array);
			close_redirect(exec);
		}
		if (aux->next != NULL)
			aux = aux->next;
	}
	close_fd(data->fd_pipe, data);
	close_pid(g_data.pid_array, data);
}
