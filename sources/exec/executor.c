/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:40:24 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/25 21:42:33 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		execute_cmd(t_exec *exec, t_config *data, int i)
{
	t_config vars;
	extern char **environ;
	
	if (ft_strncmp(exec->redirect[i - 1], ">", ft_strlen(exec->redirect[i - 1])) == 0)
		vars.fd = open(exec->redirect[i], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0644);
	if (ft_strncmp(exec->redirect[i - 1], ">>", ft_strlen(exec->redirect[i])) == 0)
		vars.fd = open(exec->redirect[i], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
	if (ft_strncmp(exec->redirect[i - 1], "<", ft_strlen(exec->redirect[i])) == 0)
	{
		input_redirection(data, exec, i);
		return (0);
	}
	if (i == (ft_tab_len(exec->redirect) - 1))
	{
			vars.bkp = dup(1);
			dup2(vars.fd, 1);
			if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
				return (1);
			dup2(vars.bkp, 1);
			close(vars.fd);
			close(vars.bkp);
	}
	return (0);	
}

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

void	execute_builtins(t_exec *exec, t_node *env, t_node *export)
{
	int			fd;
	int			bkp;
	int			i;

	if (exec->redirect[0][0] != '-')
	{	
		i = -1;
		while (exec->redirect[++i])
		{
			if ((i % 2) != 0)
			{
				if (ft_strncmp(exec->redirect[i - 1], ">", ft_strlen(exec->redirect[i - 1])) == 0)
					fd = open(exec->redirect[i], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0644);
				if (ft_strncmp(exec->redirect[i - 1], ">>", ft_strlen(exec->redirect[i])) == 0)
					fd = open(exec->redirect[i], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
				if (i == (ft_tab_len(exec->redirect) - 1))
				{
					bkp = dup(1);
					dup2(fd, 1);
					exec_builtins(exec, env, export);
					dup2(bkp, 1);
					close(fd);
					close(bkp);
				}
			}
		}
	}
	else
		exec_builtins(exec, env, export);
}

void	execute_builtins_pipe(t_exec *exec, t_node *env, t_node *export, t_config *data)
{
	int			fd;
	int			i;

	if (exec->redirect[0][0] != '-')
	{	
		i = -1;
		while (exec->redirect[++i])
		{
			if ((i % 2) != 0)
			{
				if (ft_strncmp(exec->redirect[i - 1], ">", ft_strlen(exec->redirect[i - 1])) == 0)
					fd = open(exec->redirect[i], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0644);
				if (ft_strncmp(exec->redirect[i - 1], ">>", ft_strlen(exec->redirect[i])) == 0)
					fd = open(exec->redirect[i], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
				if (i == (ft_tab_len(exec->redirect) - 1))
				{
					dup2(fd, 1);
					exec_builtins(exec, env, export);
					close(fd);
					free_var(env, export, data, exec);
					exit(0);
				}
				close(fd);
			}
		}
	}
	else
	{
		exec_builtins(exec, env, export);
		free_var(env, export, data, exec);
		exit(0);
	}
}

void	executor(t_exec *exec, t_config *data, int **fd, t_node *env, t_node *export)
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
			execute_pipe(aux, data, env, export);
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
