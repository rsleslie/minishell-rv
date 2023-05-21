/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/20 18:15:06 by rverona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executor(t_exec *exec, t_config *data, int **fd,
	t_node *env, t_node *export)
{
	extern char	**environ;
	int			pid;
	t_exec		*aux;
	int			i;
	int			status;

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
				if (ft_strncmp(exec->redirect[i - 1], ">",
						ft_strlen(exec->redirect[i - 1])) == 0)
					fd = open(exec->redirect[i], O_RDWR | O_CREAT
							| O_TRUNC, S_IRUSR | S_IWUSR, 0644);
				if (ft_strncmp(exec->redirect[i - 1], ">>",
						ft_strlen(exec->redirect[i])) == 0)
					fd = open(exec->redirect[i], O_RDWR | O_CREAT
							| O_APPEND, S_IRUSR | S_IWUSR, 0644);
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

void	pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;
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
	int			**fd;

	fd = (int **)malloc(sizeof(int [2]) * pipe_counter(data->tokens));
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
}
