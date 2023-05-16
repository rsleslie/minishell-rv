/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/16 17:48:17 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*exec_path(t_config *data, t_exec *exec)
{
	char	*path_check;
	int		i;

	i = 0;
	while (data->paths[i])
	{
		if (access(exec->cmd[0], X_OK) != -1)
			return (0);
		path_check = ft_strdup(data->paths[i]);
		path_check = ft_strjoin(path_check, "/");
		path_check = ft_strjoin(path_check, exec->cmd[0]);
		if (access(path_check, X_OK) != -1)
		{
			free(exec->cmd[0]);
			exec->cmd[0] = ft_strdup(path_check);
			free(path_check);
			
			return (exec->cmd[0]);
		}
		i++;
		free(path_check);
	}
	return (0);
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

void    pipex(t_exec *exec, int **fd, int i)
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

void	executor(t_exec *exec, t_config *data, int **fd)
{
	extern char	**environ;
	int	pid;
	t_exec	*aux;
	int	i;
	int	status;
	
	aux = exec;
	i = 0;
	while (i <= aux->index)
	{
		pid = fork();
		if (pid == 0)
		{
			pipex(aux, fd, i);
			if (execve(exec_path(data, aux), aux->cmd, environ) == -1)
				perror(strerror(errno));
		}
		if (aux->index == 0)
			close(fd[i][1]);
		else if (aux->next == NULL)
			close(fd[i - 1][0]);
		else
		{
			close(fd[i][1]);
			close(fd[i - 1][0]);
		}
		i++;
		if (aux->next != NULL)
			aux = aux->next;
	}
	i = -1;
	status = 0;
	while (++i <= aux->index)
	{
		waitpid(pid, &status, 0);
	}
}

void	pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char **environ;
	t_exec		*aux;
	int			pid;
	int			status;

	aux = exec;
	if (op_builtins(exec->cmd[0]) != 0)
	{
		if (exec->redirect[0][0] != '*')
		{
			
		}
		exec_builtins(exec, env, export);
	}
	else//verificar o se tem redirect;
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(exec_path(data, aux), aux->cmd, environ) == -1)
				perror(strerror(errno));
		}
		status = 0;
			waitpid(pid, &status, 0);
	}
}

void	init_exec(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	int			i;
	int			**fd;

	fd = (int**)malloc(sizeof(int[2]) * pipe_counter(data->tokens));
	if (exec->next == NULL)
		pipeless(exec, data, env, export);
	else
	{
		i = -1;
		while (++i < pipe_counter(data->tokens))
		{
			fd[i] = (int *)malloc(sizeof(int) * 2);
			pipe(fd[i]);
		}
		executor(exec, data, fd);
	}
}