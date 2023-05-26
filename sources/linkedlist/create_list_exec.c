/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:26:43 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/25 20:36:52 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exec	*create_node_exec(char **str_cmd, char **str_redirect, t_lexer *exec)
{
	t_exec	*node;

	node = malloc(sizeof(t_exec));
	node->cmd = strdup_tab(str_cmd, exec->j, exec->i);
	node->redirect = strdup_tab(str_redirect, 0, ft_tab_len(str_redirect));
	node->is_builtin = exec->builtins;
	node->index = exec->index;
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
