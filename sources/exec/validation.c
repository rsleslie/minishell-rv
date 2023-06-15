/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:00:41 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 19:53:24 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validation_fd_out(char *fd)
{
	if (access(fd, F_OK) == 0)
	{
		if (access(fd, R_OK | W_OK) == -1)
		{
			ft_putstr_fd("minishell: Permission denied\n", 2);
			g_data.status_code = 1;
			return (1);
		}
		g_data.status_code = 0;
		return (0);
	}
	return (0);
}

int	validation_fd_inp(char *fd)
{
	if (access(fd, F_OK) == 0)
	{
		if (access(fd, R_OK | W_OK) == -1)
		{
			ft_putstr_fd("minishell: Permission denied\n", 2);
			g_data.status_code = 1;
			return (1);
		}
		g_data.status_code = 0;
		return (0);
	}
	ft_putstr_fd("minishell: No such file or directory\n", 2);
	g_data.status_code = 1;
	return (1);
}

int	norm_aux_validation(char *path_check)
{
	if (access(path_check, F_OK) == 0)
	{
		if (access(path_check, X_OK) == -1)
		{
			ft_putstr_fd("minishell: Permission denied\n", 2);
			g_data.status_code = 126;
			return (1);
		}
		free(path_check);
		g_data.status_code = 0;
		return (0);
	}
	return (2);
}

int	aux_validation(t_config *data, t_exec *exec)
{
	char	*path_check;
	int		status;
	int		i;

	i = -1;
	while (data->paths && data->paths[++i])
	{
		path_check = ft_strdup(data->paths[i]);
		path_check = ft_strjoin(path_check, "/");
		path_check = ft_strjoin(path_check, exec->cmd[0]);
		status = norm_aux_validation(path_check);
		if (status != 2)
			return (status);
		free(path_check);
	}
	if (op_builtins(exec->cmd[0]) != 0)
		return (0);
	ft_putstr_fd("minishell: command not found\n", 2);
	g_data.status_code = 127;
	return (1);
}

int	validation_cmd(t_exec *exec, t_config *data)
{
	if (!exec->cmd[0])
		return (1);
	if (exec->cmd[0][0] == '\0')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		g_data.status_code = 127;
		return (1);
	}
	if (exec->cmd[0][0] != '.' && exec->cmd[0][0] != '/')
	{
		if (aux_validation(data, exec) == 1)
			return (1);
	}
	else if (exec->cmd[0][0] == '.' || exec->cmd[0][0] == '/')
	{
		if (exec->cmd[0][0] == '.' && ft_strlen(exec->cmd[0]) == 1)
		{
			g_data.status_code = 2;
			ft_putendl_fd("minishell: filename argument required", 2);
			return (1);
		}
		if (cmd_acess(exec->cmd[0]) == 1)
			return (1);
	}
	return (0);
}
