/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:37:07 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/31 12:56:15 by rleslie-         ###   ########.fr       */
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

void	pipex(t_exec *exec, int **fd, int i)
{
	if (exec->index == 0)
	{
		dup2(fd[i][1], 1);
		close(fd[i][0]);
	}
	else if (exec->next == NULL)
	{
		dup2(fd[i - 1][0], 0);
	}
	else
	{
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
		close(fd[i][0]);
	}
}
