/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:37:28 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/07 20:05:41 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	norm_exec_path(t_exec *exec)
{
	char	*path_check;

	if (exec->cmd[0][0] == '.' || exec->cmd[0][0] == '/')
	{
		path_check = ft_strdup(exec->cmd[0]);
		free(exec->cmd[0]);
		exec->cmd[0] = ft_strdup(path_check);
		free(path_check);
		return (0);
	}
	return (1);
}

int	norm_exec_path_two(char *path_check, t_exec *exec)
{
	if (access(path_check, X_OK) != -1)
	{
		g_status_code = 1;
		free(exec->cmd[0]);
		exec->cmd[0] = ft_strdup(path_check);
		free(path_check);
		return (0);
	}
	return (1);
}

char	*exec_path(t_config *data, t_exec *exec)
{
	char	*path_check;
	int		i;

	i = -1;
	if (norm_exec_path(exec) == 0)
		return (exec->cmd[0]);
	while (data->paths[++i])
	{
		if (access(exec->cmd[0], X_OK) != -1)
		{
			g_status_code = 1;
			return (0);
		}
		path_check = ft_strdup(data->paths[i]);
		path_check = ft_strjoin(path_check, "/");
		path_check = ft_strjoin(path_check, exec->cmd[0]);
		if (norm_exec_path_two(path_check, exec) == 0)
			return (exec->cmd[0]);
		free(path_check);
	}
	return (0);
}

int	input_redirection(t_config *data, t_exec *exec, t_node *env, t_node *export)
{
	extern char	**environ;

	dup2(data->fd_input, 0);
	if (op_builtins(exec->cmd[0]) != 0)
		exec_builtins(exec, env, export, data);
	else
	{
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
			free_var(env, export, data, exec);
			g_status_code = 126;
			exit (g_status_code);
		}
			// return (1);
	}
	close(data->fd_input);
	return (0);
}

//curl pkmn.li 
// curl wttr.in