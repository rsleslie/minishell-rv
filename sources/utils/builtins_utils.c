/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:38:54 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/17 14:58:01 by rleslie-         ###   ########.fr       */
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
