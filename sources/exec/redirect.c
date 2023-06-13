/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:27:08 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/13 19:04:57 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	norm_get_fd_input(int fd, int i, t_exec *exec, t_config *data)
{
	if (ft_strncmp(exec->redirect[i], "<",
			ft_strlen(exec->redirect[i])) == 0)
	{
		if (fd != 0)
			close(fd);
		if (validation_fd_inp(exec->redirect[i + 1]) == 1)
			return (-1);
		else
			fd = open(exec->redirect[i + 1], O_RDWR);
	}
	if (ft_strncmp(exec->redirect[i], "<<", 2) == 0)
	{
		if (fd != 0)
			close(fd);
		if (heredoc(exec->redirect[i + 1], data) > 129)
			return (-1);
		fd = open("heredoc", O_RDONLY);
	}
	return (fd);
}

int	get_fd_input(t_exec *exec, t_config *data)
{
	int	fd;
	int	i;

	i = -1;
	fd = 0;
	while (exec->redirect[++i])
	{
		if ((i % 2) == 0)
		{
			fd = norm_get_fd_input(fd, i, exec, data);
			if (fd == -1)
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
		if (validation_fd_out(exec->redirect[i + 1]) == 1)
			return (-1);
		else
			fd = open(exec->redirect[i + 1],
					O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0644);
	}
	if (ft_strncmp(exec->redirect[i], ">>", 2) == 0)
	{
		if (fd != 0)
			close(fd);
		if (validation_fd_out(exec->redirect[i + 1]) == 1)
			return (-1);
		else
			fd = open(exec->redirect[i + 1],
					O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
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
				return (fd);
		}
	}
	return (fd);
}

void	get_redirect(t_exec *exec, t_config *data)
{
	t_exec	*aux;

	aux = exec;
	while (aux != NULL)
	{	
		aux->fd_input = 0;
		aux->fd_output = 0;
		if (aux->redirect[0][0] != '-')
		{
			aux->fd_input = get_fd_input(aux, data);
			aux->fd_output = get_fd_output(aux);
		}
		aux = aux->next;
	}
}
