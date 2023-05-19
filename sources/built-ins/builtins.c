/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:57 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/19 18:25:17 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_builtins(t_exec *exec, t_node *env, t_node *export)
{
	if (ft_strncmp(exec->cmd[0], "cd", ft_strlen(exec->cmd[0])) == 0
		&& ft_strncmp(exec->cmd[1], "..", ft_strlen(exec->cmd[1])) != 0)
		return ;
	if (ft_strncmp(exec->cmd[0], "cd", ft_strlen(exec->cmd[0])) == 0 && (ft_tab_len(exec->cmd)) > 1)
		printf("too many arguments");
	if (ft_strncmp(exec->cmd[0], "cd", ft_strlen(exec->cmd[0])) == 0)
		ft_cd(exec->cmd, env);
	if (ft_strncmp(exec->cmd[0], "echo", ft_strlen(exec->cmd[0])) == 0)
		ft_echo(exec->cmd);
	if (ft_strncmp(exec->cmd[0], "pwd", ft_strlen(exec->cmd[0])) == 0)
		ft_pwd();
	if (ft_strncmp(exec->cmd[0], "env", ft_strlen(exec->cmd[0])) == 0
		&& !exec->cmd[1])
		print_env(env);
	else if (ft_strncmp(exec->cmd[0], "export", ft_strlen(exec->cmd[0])) == 0
		&& !exec->cmd[1])
		print_export(export);
	else if (ft_strncmp(exec->cmd[0], "export", ft_strlen(exec->cmd[0])) == 0)
		arguments_export(exec->cmd, env, export);
	else if (ft_strncmp(exec->cmd[0], "unset", ft_strlen(exec->cmd[0])) == 0
		&& !exec->cmd[1])
		printf("unset: not enough arguments\n");
	else if (ft_strncmp(exec->cmd[0], "unset", ft_strlen(exec->cmd[0])) == 0)
		arguments_unset(exec->cmd, env, export);
}