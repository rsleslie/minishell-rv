/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:57:21 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 20:40:33 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_var(t_node *env, t_node *export, t_config *data, t_exec *exec)
{
	free(data->str);
	ft_free_tab(data->paths);
	ft_free_tab(data->tokens);
	ft_free_list(env);
	ft_free_list(export);
	free_exec_list(exec);
}

void	terminate(t_node *env, t_node *export, t_config *data)
{
	ft_free_list(env);
	ft_free_list(export);
	free(data->str);
	ft_free_tab(data->paths);
	ft_free_tab(data->tokens);
	close(STDOUT_FILENO);
	rl_clear_history();
	exit (data->status_code);
}

int	check_space(t_config *data)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (data->str[i])
	{
		if (data->str[i] != 32 && !(data->str[i] >= 9 && data->str[i] <= 13))
			counter++;
		i++;
	}
	return (counter);
}

int	ft_init_exit(t_config *data, char **split_exit)
{
	trim_quotes(split_exit);
	if (exit_norm(split_exit, data->node_exec) == 1)
		terminate(data->node_env, data->node_export, data);
	else if (ft_tab_len(split_exit) > 2 && ft_isnum(split_exit[1]) != 0)
	{
		g_data.status_code = 1;
		ft_free_tab(split_exit);
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (ft_isnum(split_exit[1]) == 0)
	{
		free_exec_list(data->node_exec);
		norminette_exit(split_exit, data, data->node_env, data->node_export);
	}
	return (0);
}
