/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:42 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 12:38:44 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	executor_redirect(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char	**environ;

	if (exec->fd_input != 0 && exec->fd_output != 0)
	{
		norm_aux_exec_redirect(exec, data, env, export);
		return (1);
	}
	else if (exec->fd_input != 0 && exec->fd_output == 0)
	{
		if (op_builtins(exec->cmd[0]) != 0)
		{
			close(exec->fd_input);
			exec_builtins(exec, env, export, data);
			return (1);
		}
		input_redirection(data, exec, env, export);
		return (1);
	}
	return (0);
}

int	cmd_acess(char *str)
{
	if (access(str, F_OK) == 0)
	{
		if (access(str, X_OK) == 0 && chdir(str) != 0)
			return (0);
		else
		{
			ft_putstr_fd("minishell: permission denied\n", 2);
			g_data.status_code = 126;
			return (1);
		}
	}
	else
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		g_data.status_code = 127;
		return (1);
	}
}

int	pipe_counter(char **tokens)
{
	int	counter;
	int	i;

	counter = 0;
	i = -1;
	while (tokens[++i])
	{
		if (ft_strncmp(&tokens[i][0], "|", 2) == 0)
			counter++;
	}
	return (counter);
}

int	input_redirection(t_config *data, t_exec *exec, t_node *env, t_node *export)
{
	extern char	**environ;

	dup2(exec->fd_input, 0);
	if (op_builtins(exec->cmd[0]) != 0)
		exec_builtins(exec, env, export, data);
	else
	{
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
			free_var(data->node_env, data->node_export, data, data->node_exec);
			data->status_code = 126;
			close(exec->fd_input);
			close_fd(data->fd_pipe, data);
			exit (data->status_code);
		}
	}
	close(exec->fd_input);
	return (0);
}

int	output_redirection(t_config *data, t_exec *exec,
		t_node *env, t_node *export)
{
	int			bkp;
	extern char	**environ;

	bkp = dup(1);
	dup2(exec->fd_output, 1);
	if (op_builtins(exec->cmd[0]) != 0)
		exec_builtins(exec, env, export, data);
	else
	{
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
			free_var(data->node_env, data->node_export, data, data->node_exec);
			data->status_code = 126;
			close_fd(data->fd_pipe, data);
			close_redirect(data->node_exec);
			exit (data->status_code);
		}
	}
	dup2(bkp, 1);
	close_redirect(data->node_exec);
	close(bkp);
	return (0);
}
