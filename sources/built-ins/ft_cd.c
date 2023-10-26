/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:39:31 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 19:22:46 by rleslie-         ###   ########.fr       */
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
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

void	norminette_cd(char **data_str)
{
	char	buffer[1024];
	char	*temp;
	int		i;

	if (ft_isdigit(data_str[1][0]) != 0)
	{
		g_data.status_code = 1;
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
	{
		g_data.status_code = 1;
		ft_putstr_fd("minishell: No such file or directory\n", 2);
	}
	else
		g_data.status_code = 0;
	free(temp);
}

int	cd_acess(char *str)
{
	if (access(str, F_OK) == 0)
	{
		if (chdir(str) != 0)
		{
			ft_putstr_fd("minishell: Not a directory\n", 2);
			return (1);
		}
		g_data.status_code = 0;
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return (1);
	}
}

void	cd_null(t_node *current, t_node *env)
{
	current = aux_cd(env);
	if (current == NULL)
	{
		g_data.status_code = 1;
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return ;
	}
	chdir(current->value);
	g_data.status_code = 0;
	return ;
}

void	ft_cd(char **data_str, t_node *env)
{	
	t_node	*current;

	current = NULL;
	if (data_str[1] == NULL)
	{
		cd_null(current, env);
		return ;
	}
	else if (ft_strncmp(data_str[1], "..", ft_strlen(data_str[1])) == 0)
	{
		chdir("..");
		g_data.status_code = 0;
	}
	else if (data_str[1][0] == '.' || data_str[1][0] == '/')
	{
		if (cd_acess(data_str[1]) == 1)
			g_data.status_code = 1;
	}
	else
		norminette_cd(data_str);
}
