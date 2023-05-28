/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:40:24 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/28 18:39:57 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		execute_cmd_pipeless(t_exec *exec, t_config *data, int i)
{
	t_config vars;
	extern char **environ;
	
	if (ft_strncmp(exec->redirect[i - 1], ">", ft_strlen(exec->redirect[i - 1])) == 0)
		vars.fd = open(exec->redirect[i], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0644);
	if (ft_strncmp(exec->redirect[i - 1], ">>", ft_strlen(exec->redirect[i - 1])) == 0)
		vars.fd = open(exec->redirect[i], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
	if (ft_strncmp(exec->redirect[i - 1], "<", ft_strlen(exec->redirect[i])) == 0)
	{
		input_redirection(data, exec, i);
		return (0);
	}
	if (i == (ft_tab_len(exec->redirect) - 1))
	{
			vars.pid = fork();
			if (vars.pid == 0)
			{
				vars.bkp = dup(1);
				dup2(vars.fd, 1);
				if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
				{
					g_status_code = 127;
					//ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
					//free_var(env, export, data, exec);
					ft_printf("error");
					exit(g_status_code);
				}
				dup2(vars.bkp, 1);
				close(vars.fd);
				close(vars.bkp);
		}
		vars.status = 0;
		waitpid(vars.pid, &vars.status, 0);
		if (WIFEXITED(vars.status))
        	g_status_code = WEXITSTATUS(vars.status);
	}
	return (0);	
}

int		execute_cmd(t_exec *exec, t_config *data, int i)
{
	t_config vars;
	extern char **environ;
	
	if (ft_strncmp(exec->redirect[i - 1], ">", ft_strlen(exec->redirect[i - 1])) == 0)
		vars.fd = open(exec->redirect[i], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0644);
	if (ft_strncmp(exec->redirect[i - 1], ">>", ft_strlen(exec->redirect[i - 1])) == 0)
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
			{
				// tem que dar free
				g_status_code = 127;
				dup2(vars.bkp, 1);
				close(vars.fd);
				close(vars.bkp);
				exit(g_status_code);
			}
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

	i = -1;
	while (data->paths[++i])
	{
		if (access(exec->cmd[0], X_OK) != -1)
		{
			g_status_code = 1;
			return (0);
		}
		path_check = ft_strdup(data->paths[i]);
		path_check = ft_strjoin(path_check, "/");
		path_check = ft_strjoin(path_check, exec->cmd[0]);
		if (access(path_check, X_OK) != -1)
		{
			g_status_code = 1;
			free(exec->cmd[0]);
			exec->cmd[0] = ft_strdup(path_check);
			free(path_check);
			
			return (exec->cmd[0]);
		}
		free(path_check);
	}
	return (0);
}

void	execute_builtins(t_exec *exec, t_node *env, t_node *export)
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
				if (ft_strncmp(exec->redirect[i - 1], ">>", ft_strlen(exec->redirect[i - 1])) == 0)
					fd = open(exec->redirect[i], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
				if (i == (ft_tab_len(exec->redirect) - 1))
					norminette_exec_builtins(fd, exec, env, export);
			}
		}
	}
	else
		exec_builtins(exec, env, export);
}

void	execute_builtins_pipe(t_exec *exec, t_node *env, t_node *export, t_config *data)
{
	if (exec->redirect[0][0] != '-')
	{	
		data->i = -1;
		while (exec->redirect[++data->i])
		{
			if ((data->i % 2) != 0)
				norm_execute_builtins_pipe(exec, env, export, data);
		}
	}
	else
	{
		exec_builtins(exec, env, export);
		ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
		free_var(env, export, data, exec);
		exit(g_status_code);
	}
}

void	executor(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;
	t_exec	*aux;

	aux = exec;
	vars.i = -1;
	while (++vars.i <= aux->index)
	{
		vars.pid = fork();
		if (vars.pid == 0)
		{
			pipex(aux, exec->fd, vars.i);
			execute_pipe(aux, data, env, export);
		}
		if (aux->index == 0)
			close(exec->fd[vars.i][1]);
		else if (aux->next == NULL)
			close(exec->fd[vars.i - 1][0]);
		else
		{
			close(exec->fd[vars.i][1]);
			close(exec->fd[vars.i - 1][0]);
		}
		if (aux->next != NULL)
			aux = aux->next;
	}
	vars.i = -1;
	vars.status = 0;
	while (++vars.i <= aux->index)
	{
		waitpid(vars.pid, &vars.status, 0);
		if (WIFEXITED(vars.status))
        	g_status_code = WEXITSTATUS(vars.status);
	}
}
