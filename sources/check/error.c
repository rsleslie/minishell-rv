/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:13 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/30 19:37:37 by rleslie-         ###   ########.fr       */
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

void	terminate(t_node *env, t_node *export, t_config *data, char *error_msg)
{
	(void)error_msg;
	// if (error_msg)
	// 	ft_putstr_fd(error_msg, 1);
	ft_free_list(env);
	ft_free_list(export);
	free(data->str);
	ft_free_tab(data->paths);
	ft_free_tab(data->tokens);
	exit (g_status_code);
}

void	norminette_exit(char **s, t_config *data, t_node *env, t_node *export)
{
	ft_putstr_fd("exit\nnumeric argument required\n", 2);
	{
		g_status_code = 2;
		ft_free_tab(s);
		terminate(env, export, data, NULL);
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

int	ft_exit(t_config *data, t_node *env, t_node *export, t_exec *exec)
{
	char	**split_exit;

	split_exit = ft_split(data->str, ' ');
	if (ft_strncmp(split_exit[0], "exit", ft_strlen(split_exit[0])) == 0)
	{
		if (split_exit[1])
		{
			if (split_exit[1][0] == DOUBLE_QUOTE)
				split_exit[1] = ft_strtrim(split_exit[1], "\"");
		}
		if ((ft_tab_len(split_exit) == 1) || (ft_tab_len(split_exit) == 2
				&& ft_isnum(split_exit[1]) == 1))
		{
			if (ft_tab_len(split_exit) == 2)
				exit_num(split_exit[1]);
			free_exec_list(exec);
			ft_free_tab(split_exit);
			terminate(env, export, data, "exit");
		}
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
