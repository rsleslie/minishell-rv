/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:39:31 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/28 15:42:35 by rleslie-         ###   ########.fr       */
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

void	norminette_cd(char **data_str)
{
	char	buffer[1024];
	char	*temp;
	int		i;

	if (ft_isdigit(data_str[1][0]) != 0)
	{
		g_status_code = 1;
		return ;
	}
	getcwd(buffer, sizeof(buffer));
	temp = ft_strjoin(ft_strdup(buffer), "/");
	i = 0;
	while (data_str[++i] != NULL)
	{
		temp = ft_strjoin(temp, data_str[i]);
		temp = ft_strjoin(temp, "/");
	}
	if (chdir(temp) != 0)
		g_status_code = 0;
	else
		g_status_code = 0;
	free(temp);
}

void	ft_cd(char **data_str, t_node *env)
{	
	t_node	*current;

	if (data_str[1] == NULL)
	{
		current = aux_cd(env);
		chdir(current->value);
		g_status_code = 0;
		return ;
	}
	else if (ft_strncmp(data_str[1], "..", ft_strlen(data_str[1])) == 0)
	{
		chdir("..");
		g_status_code = 0;
	}
	else if (ft_strncmp(data_str[1], "$PWD", ft_strlen(data_str[1])) == 0)
	{
		g_status_code = 1;
		return ;
	}
	else
		norminette_cd(data_str);
}
