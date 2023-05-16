/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:39:31 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/16 16:13:56 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*aux_cd(t_node *env)
{
	t_node	*current;

	current = env;
	while (current->next)
	{
		if (search_env("HOME", current->variable) == 0)
			break ;
		current = current->next;
	}
	return (current);
}

void	ft_cd(char **data_str, t_node *env)
{
	char	buffer[1024];
	char	*temp;
	t_node	*current;
	int		i;
	
	if (data_str[1] == NULL)
	{
		current = aux_cd(env);
		chdir(current->value);
		return ;
	}
	else if (ft_strncmp(data_str[1], "..", ft_strlen(data_str[1])) == 0)
		chdir("..");
	else
	{
		getcwd(buffer, sizeof(buffer));
		temp = ft_strjoin(buffer, "/");
		i = 0;
		while(data_str[++i] != NULL)
		{
			temp = ft_strjoin(temp, data_str[i]);
			temp = ft_strjoin(temp, "/");
		}
		if (chdir(temp) != 0)
		{
			printf("minishell: cd: %s: %s\n",
				data_str[1], strerror(errno));
		}
		free(temp);
	}
}
