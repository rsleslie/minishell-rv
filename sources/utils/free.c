/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:11:20 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/13 17:01:50 by rleslie-         ###   ########.fr       */
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
	if (str == NULL)
		return ;
	if (str && str[i])
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

void	ft_free_tab_int(int **fd, int size)
{
	int	i;

	i = 0;
	if (fd == NULL)
		return ;
	if (size < 1)
		return ;
	if (fd && fd[i])
	{
		i = -1;
		while (++i < size)
		{
			if (fd[i])
				free(fd[i]);
		}
	}
	if (fd)
		free(fd);
}

void	free_exec_list(t_exec *exec)
{
	t_exec	*aux;
	t_exec	*next;
	int		i;

	i = -1;
	aux = exec;
	while (aux != NULL)
	{
		i = -1;
		while (aux->cmd && aux->cmd[++i])
			free(aux->cmd[i]);
		free(aux->cmd);
		i = -1;
		while (aux->redirect && aux->redirect[++i])
			free(aux->redirect[i]);
		free(aux->redirect);
		next = aux->next;
		free(aux);
		aux = next;
	}
}
