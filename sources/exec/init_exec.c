/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:19:34 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/29 17:30:19 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	input_redirection_pipe(t_config *data, t_exec *exec, int i)
{
	t_config	vars;
	extern char	**environ;

	if (access(exec->redirect[i], R_OK) == 0)
	{
		vars.fd = open(exec->redirect[i], O_RDONLY);
		if (vars.fd == -1)
			//fazer error
		dup2(vars.fd, 0);
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			g_status_code = 127;
			//free_var(env, export, data, exec);
			ft_putstr_fd("error", 2);// matar o processo
			exit(g_status_code);
		}
		close(vars.fd);
		g_status_code = 0;
	}
	else if (access(exec->redirect[i], R_OK) != 0)
	{
		ft_putstr_fd("Permission denied\n", 2);
		g_status_code = 1;
	}
}

int	input_redirection(t_config *data, t_exec *exec, int i)
{
	t_config	vars;
	extern char	**environ;

	if (access(exec->redirect[i], R_OK) == 0)
	{
		vars.pid = fork();
		if (vars.pid == 0)
		{
			vars.fd = open(exec->redirect[i], O_RDONLY);
			if (vars.fd == -1)
			{
				close(vars.fd);
				g_status_code = 127;
				return (1);
			}
			dup2(vars.fd, 0);
			if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
			{
				close(vars.fd);
				g_status_code = 127;
				return (1);
			}
			close(vars.fd);
		}
		vars.status = 0;
		waitpid(vars.pid, &vars.status, 0);
		if (WIFEXITED(vars.status))
			g_status_code = WEXITSTATUS(vars.status);
	}
	else if (access(exec->redirect[i], R_OK) != 0)
	{
		ft_putstr_fd("Permission denied\n", 2);
		g_status_code = 1;
	}
	return (0);
}

void input_redi_aux(t_exec *exec, t_node *env, t_node *export, int i)
{
	t_config	vars;
	extern char	**environ;

	if (access(exec->redirect[i], R_OK) == 0)
	{
		vars.fd = open(exec->redirect[i], O_RDONLY);
		if (vars.fd == -1)
		{
			close(vars.fd);
			g_status_code = 1;
			return ;
		}
		dup2(vars.fd, 0);
		exec_builtins(exec, env, export);
		close(vars.fd);
		exit(0);
	}
	else if (access(exec->redirect[i], R_OK) != 0)
	{
		ft_putstr_fd("Permission denied\n", 2);
		g_status_code = 1;
	}
}

void	pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
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
				{
					if (execute_cmd_pipeless(exec, data, i) == 1)
					{
						ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
						free_var(env, export, data, exec);
						ft_putstr_fd("error", 2);
						exit(g_status_code);
					}
				}
			}
		}
		else
			norm_pipeless(exec, data, env, export);
	}
}

void	init_exec(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	int			i;

	if (exec->next == NULL)
	{
		pipeless(exec, data, env, export);
		return ;
	}
	else
	{
		i = -1;
		exec->fd = (int **)malloc(sizeof(int [2]) * pipe_counter(data->tokens));
		while (++i < pipe_counter(data->tokens))
		{
			exec->fd[i] = (int *)malloc(sizeof(int) * 2);
			pipe(exec->fd[i]);
		}
		executor(exec, data, env, export);
	}
	ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
}
