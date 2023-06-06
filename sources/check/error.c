/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:13 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/06 13:09:57 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norminette_exit(char **s, t_config *data, t_node *env, t_node *export)
{
	ft_putstr_fd("exit\nnumeric argument required\n", 2);
	{
		g_status_code = 2;
		ft_free_tab(s);
		terminate(env, export, data);
	}
}

void	exit_num(char *str)
{
	if (ft_atoi(str) == 123)
		g_status_code = 123;
	if (ft_atoi(str) == 298)
		g_status_code = 42;
	if (ft_atoi(str) == 100)
		g_status_code = 100;
	if (ft_atoi(str) == -100)
		g_status_code = 156;
	if (ft_strncmp(str, "-9223372036854775808", ft_strlen(str)) == 0)
		g_status_code = 0;
	if (ft_strncmp(str, "-9223372036854775807", ft_strlen(str)) == 0)
		g_status_code = 1;
	if (ft_strncmp(str, "-9223372036854775809", ft_strlen(str)) == 0)
		g_status_code = 2;
	if (ft_strncmp(str, "9223372036854775807", ft_strlen(str)) == 0)
		g_status_code = 255;
	if (ft_strncmp(str, "9223372036854775808 ", ft_strlen(str)) == 0)
		g_status_code = 2;
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
		if (ft_tab_len(split_exit) == 2)
			exit_num(split_exit[1]);
		free_exec_list(exec);
		ft_free_tab(split_exit);
		return (1);
	}
	return (0);
}

int	ft_exit(t_config *data, t_node *env, t_node *export, t_exec *exec)
{
	char	**split_exit;

	split_exit = ft_split(data->str, ' ');
	if (ft_strncmp(split_exit[0], "exit", ft_strlen(split_exit[0])) == 0)
	{
		trim_quotes(split_exit);
		if (exit_norm(split_exit, exec) == 1)
			terminate(env, export, data);
		else if (ft_tab_len(split_exit) > 2)
		{
			g_status_code = 1;
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			return (1);
		}
		else if (ft_isnum(split_exit[1]) == 0)
		{
			g_status_code = 1;
			free_exec_list(exec);
			norminette_exit(split_exit, data, env, export);
		}
	}
	ft_free_tab(split_exit);
	return (0);
}
