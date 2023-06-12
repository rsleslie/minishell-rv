/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:22:09 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/12 15:08:09 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norm_executor_redirect(t_exec *exec, t_config *data, t_node *env, t_node *export)
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

int	executor_redirect(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char	**environ;

	if (exec->fd_input != 0 && exec->fd_output != 0)
	{
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
		return (1);
	}
	else if (exec->fd_input != 0)
	{
		if (op_builtins(exec->cmd[0]) != 0)
		{
			close(exec->fd_input);
			exec_builtins(exec, env, export, data);
			return (1);
		}
		input_redirection(data, exec, env, export);
		// exit(data->status_code); olhar a execução do executor_pipe
		return (1);
	}
	return (0);
}

void	executor(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char	**environ;
	
	if (validation_cmd(exec, data) != 0)
		return ;
	if (exec->fd_input == -1 || exec->fd_output == -1)
		return ;
	if (exec->fd_input == 0 && exec->fd_output == 0)
	{
		if (op_builtins(exec->cmd[0]) != 0)
		{
			exec_builtins(exec, env, export, data);
			// data->status_code = 0;
		}
		else if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
			free_var(data->node_env, data->node_export, data, data->node_exec);
			data->status_code = 126;
			exit (data->status_code);
		}
	}
	else
	{
		if (executor_redirect(exec, data, env, export) == 0)
			norm_executor_redirect(exec, data, env, export);
	}
}

/// tem que dar free na builtins
