/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:57:21 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/06 13:08:31 by rleslie-         ###   ########.fr       */
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
	exit (g_status_code);
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
