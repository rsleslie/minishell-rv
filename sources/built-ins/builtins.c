/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:57 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/06 12:20:59 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_builtins(t_exec *exec, t_node *env, t_node *export, t_config *data)
{
	if (ft_strncmp(exec->cmd[0], "pwd", ft_strlen(exec->cmd[0])) == 0)
		ft_pwd();
	else if (ft_strncmp(exec->cmd[0], "cd", ft_strlen(exec->cmd[0])) == 0
		&& ft_tab_len(exec->cmd) > 2)
	{
		g_status_code = 1;
		return ;
	}
	else if (ft_strncmp(exec->cmd[0], "cd", ft_strlen(exec->cmd[0])) == 0)
		ft_cd(exec->cmd, env);
	else if (ft_strncmp(exec->cmd[0], "exit", ft_strlen(exec->cmd[0])) == 0)
		ft_exit(data, env, export, exec);
	else if (ft_strncmp(exec->cmd[0], "echo", ft_strlen(exec->cmd[0])) == 0)
		ft_echo(exec->cmd);
	else if (ft_strncmp(exec->cmd[0], "env", ft_strlen(exec->cmd[0])) == 0
		&& !exec->cmd[1])
		print_env(env);
	else if (ft_strncmp(exec->cmd[0], "export", ft_strlen(exec->cmd[0])) == 0
		&& !exec->cmd[1])
		print_export(export);
	else if (ft_strncmp(exec->cmd[0], "export", ft_strlen(exec->cmd[0])) == 0)
		arguments_export(exec->cmd, env, export);
	else if ((ft_strncmp(exec->cmd[0], "unset", ft_strlen(exec->cmd[0])) == 0)
		&& exec->cmd[1])
		arguments_unset(exec->cmd, env, export);
}
