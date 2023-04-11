/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:13 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/11 15:15:37 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_config *data)
{
	char	**split_exit;

	split_exit = ft_split(data->str, ' ');
	if (ft_strncmp(split_exit[0], "exit", ft_strlen(split_exit[0])) == 0)
	{
		if ((ft_tab_len(split_exit) == 1) || (ft_tab_len(split_exit) == 2
				&& ft_isnum(split_exit[1]) == 1))
		{	
			printf("exit\n");
			exit (0);
		}
		else if (ft_isnum(split_exit[1]) == 0)
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				split_exit[1]);
			exit (0);
		}
		else if (ft_tab_len(split_exit) > 2)
		{
			printf("exit\nminishell: exit: too many arguments\n");
		}
	}
	ft_free_tab(split_exit);
}
