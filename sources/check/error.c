/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:13 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 15:15:49 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norminette_exit(char **s, t_config *data, t_node *env, t_node *export)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(s[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	{
		data->status_code = 2;
		ft_free_tab(s);
		terminate(env, export, data);
	}
}

void	exit_num(char *str)
{
	if (ft_atoull(str) > 9223372036854775807 || ft_strlen(str) > 19)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		g_data.status_code = 2;
		if (ft_strncmp(str, "-9223372036854775808", 20) == 0)
			g_data.status_code = 0;
		if (ft_strncmp(str, "-9223372036854775807", 20) == 0)
			g_data.status_code = 1;
	}
	else
		g_data.status_code = ft_atoll(str);
}

void	trim_quotes(char **split_exit)
{
	if (split_exit[1])
	{
		if (split_exit[1][0] == DOUBLE_QUOTE)
			split_exit[1] = ft_strtrim(split_exit[1], "\"");
	}
}

int	exit_norm(char **split_exit, t_exec *exec)
{
	if ((ft_tab_len(split_exit) == 1) || (ft_tab_len(split_exit) == 2
			&& ft_isnum(split_exit[1]) == 1))
	{
		ft_putendl_fd("exit", 2);
		if (ft_tab_len(split_exit) == 2)
			exit_num(split_exit[1]);
		free_exec_list(exec);
		ft_free_tab(split_exit);
		return (1);
	}
	return (0);
}

int	ft_exit(t_config *data)
{
	char	**split_exit;

	split_exit = ft_split(data->str, ' ');
	if (ft_strncmp(split_exit[0], "exit", 5) == 0)
	{
		if (ft_init_exit(data, split_exit) == 1)
			return (1);
	}
	ft_free_tab(split_exit);
	return (0);
}
