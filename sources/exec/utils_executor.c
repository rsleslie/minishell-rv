/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:42 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/08 17:59:34 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
			free_var(env, export, data, exec);
			g_status_code = 126;
			exit (g_status_code);
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
			ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
			free_var(env, export, data, exec);
			g_status_code = 126;
			exit (g_status_code);
		}
	}
	dup2(bkp, 1);
	close(exec->fd_output);
	close(bkp);
	return (0);
}
