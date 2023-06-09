/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:00:41 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/12 15:17:20 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validation_fd_out(char *fd)
{
	if (access(fd, F_OK) == 0)
	{
		if (access(fd, R_OK | W_OK) == -1)
		{
			ft_putstr_fd("Permission denied\n", 2);
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
			ft_putstr_fd("Permission denied\n", 2);
			g_data.status_code = 1;
			return (1);
		}
		g_data.status_code = 0;
		return (0);
	}
	ft_putstr_fd("No such file or directory\n", 2);
	g_data.status_code = 1;
	return (1);
}

int	cmd_acess(char *str)
{
	if (access(str, F_OK) == 0)
	{
		if (access(str, X_OK) == 0)
			return (0);
		else
		{
			ft_putstr_fd("Permission denied\n", 2);
			g_data.status_code = 126;
			return (1);
		}
	}
	else
	{
		ft_putstr_fd("command not found\n", 2);
		g_data.status_code = 127;
		return (1);
	}
}

int	aux_validation(t_config *data, t_exec *exec)
{
	char	*path_check;
	int		i;

	i = -1;
	while (data->paths[++i])
	{
		path_check = ft_strdup(data->paths[i]);
		path_check = ft_strjoin(path_check, "/");
		path_check = ft_strjoin(path_check, exec->cmd[0]);
		if (access(path_check, F_OK) == 0)
		{
			if (access(path_check, X_OK) == -1)
			{
				ft_putstr_fd("Permission denied\n", 2);
				g_data.status_code = 126;
				return (1);
			}
			free(path_check);
			g_data.status_code = 0;
			return (0);
		}
		free(path_check);
	}
	ft_putstr_fd("command not found\n", 2);
	g_data.status_code = 127;
	return (1);
}

int	validation_cmd(t_exec *exec, t_config *data)
{
	if (op_builtins(exec->cmd[0]) != 0)
		return (0);
	if (exec->cmd[0][0] != '.' && exec->cmd[0][0] != '/')
	{
		if (aux_validation(data, exec) == 1)
			return (1);
		else
			return (0);
	}
	else if (exec->cmd[0][0] == '.' || exec->cmd[0][0] == '/')
	{
		if ((cmd_acess(exec->cmd[0])) == 1)
			return (1);
		else
			return (0);
	}
	return(0);
}
