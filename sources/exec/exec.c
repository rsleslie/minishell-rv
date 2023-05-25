/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/23 16:43:22 by rleslie-         ###   ########.fr       */
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

void	input_redirection(t_config *data, t_exec *exec, int i)
{
	t_config vars;
	extern char **environ;
	
	if (access(exec->redirect[i], R_OK) == 0)
	{
		vars.pid = fork();
		if (vars.pid == 0)
		{
			vars.fd = open(exec->redirect[i], O_RDONLY);
			dup2(vars.fd, 0);
			if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
				perror(strerror(errno));//tirar errno
			close(vars.fd);
			exit(1);
		}
	}
	else if (access(exec->redirect[i], R_OK) != 0)
		printf("minishell: %s: Permission denied\n", exec->redirect[i]);
	// close(vars.fd);
	vars.status = 0;
	waitpid(vars.pid, &vars.status, 0);
	
}

void	execute_cmd(t_exec *exec, t_config *data, int i)
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
		return ;
	}
	if (i == (ft_tab_len(exec->redirect) - 1))
	{
		vars.pid = fork();
		if (vars.pid == 0)
		{
			vars.bkp = dup(1);
			dup2(vars.fd, 1);
			if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
				perror(strerror(errno));
			dup2(vars.bkp, 1);
			close(vars.fd);
			close(vars.bkp);
		}
		close(vars.fd);
		vars.status = 0;
			waitpid(vars.pid, &vars.status, 0);
		
	}	
}

void	execute_pipe(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char **environ;
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

void	pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;
	extern char **environ;
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
			vars.pid = fork();
			if (vars.pid == 0)
			{
				if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
					perror(strerror(errno));
			}
			vars.status = 0;
				waitpid(vars.pid, &vars.status, 0);
		}
	}
}

void	init_exec(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	int			i;
	int			**fd = {0};

	if (pipe_counter(data->tokens) >= 1)
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
		executor(exec, data, fd, env, export);
	}
	if (pipe_counter(data->tokens) >= 1)
		ft_free_tab_int(fd, pipe_counter(data->tokens));
}
