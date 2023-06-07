/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeless.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:14:00 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/07 13:38:29 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipeless_aux_redirect(t_exec *exec, t_config *data,
	t_node *env, t_node *export)
{
	close(data->fd_input);
	close(data->fd_output);
	ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
	free_var(env, export, data, exec);
	g_status_code = 127;
}

int	exec_redirect(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char	**environ;

	if (data->fd_input != 0 && data->fd_output != 0)
	{
		dup2(data->fd_input, 0);
		dup2(data->fd_output, 1);
		if (op_builtins(exec->cmd[0]) != 0)
			exec_builtins(exec, env, export, data);
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			pipeless_aux_redirect(exec, data, env, export);
			exit (g_status_code);
		}
		close(data->fd_input);
		close(data->fd_output);
		exit(g_status_code);
		return (1);
	}
	else if (data->fd_input != 0)
	{
		input_redirection(data, exec, env, export);
		exit(g_status_code);
		return (1);
	}
	return (0);
}

void	free_pipelees(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
	free_var(env, export, data, exec);
	g_status_code = 1;
	exit (g_status_code);
}

void	norm_aux(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char	**environ;

	if (data->fd_output != 0)
		output_redirection(data, exec, env, export);
	else
	{
		if (op_builtins(exec->cmd[0]) != 0)
			exec_builtins(exec, env, export, data);
		else if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
			free_var(env, export, data, exec);
			g_status_code = 127;
			exit (g_status_code);
		}
	}	
}

int	pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	if (get_fd(exec, data) == 1)
		g_status_code = 1;
	// abrindo o fd duas vezes
	if (validation_cmd(exec, data) == 0)
	{
		if (exec_redirect(exec, data, env, export) == 0)
			norm_aux(exec, data, env, export);
		else
		{
			ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
			free_var(env, export, data, exec);
			g_status_code = 127;
			exit (g_status_code);
		}
	}
	else
		return (1);
	return (0);
}
