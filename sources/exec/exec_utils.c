/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverona- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:21:48 by rverona-          #+#    #+#             */
/*   Updated: 2023/05/20 21:21:49 by rverona-         ###   ########.fr       */
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

void	execute_cmd(t_exec *exec, t_config *data, int i)
{
	t_config		vars;
	extern char		**environ;

	if (ft_strncmp(exec->redirect[i - 1], ">",
			ft_strlen(exec->redirect[i - 1])) == 0)
		vars.fd = open(exec->redirect[i], O_RDWR | O_CREAT
				| O_TRUNC, S_IRUSR | S_IWUSR, 0644);
	if (ft_strncmp(exec->redirect[i - 1], ">>",
			ft_strlen(exec->redirect[i])) == 0)
		vars.fd = open(exec->redirect[i], O_RDWR | O_CREAT
				| O_APPEND, S_IRUSR | S_IWUSR, 0644);
	if (i == (ft_tab_len(exec->redirect) - 1))
	{
		vars.bkp = dup(1);
		dup2(vars.fd, 1);
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
			perror(strerror(errno));
		dup2(vars.bkp, 1);
		close(vars.fd);
		close(vars.bkp);
	}	
}
