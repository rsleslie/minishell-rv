/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:26:43 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/12 19:39:48 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exec	*create_node_exec(char **str_cmd, char **str_redirect, int builtin, int index)
{
	t_exec *node;
	
	node = malloc(sizeof(t_exec));
	node->cmd = str_cmd;
	node->redirect = str_redirect;
	node->is_builtin = builtin;
	node->index = index;
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
