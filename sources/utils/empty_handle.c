/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:08:25 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 14:08:46 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_space_tab(char **tab)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (tab[++i])
	{
		if (tab[i][0] == 32 && ft_strlen(tab[i]) == 1)
			continue ;
		counter++;
	}
	return (counter);
}

void	reset_exec_tab(t_exec *exec)
{
	char	**aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!exec->cmd)
		return ;
	aux = (char **)ft_calloc(sizeof(t_exec), count_space_tab(exec->cmd) + 1);
	while (exec->cmd[i])
	{
		if (exec->cmd[i][0] != 32 || ft_strlen(exec->cmd[i]) > 1)
		{
			aux[j] = ft_strdup(exec->cmd[i]);
			j++;
		}
		i++;
	}
	aux[count_space_tab(exec->cmd)] = NULL;
	ft_free_tab(exec->cmd);
	exec->cmd = aux;
}

void	empty_cmd_handle(t_exec *exec)
{
	t_exec	*aux;
	int		i;

	aux = exec;
	i = -1;
	while (aux != NULL)
	{
		reset_exec_tab(aux);
		aux = aux->next;
	}
}
