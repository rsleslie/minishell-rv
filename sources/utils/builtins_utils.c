/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:38:54 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/16 16:51:28 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	arguments_export(char **data_str, t_node *env, t_node *export)
{
	int	i;

	i = 1;
	while (data_str[i])
	{
		if (ft_lurkstr(data_str[i], '=') == 1)
			ft_export(&export, data_str[i]);
		else
		{
			ft_export(&export, data_str[i]);
			ft_export(&env, data_str[i]);
		}
		i++;
	}
}

void	arguments_unset(char **data_str, t_node *env, t_node *export)
{
	int	i;

	i = 1;
	while (data_str[i])
	{
		ft_unset(&export, data_str[i]);
		ft_unset(&env, data_str[i]);
		i++;
	}
}

int	search_env(char *data, char *key)
{
	int	len_data;
	int	len_key;

	len_data = ft_strlen(data);
	len_key = ft_strlen(key);
	if (len_data == len_key)
	{
		if (ft_strncmp(data, key, len_data) == 0)
			return (0);
	}	
	return (1);
}
