/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:42 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/26 18:07:35 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norm_pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;
	extern char	**environ;

	vars.pid = fork();
	if (vars.pid == 0)
	{
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
			free_var(env, export, data, exec);
			ft_printf("error");
			exit(0);
		}
	}
	vars.status = 0;
	waitpid(vars.pid, &vars.status, 0);
	// ft_printf("status: %i", vars.status);
}

void	norminette_exec_builtins(int fd, t_exec *exec, t_node *env, t_node *export)
{
	int			bkp;

	bkp = dup(1);
	dup2(fd, 1);
	exec_builtins(exec, env, export);
	dup2(bkp, 1);
	close(fd);
	close(bkp);
}

void	norm_execute_builtins_pipe(t_exec *exec, t_node *env, t_node *export, t_config *data)
{
	if (ft_strncmp(exec->redirect[data->i - 1],
			">", ft_strlen(exec->redirect[data->i - 1])) == 0)
		data->fd = open(exec->redirect[data->i], O_RDWR
				| O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0644);
	if (ft_strncmp(exec->redirect[data->i - 1],
			">>", ft_strlen(exec->redirect[data->i])) == 0)
		data->fd = open(exec->redirect[data->i], O_RDWR | O_CREAT
				| O_APPEND, S_IRUSR | S_IWUSR, 0644);
	if (data->i == (ft_tab_len(exec->redirect) - 1))
	{
		dup2(data->fd, 1);
		exec_builtins(exec, env, export);
		close(data->fd);
		ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
		free_var(env, export, data, exec);
		exit(0);
	}
	close(data->fd);
}
