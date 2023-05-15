/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:26:43 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/15 17:30:51 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exec	*create_node_exec(char **str, char **redirect, int index, int i)
{
	t_exec *node;
	char	**if_null = (char *[]){"*", 0};
	
	node = malloc(sizeof(t_exec));
	node->cmd = strdup_tab(str, 0, i);
	if (!redirect)
		node->redirect = strdup_tab(if_null, 0, ft_tab_len(if_null));
	else
		node->redirect = strdup_tab(redirect, 0, ft_tab_len(redirect));
	node->is_builtin = op_builtins(str[0]);
	node->index = index;
	node->next = NULL;
	return (node);
}


t_exec	*exec_node_last(t_exec *list)
{
	t_exec	*aux;

	aux = list;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	exec_link_node_end(t_exec **list, t_exec *node)
{
	t_exec	*aux;

	if (list == NULL)
		return ;
	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	aux = exec_node_last(*list);
	aux->next = node;
}
