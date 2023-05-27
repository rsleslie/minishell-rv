/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:55:48 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/26 19:30:06 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	error_equal(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
		{
			if (i == 0)
			{
				ft_printf(" not a valid identifier");
				return (1);
			}
			if (key[i - 1] == '-')
			{
				ft_printf(" not a valid identifier");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	aux_search(t_node **list, char *key, int i)
{
	t_node	*current;

	current = (*list);
	while (current != NULL)
	{
		if (search_env(key, current->variable) == 0)
		{
			if (i == 1)
			{
				free(current->value);
				current->value = ft_strdup("");
			}
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	aux_parser(t_node **list, char *key)
{
	char	**split_key;

	split_key = ft_split(key, '=');
	if (aux_search(list, split_key[0], 1) == 1)
	{
		ft_free_tab(split_key);
		return (2);
	}
	link_node_end(list, create_node_null(split_key[0]));
	ft_free_tab(split_key);
	return (2);
}

int	parse_export(t_node **list, char *key)
{
	if (key[ft_strlen(key) -1] == '-' || error_equal(key) == 1
		|| ft_isdigit(key[0]) != 0)
	{
		g_status_code = 1;
		return (1);
	}
	if (ft_strcs(key, '=') == 0)
	{
		if (aux_search(list, key, 0) == 1)
			return (1);
		link_node_end(list, create_node_null(key));
		return (1);
	}
	if (!key[ft_strcs(key, '=') + 1])
	{
		if (aux_parser(list, key) == 2)
			return (2);
	}
	return (0);
}
