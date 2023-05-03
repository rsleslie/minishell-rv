/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:52:13 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/25 15:34:20 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**split_path(char *path)
{
	char	**broken_path;

	broken_path = ft_split(path, ':');
	return (broken_path);
}

void	handle_path(t_node **env, t_config *data)
{
	t_node	*aux;

	aux = (*env);
	while (aux->next != NULL)
	{
		if (search_env(aux->variable, "PATH") == 0)
			break ;
		aux = aux->next;
	}
	data->paths = split_path(aux->value);
}

// int		tentando_usar_exec(char *cmd, char *key)
// {
// 	int		pid;
// 	char	*str;
// 	char	*str1[] = {key, NULL};

// 	str = ft_strjoin(cmd, "/");
// 	str = ft_strjoin(str, key);
// 	if (access(str, F_OK) == 0)
// 	{
// 		pid = fork();		
// 		if (pid == 0)
// 		{
// 			execve(str, str1, NULL);
// 			exit (0);
// 		}
// 	}
// 	int status = 1;
// 	wait(&status);
// 	return (status);
// }

// int	cmd_exist(t_config *data, char *key)
// {
// 	int	i;

// 	i = 0;
// 	while (data->paths[i])
// 	{
// 		if (tentando_usar_exec(data->paths[i], key) == 0)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
