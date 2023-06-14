/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:52:13 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/14 19:16:01 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_path(t_node **env, t_config *data)
{
	t_node	*aux;

	aux = (*env);
	while (aux->next != NULL)
	{
		if (search_env(aux->variable, "PATH") == 0)
		{
			data->paths = ft_split(aux->value, ':');
			return ;
		}
		aux = aux->next;
	}
	data->paths = NULL;
}
