/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:37:07 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/25 21:44:08 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_pipe(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char **environ;
	int			i;
	
	if (op_builtins(exec->cmd[0]) != 0)
		execute_builtins_pipe(exec, env, export, data);
	else
	{
		if (exec->redirect[0][0] != '-')
		{
			i = -1;
			while (exec->redirect[++i])
			{
				if ((i % 2) != 0)
				{
					if (execute_cmd(exec, data, i) == 1)
					{
						free_var(env, export, data, exec);
						printf("error");
						exit(0);
					}
				}
			}
		}
		else
		{
			if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
			{
				free_var(env, export, data, exec);
				printf("error");// matar o processo
				exit(0);
			}
				
		}
	}
}

int	pipe_counter(char **tokens)
{
	int counter;
	int i;

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