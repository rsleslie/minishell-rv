/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:30:18 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/17 15:04:51 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_env(t_node **env, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		link_node_end(env, create_node(envp[i]));
}

void	print_env(t_node *env)
{
	t_node	*temp;

	temp = env;
	while (temp)
	{
		printf("%s=%s\n", temp->variable, temp->value);
		temp = temp->next;
	}
}
