/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:22:54 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/25 17:13:33 by rleslie-         ###   ########.fr       */
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

int	error_equal(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
		{
			if (i == 0)
				return (1);
			if (key[i - 1] == '-')
				return (1);
		}
		i++;
	}
	return (0);
}

int	parse_export(t_node **list, char *key)
{
	char	**split_key;
	
	if (key[ft_strlen(key) -1] == '-' || error_equal(key) == 1)
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
	return (0);
}

void	ft_export(t_node **list, char *key)
{
	t_node	*current;
	t_node	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (parse_export(list, key) == 1 || parse_export(list, key) == 2)
		return ;
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
