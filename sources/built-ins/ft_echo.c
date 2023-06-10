/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:26:21 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/10 16:52:55 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	aux_echo(char **data_str, int tab_len)
{
	int	i;

	i = 0;
	while (++i < tab_len)
	{
		ft_printf("%s", data_str[i]);
		if (i != tab_len - 1)
			ft_printf(" ");
	}
	ft_printf("\n");
}

void	ft_echo(char **data_str)
{
	int	tab_len;
	int	i;

	i = 0;
	tab_len = ft_tab_len(data_str);
	if (tab_len == 1)
		write(1, "\n", 1);
	else if (ft_strncmp(data_str[1], "-n", ft_strlen(data_str[1])) == 0)
	{
		if (tab_len > 2)
		{
			i = 1;
			while (++i < tab_len)
			{				
				printf("%s", data_str[i]);
				if (i != tab_len - 1)
					printf(" ");
			}	
		}
	}
	else
		aux_echo(data_str, tab_len);
}
