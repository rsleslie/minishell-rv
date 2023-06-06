/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeless.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:14:00 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/06 12:21:56 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int cmd_acess(char *str)
{
	if (access(str, F_OK) == 0 )
	{
		if (access(str, X_OK) == 0)
			return (0);
		else
		{
			ft_putstr_fd("Permission denied\n", 2);
			g_status_code = 126;
			return (1);
		}
	}
	else
	{
		ft_putstr_fd("No such file or directory\n", 2);
		g_status_code = 127;
		return (1);
	}
}

int	validation_cmd(t_exec *exec, t_config *data)
{
	char	*path_check;
	int		i;

	i = 0;
	if (exec->cmd[0][0] != '.' && exec->cmd[0][0] != '/')
	{
		while(data->paths[i])
		{
			path_check = ft_strdup(data->paths[i]);
			path_check = ft_strjoin(path_check, "/");
			path_check = ft_strjoin(path_check, exec->cmd[0]);
			if (access(path_check, F_OK) == 0)
			{
				if (access(path_check, X_OK) == -1)
				{
					ft_putstr_fd("Permission denied\n", 2);
					g_status_code = 126;
					return (1);
				}
				free(path_check);
				g_status_code = 0;
				return (0);
			}
			i++;
			free(path_check);
		}
	}
	else if (exec->cmd[0][0] == '.' || exec->cmd[0][0] == '/')
	{
		if ((cmd_acess(exec->cmd[0])) == 1)
			return (1);
		else
			return (0);
	}
	if (op_builtins(exec->cmd[0]) != 0)
		return (0);
	ft_putstr_fd("No such file or directory\n", 2);
	g_status_code = 127;
	return (1);
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
			close(data->fd_input);
			close(data->fd_output);
			ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
			free_var(env, export, data, exec);
			g_status_code = 127;
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

void	pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export, t_exec *e)
{
	extern char	**environ;
	
	if (get_fd(exec, data) == 1)
		g_status_code = 1;
	if (validation_cmd(exec, data) == 0)
	{
		if (exec_redirect(exec, data, env, export) == 0)
		{
			if (data->fd_output != 0)
				output_redirection(data, exec, env, export);
			else
			{
				if (op_builtins(exec->cmd[0]) != 0)
					exec_builtins(exec, env, export, data);
				else if(execve(exec_path(data, exec), exec->cmd, environ) == -1)
				{
					ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
					free_var(env, export, data, exec);
					g_status_code = 127;
					exit (g_status_code);
				}
			}
		}
		else
		{
			ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
			free_var(env, export, data, exec);
			g_status_code = 127;
			exit (g_status_code);
		}
	}
	else
	{
		ft_free_tab_int(e->fd, pipe_counter(data->tokens));
		free_var(env, export, data, e);
		g_status_code = 1;
		exit (g_status_code);
	}
}
