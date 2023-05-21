/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverona- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:21:36 by rverona-          #+#    #+#             */
/*   Updated: 2023/05/20 21:21:37 by rverona-         ###   ########.fr       */
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

void	execute_pipe(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char	**environ;
	int			i;

	if (op_builtins(exec->cmd[0]) != 0)
		execute_builtins(exec, env, export);
	else
	{
		if (exec->redirect[0][0] != '-')
		{
			i = -1;
			while (exec->redirect[++i])
			{
				if ((i % 2) != 0)
					execute_cmd(exec, data, i);
			}
		}
		else
		{
			if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
				perror(strerror(errno));
		}
	}
}
