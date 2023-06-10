/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:27:08 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/10 16:09:14 by rleslie-         ###   ########.fr       */
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
				if (validation_fd_inp(exec->redirect[i + 1]) == 1)
					return (-1);
				else
					fd = open(exec->redirect[i + 1], O_RDWR);
			}
			if (ft_strncmp(exec->redirect[i], "<<", 2) == 0)
			{
				if (fd != 0)
					close(fd);
				if (heredoc(exec->redirect[i + 1]) == 130)
				{
					// close(exec->fd_input);
					// ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
					//free_var(env, export, data, exec);
					return (-1);
				}
				//free_var(env, export, data, exec);
				fd = open("heredoc", O_RDONLY);
			}
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

void	get_redirect(t_exec *exec)
{
	t_exec	*aux;

	aux = exec;
	while (aux != NULL)
	{	
		aux->fd_input = 0;
		aux->fd_output = 0;
		if (aux->redirect[0][0] != '-')
		{
			aux->fd_input = get_fd_input(aux);
			if (aux->fd_input == -1)
				close(aux->fd_input);
			else
				aux->fd_output = get_fd_output(aux);
			if (exec->fd_output == -1)
			{
				if (exec->fd_output != 0)
					close(exec->fd_output);
				if (exec->fd_input != 0)
					close(exec->fd_input);
			}
		}
		aux = aux->next;
	}
}

// enter dando errado