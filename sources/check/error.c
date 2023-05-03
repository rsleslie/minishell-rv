/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:13 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/03 15:06:41 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	terminate(t_node *env, t_node *export, t_config *data, char *error_msg)
{
	if (error_msg)
		ft_printf("%s\n", error_msg);
	ft_free_list(env);
	ft_free_list(export);
	free(data->str);
	//ft_free_tab(data->cmd);
	//ft_free_tab(data->paths);
	ft_free_tab(data->tokens);
	exit (0);
}

void	ft_exit(t_config *data, t_node *env, t_node *export)
{
	char	**split_exit;

	split_exit = ft_split(data->str, ' ');
	if (ft_strncmp(split_exit[0], "exit", ft_strlen(split_exit[0])) == 0)
	{
		if ((ft_tab_len(split_exit) == 1) || (ft_tab_len(split_exit) == 2
				&& ft_isnum(split_exit[1]) == 1))
		{
			ft_free_tab(split_exit);
			terminate(env, export, data, "exit");
		}
		else if (ft_isnum(split_exit[1]) == 0)
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				split_exit[1]);
			{
				ft_free_tab(split_exit);
				terminate(env, export, data, NULL);
			}
		}
		else if (ft_tab_len(split_exit) > 2)
			printf("exit\nminishell: exit: too many arguments\n");
	}
	ft_free_tab(split_exit);
}


// void	terminate(t_node *env, t_node *export, t_config *data, char *error_msg)
// {
// 	if (error_msg)
// 		ft_printf("%s\n", error_msg);
// 	ft_free_list(env);
// 	ft_free_list(export);
// 	ft_free_tab(data->cmd);
// 	ft_free_tab(data->paths);
// 	ft_free_tab(data->tokens);
// 	// free(data->str);
// 	exit (0);
// }

// void	ft_exit(t_config *data, t_node *env, t_node *export)
// {
// 	if (ft_strncmp(data->tokens[0], "exit", ft_strlen(data->tokens[0])) == 0)
// 	{
// 		if ((ft_tab_len(data->tokens) == 1) || (ft_tab_len(data->tokens) == 2
// 				&& ft_isnum(data->tokens[1]) == 1))
// 			terminate(env, export, data, "exit");
// 		else if (ft_isnum(data->tokens[1]) == 0)
// 		{
// 			printf("exit\nminishell: exit: %s: numeric argument required\n",
// 				data->tokens[1]);
// 			terminate(env, export, data, NULL);
// 		}
// 		else if (ft_tab_len(data->tokens) > 2)
// 			printf("exit\nminishell: exit: too many arguments\n");
// 	}
// }

