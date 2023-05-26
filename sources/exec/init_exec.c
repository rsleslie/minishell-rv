/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/25 21:42:28 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	input_redirection(t_config *data, t_exec *exec, int i)
{
	t_config 	vars;
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
	vars.status = 0;
	waitpid(vars.pid, &vars.status, 0);
	
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

	if (exec->next == NULL)
	{
		pipeless(exec, data, env, export);
		return ;
	}
	else
	{
		i = -1;
		fd = (int**)malloc(sizeof(int[2]) * pipe_counter(data->tokens));
		while (++i < pipe_counter(data->tokens))
		{
			fd[i] = (int *)malloc(sizeof(int) * 2);
			pipe(fd[i]);
		}
		executor(exec, data, fd, env, export);
	}
	ft_free_tab_int(fd, pipe_counter(data->tokens));
}
