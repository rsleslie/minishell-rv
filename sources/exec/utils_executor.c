/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:42 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/07 13:30:06 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_fd_input(t_exec *exec)
{
	int	fd;
	int	i;

	i = -1;
	fd = 0;
	while (exec->redirect[++i])
	{
		if ((i % 2) == 0)
		{
			if (ft_strncmp(exec->redirect[i], "<",
					ft_strlen(exec->redirect[i])) == 0)
			{
				if (fd != 0)
					close(fd);
				fd = open(exec->redirect[i + 1], O_RDWR);
			}
			if (ft_strncmp(exec->redirect[i], "<<",
					ft_strlen(exec->redirect[i])) == 0)
			{
				if (fd != 0)
					close(fd);
				if (heredoc(exec->redirect[i + 1]) == 130)
					return (-1);
				fd = open("heredoc", O_RDONLY);
			}
		}
		if (fd == -1)
		{
			g_status_code = 1;
			ft_putstr_fd("Permission denied\n", 2);
			return (fd);
		}
	}
	return (fd);
}

int	aux_get_fd_output(t_exec *exec, int fd, int i)
{
	if (ft_strncmp(exec->redirect[i], ">",
			ft_strlen(exec->redirect[i])) == 0)
	{
		if (fd != 0)
			close(fd);
		fd = open(exec->redirect[i + 1],
				O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0644);
	}
	if (ft_strncmp(exec->redirect[i], ">>",
			ft_strlen(exec->redirect[i])) == 0)
	{
		if (fd != 0)
			close(fd);
		fd = open(exec->redirect[i + 1],
				O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
	}
	return (fd);
}

int	get_fd_output(t_exec *exec)
{
	int	fd;
	int	i;

	i = -1;
	fd = 0;
	while (exec->redirect[++i])
	{
		if ((i % 2) == 0)
		{
			fd = aux_get_fd_output(exec, fd, i);
			if (fd == -1)
			{
				ft_putstr_fd("Permission denied\n", 2);
				g_status_code = 1;
				return (fd);
			}
		}
	}
	return (fd);
}

int	get_fd(t_exec *exec, t_config *data)
{
	data->fd_input = 0;
	data->fd_output = 0;
	if (exec->redirect[0][0] != '-')
	{
		data->fd_input = get_fd_input(exec);
		data->fd_output = get_fd_output(exec);
		if (data->fd_input == -1 || data->fd_output == -1)
		{
			if (data->fd_output != 0)
				close(data->fd_output);
			if (data->fd_input != 0)
				close(data->fd_input);
			data->fd_input = 0;
			data->fd_output = 0;
			// ft_putstr_fd("No such file or directory\n", 2);
			return (1);
		}
	}
	return (0);
}

int	output_redirection(t_config *data, t_exec *exec,
		t_node *env, t_node *export)
{
	int			bkp;
	extern char	**environ;

	bkp = dup(1);
	dup2(data->fd_output, 1);
	if (op_builtins(exec->cmd[0]) != 0)
		exec_builtins(exec, env, export, data);
	else
	{
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
			write(STDERR_FILENO, "DEU RUIM\n", 9);
		exit(126);
	}
	dup2(bkp, 1);
	close(data->fd_output);
	close(bkp);
	return (0);
}
