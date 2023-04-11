/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:11:20 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/11 16:57:27 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_node(t_node *data)
{
	if (data)
	{
		free(data->variable);
		free(data->value);
		free(data);
	}
}

void	ft_free_list(t_node *list)
{
	if (list)
	{
		ft_free_list(list->next);
		ft_free_node(list);
	}
}

void	ft_free_tab(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	if (str)
		free(str);
}
