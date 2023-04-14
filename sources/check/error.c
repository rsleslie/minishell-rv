/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:13 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/13 18:44:04 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	terminate(t_node *env, t_node *export, char **split, char *error_msg)
{
	if (error_msg)
		ft_printf("%s\n", error_msg);
	ft_free_list(env);
	ft_free_list(export);
	ft_free_tab(split);
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
			terminate(env, export, split_exit, "exit");
		else if (ft_isnum(split_exit[1]) == 0)
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				split_exit[1]);
			terminate(env, export, split_exit, NULL);
		}
		else if (ft_tab_len(split_exit) > 2)
		{
			printf("exit\nminishell: exit: too many arguments\n");
		}
	}
	ft_free_tab(split_exit);
}
