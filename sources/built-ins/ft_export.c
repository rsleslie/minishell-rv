/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:22:54 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/12 18:01:20 by rleslie-         ###   ########.fr       */
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
	t_node *temp;
	
	temp = export;
	while(temp != NULL)
	{
		if (temp->value == NULL)
			printf("declare -x %s\n", temp->variable);
		else
			printf("declare -x %s=\"%s\"\n", temp->variable, temp->value);
		temp = temp->next;
	}
}

int	ft_key_parser(char *key)
{
	char	**split_key;

	if (ft_lurkstr(key, '=') == 0)
	{
		split_key = ft_split(key, '=');
		if (split_key[1] == NULL)
			return (0);
		else
			return (1);
	}
	return (2);
}

// void	ft_export_env(t_node **list, char *key)
// {
// 	t_node	*current;
// 	t_node	*temp;
// 	int		i;

// 	i = 0;
// 	temp = create_node(key);
// 	current = (*list);
// 	while (current != NULL)
// 	{
// 		if (search_env(temp->variable, current->variable) == 0)
// 		{
// 			i = 1;
// 			free(current->value);
// 			current->value = ft_strdup(temp->value);
// 			ft_free_node(temp);
// 			return;
// 		}
// 		current = current->next;
// 	}
// 	if (i == 0)
// 		link_node_end(list,create_node(key));
// 	ft_free_node(temp);
// }


/*
OLD
NAO FUNCIONA COM VALGRIND
NA REAL POR ALGUM MOTIVO PAROU DE FUNCIONAR ATE SEM
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
void	ft_export(t_node **env, t_node **export, char *key)
{
	t_node	*node_env;
	t_node	*node_export;
	
	node_env = NULL;
	node_export = NULL;
	if (ft_key_parser(key) == 0)
	{
		node_env = create_node_null(key);
		ft_add_export(env, node_env);
		node_export = create_node_quotes(key);
		ft_add_export(export, node_export);
	}
	else if (ft_key_parser(key) == 1)
	{
		node_export = create_node(key);
		ft_add_export(env, node_export);
		ft_add_export(export, node_export);
	}
	else if (ft_key_parser(key) == 2)
	{
		t_node	*current;
		int		i;
	
		i = 0;
		current = (*export);
		while (current != NULL)
		{
			if (search_env(key, current->variable) == 0)
				return ;
			current = current->next;
		}
		node_export = create_node_null(key);
		ft_add_export(export, node_export);
	}
	//ft_free_node(node_env);
	//ft_free_node(node_export);
}

void	ft_add_export(t_node **list, t_node *node)
{
	t_node	*current;
	int		i;
	
	i = 0;
	current = (*list);
	while (current != NULL)
	{
		if (search_env(node->variable, current->variable) == 0)
		{
			i = 1;
			free(current->value);
			current->value = ft_strdup(node->value);
			//ft_free_node(node);
			return ;
		}
		current = current->next;
	}
	if (i == 0)
		link_node_end(list, node);
}*/
