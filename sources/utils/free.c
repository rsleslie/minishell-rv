/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:11:20 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/15 19:16:12 by rleslie-         ###   ########.fr       */
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
			if (str[i])
				free(str[i]);
		}
	}
	if (str)
		free(str);
}

void	is_null(char **str)
{
	if(str && *str)
		ft_free_tab(str);
}

void free_exec_list(t_exec *head) 
{
    t_exec *current = head;
    t_exec *next;
    
    while (current != NULL) {
        // Libera a memória alocada para cmd e redirect
        for (int i = 0; current->cmd[i]; i++) {
            free(current->cmd[i]);
        }
        free(current->cmd);
		
        for (int i = 0; current->redirect[i]; i++) {
            free(current->redirect[i]);
        }
        
		free(current->redirect);
        // Move para o próximo elemento da lista
        next = current->next;
        free(current);
        current = next;
    }
}
