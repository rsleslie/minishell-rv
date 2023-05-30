/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:42 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/30 20:24:49 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_fd_input(t_exec *exec)
{
	int fd;
	int	i;

	i = -1;
	fd = 0;
	while (exec->redirect[++i])
	{
		if ((i % 2) == 0)
		{
			if (ft_strncmp(exec->redirect[i], "<", ft_strlen(exec->redirect[i])) == 0)
            {
                if (fd != 0)
				    close(fd);
				fd = open(exec->redirect[i + 1], O_RDONLY);
            }
		}
		if (fd == -1)
        {
            close(fd);
			return (-1);
        }
	}
	return (fd);
}

int	get_fd_output(t_exec *exec)
{
	int fd;
	int	i;

	i = -1;
	fd = 0;
	while (exec->redirect[++i])
	{
		if ((i % 2) == 0)
		{
			if (ft_strncmp(exec->redirect[i], ">", ft_strlen(exec->redirect[i])) == 0)
			{
				if (fd != 0)
					close(fd);
				fd = open(exec->redirect[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0644);
			}
			if (ft_strncmp(exec->redirect[i], ">>",	ft_strlen(exec->redirect[i])) == 0)
			{
				if (fd != 0)
					close(fd);
				fd = open(exec->redirect[i + 1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
			}
		}
	}
	return (fd);
}
