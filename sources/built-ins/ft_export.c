/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:22:54 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/13 12:00:13 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_export(t_node **export, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		link_node_end(export, create_node(envp[i]));
		i++;
	}
}

void	print_export(t_node *export)
{
	t_node	*temp;

	temp = export;
	while (temp != NULL)
	{
		if (temp->value == NULL)
			ft_printf("declare -x %s\n", temp->variable);
		else
			ft_printf("declare -x %s=\"%s\"\n", temp->variable, temp->value);
		temp = temp->next;
	}
}

int	aux_export(t_node **list, char *key)
{
	int	i;

	i = parse_export(list, key);
	if (i == 1 || i == 2 || i == 3)
	{
		if (i == 3)
			g_data.status_code = 0;
		else
			g_data.status_code = 1;
		return (1);
	}
	return (0);
}

void	ft_export(t_node **list, char *key)
{
	t_node	*current;
	t_node	*temp;
	int		i;

	temp = NULL;
	if (aux_export(list, key) == 1)
		return ;
	i = 0;
	temp = create_node(key);
	current = (*list);
	while (current != NULL)
	{
		if (search_env(temp->variable, current->variable) == 0)
		{
			i = 1;
			free(current->value);
			current->value = ft_strdup(temp->value);
			ft_free_node(temp);
			return ;
		}
		current = current->next;
	}
	if (i == 0)
		link_node_end(list, create_node(key));
	ft_free_node(temp);
}
