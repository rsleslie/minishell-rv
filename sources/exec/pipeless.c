/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeless.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:14:00 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/12 15:08:09 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	t_config	vars;

	if (validation_cmd(exec, data) != 0)
		return ;
	if (exec->fd_input == -1 || exec->fd_output == -1)
	{
		data->status_code = 1;
		return ;
	}
	if (op_builtins(exec->cmd[0]) != 0)
	{
		executor(exec, data, env, export);	
	}
	else
	{
		vars.pid = fork();
		signal_handler_child();
		if (vars.pid == 0)
			executor(exec, data, env, export);
		vars.status = 0;
		waitpid(vars.pid, &vars.status, 0);
		if (WIFEXITED(vars.status))
			data->status_code = WEXITSTATUS(vars.status);
	}
}
