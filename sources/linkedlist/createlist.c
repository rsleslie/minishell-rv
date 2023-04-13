/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:09:17 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/12 16:58:07 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*create_node(char *data)
{
	t_node	*aux;
	char	**split_data;

	split_data = ft_split(data, '=');
	aux = malloc(sizeof(t_node));
	aux->variable = ft_strdup(split_data[0]);
	aux->value = ft_strdup(split_data[1]);
	aux->next = NULL;
	ft_free_tab(split_data);
	return (aux);
}

t_node	*node_last(t_node *list)
{
	t_node	*aux;

	aux = list;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	link_node_end(t_node **list, t_node *node)
{
	t_node	*aux;

	if (list == NULL)
		return ;
	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	aux = node_last(*list);
	aux->next = node;
}

t_node	*create_node_null(char *data)
{
	t_node	*aux;
	char	**split_data;

	split_data = ft_split(data, '=');
	aux = malloc(sizeof(t_node));
	aux->variable = ft_strdup(split_data[0]);
	aux->value = " ";
	aux->next = NULL;
	ft_free_tab(split_data);
	return (aux);
}

t_node	*create_node_quotes(char *data)
{
	t_node	*aux;
	char	**split_data;

	split_data = ft_split(data, '=');
	aux = malloc(sizeof(t_node));
	aux->variable = ft_strdup(split_data[0]);
	aux->value = "";
	aux->next = NULL;
	ft_free_tab(split_data);
	return (aux);
}
