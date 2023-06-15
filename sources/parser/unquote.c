/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:45:12 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 19:35:06 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	aux_strip_quotes(t_exec *exec, int i, int size, char *ptr)
{
	int	j;

	j = 0;
	while (exec->cmd[i][size])
	{
		ptr[j] = exec->cmd[i][size];
		size++;
		if (exec->cmd[i][size] == SIMPLE_QUOTE
			|| exec->cmd[i][size] == DOUBLE_QUOTE)
			size++;
		j++;
	}
	return (j);
}

char	*strip_quotes(t_exec *exec, int i)
{
	char	*ptr;
	int		size;
	int		j;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(exec->cmd[i]) - 1));
	size = 1;
	j = 0;
	if (exec->cmd[i][size] == '$'
		&& exec->cmd[i][size + 1] == exec->cmd[i][size - 1])
		j = aux_strip_quotes(exec, i, size, ptr);
	else
	{
		while (exec->cmd[i][size + 1])
		{
			ptr[j] = exec->cmd[i][size];
			size++;
			j++;
		}
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*strip_quotes_two(t_exec *exec, int i)
{
	char	*ptr;
	int		size;
	int		j;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(exec->redirect[i]) - 1));
	size = 1;
	j = 0;
	while (exec->redirect[i][size + 1])
	{
		ptr[j] = exec->redirect[i][size];
		size++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

void	aux_unquotes(t_exec *aux)
{
	int		i;
	char	*new_value;

	i = -1;
	while (aux->redirect[++i])
	{
		if (aux->redirect[i][0] == DOUBLE_QUOTE
			|| aux->redirect[i][0] == SIMPLE_QUOTE)
		{
			new_value = strip_quotes_two(aux, i);
			free(aux->redirect[i]);
			aux->redirect[i] = ft_strdup(new_value);
			free(new_value);
		}
	}
}

void	unquotes(t_exec *exec)
{
	int		i;
	t_exec	*aux;
	char	*new_value;

	aux = exec;
	while (aux != NULL)
	{
		i = -1;
		while (aux->cmd && aux->cmd[++i])
		{
			if (aux->cmd[i][0] == DOUBLE_QUOTE
				|| aux->cmd[i][0] == SIMPLE_QUOTE)
			{
				new_value = strip_quotes(aux, i);
				free(aux->cmd[i]);
				aux->cmd[i] = ft_strdup(new_value);
				free(new_value);
			}
		}
		aux_unquotes(aux);
		aux = aux->next;
	}
}
