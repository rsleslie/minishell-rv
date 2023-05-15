/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:11:20 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/15 18:24:55 by rleslie-         ###   ########.fr       */
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

	i = 0;
	if(str && str[i])
	{
		i = -1;
		while (str[++i] != NULL)
		{
			if (str[i] != NULL)
			{
				free(str[i]);
				str[i] = NULL;
			}
		}
	}
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void	is_null(char **str)
{
	int	i;

	i = 0;
	if(str && str[i])
	{
		ft_free_tab(str);
	}
}

void	ft_free_exec(t_exec *exec)
{
	t_exec	*aux;
	t_exec	*next;
	
	aux = exec;
	while (aux != NULL)
	{
		ft_free_tab(exec->cmd);
		ft_free_tab(exec->redirect);
		next = aux->next;
		free(aux);
		aux = next;
	}
	if (exec)
		free(exec);
}

void freeLinkedList(t_exec *head) {
    t_exec *current = head;
    t_exec *next;

    while (current != NULL) {
        // Liberar a memória alocada para cmd e redirect
        for (int i = 0; current->cmd[i] != NULL; i++) {
            free(current->cmd[i]);
        }
        free(current->cmd);

        for (int i = 0; current->redirect[i] != NULL; i++) {
            free(current->redirect[i]);
        }
        free(current->redirect);

        // Avançar para o próximo nó e liberar o atual
        next = current->next;
        free(current);

        current = next;
    }
}
