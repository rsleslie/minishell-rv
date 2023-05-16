/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:19:01 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/16 19:13:49 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	search_var(t_node *list, char *exec, char *key)
{
	t_node	*aux;

	aux = list;
	while (aux != NULL)
	{
		if (search_env(key, aux->variable) == 0)
		{
			free(exec);
			exec = ft_strdup(aux->value);
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}

void dollar_sign(t_exec *exec, t_node *env)
{
	t_exec	*aux;
	int		i;
	int		j;

	j = 0;
	aux = exec;
	while (aux)
	{
		i = 0;
		while(aux->cmd[i])
		{
			if (aux->cmd[i][0] == '$')
				search_var(env, exec->cmd[i], &exec->cmd[i][1]);
			i++;
		}
		aux = aux->next;
	}
}	
