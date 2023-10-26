/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:22:09 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 16:09:49 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norm_executor_redirect(t_exec *exec,
	t_config *data, t_node *env, t_node *export)
{
	if (exec->fd_output != 0)
		output_redirection(data, exec, env, export);
}

void	error_execve(t_exec *exec, t_config *data,
	t_node *env, t_node *export)
{
	close(exec->fd_input);
	close(exec->fd_output);
	ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
	free_var(env, export, data, data->node_exec);
	data->status_code = 126;
}

void	norm_aux_exec_redirect(t_exec *exec,
	t_config *data, t_node *env, t_node *export)
{
	extern char	**environ;

	dup2(exec->fd_input, 0);
	dup2(exec->fd_output, 1);
	if (op_builtins(exec->cmd[0]) != 0)
		exec_builtins(exec, env, export, data);
	if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
	{
		error_execve(exec, data, env, export);
		exit (data->status_code);
	}
	close(exec->fd_input);
	close(exec->fd_output);
	exit(data->status_code);
}

int	norm_excutor(t_exec *exec, t_config *data)
{
	if (exec->cmd && validation_cmd(exec, data) != 0)
		return (1);
	if (exec->fd_input == -1 || exec->fd_output == -1)
	{
		g_data.status_code = 1;
		return (1);
	}
	return (0);
}

int	executor(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char	**environ;

	if (!exec->cmd)
		return (1);
	if (norm_excutor(exec, data) == 1)
		return (1);
	if (exec->fd_input == 0 && exec->fd_output == 0)
	{
		if (op_builtins(exec->cmd[0]) != 0)
			exec_builtins(exec, env, export, data);
		else if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			data->status_code = 126;
			ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
			free_var(data->node_env, data->node_export, data, data->node_exec);
			close_fd(data->fd_pipe, data);
			exit (data->status_code);
		}
	}
	else
	{
		if (executor_redirect(exec, data, env, export) == 0)
			norm_executor_redirect(exec, data, env, export);
	}
	return (0);
}
