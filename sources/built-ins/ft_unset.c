/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:13:33 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/24 14:03:58 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_node **list, char *key)
{
	t_node		*current;
	t_node		*temp;

	temp = NULL;
	current = (*list);
	while (current != NULL)
	{
		if (search_env(current->variable, key) == 0)
		{
			if (temp == NULL)
				(*list) = (*list)->next;
			else
				temp->next = current->next;
			ft_free_node(current);
			return ;
		}
		temp = current;
		current = current->next;
	}	
}
