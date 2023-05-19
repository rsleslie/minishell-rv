/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:45:12 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/19 13:00:22 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void strip_quotes(t_exec *exec, int i)
{
	char	*ptr;
	int		j;
	int		size;
	
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(exec->cmd[i]) - 2));
	size = 1;
	j = 0;
	while(exec->cmd[i][size + 1])
	{
		ptr[j] = exec->cmd[i][size];
		size++;
		j++;
	}
	ptr[j] = '\0';
	free(exec->cmd[i]);
	exec->cmd[i] = ft_strdup(ptr);
	free(ptr);
}

void unquotes(t_exec *exec)
{
	t_exec *aux;
	int		i;

	aux = exec;
	while(aux != NULL)
	{
		i = -1;
		while(aux->cmd[++i])
		{
			if (aux->cmd[i][0] == DOUBLE_QUOTE || aux->cmd[i][0] == SIMPLE_QUOTE)
				strip_quotes(exec, i);
		}
		aux = aux->next;
	}
}