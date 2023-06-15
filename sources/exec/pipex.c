/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:37:07 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 16:49:33 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipex(t_exec *exec, int **fd, int i, t_config *data)
{
	if (exec->index == 0)
	{
		dup2(fd[i][1], 1);
		close_fd(fd, data);
	}
	else if (exec->next == NULL)
	{
		dup2(fd[i - 1][0], 0);
		close_fd(fd, data);
	}
	else
	{
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
		close_fd(fd, data);
	}
}
