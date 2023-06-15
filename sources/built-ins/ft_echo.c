/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:26:21 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 19:08:39 by rleslie-         ###   ########.fr       */
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
	g_data.status_code = 0;
	ft_printf("\n");
}

int	echo_is_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n' && str[i] != '\0')
			return (0);
	}
	return (1);
}

void	ft_echo(char **data_str)
{
	int	tab_len;
	int	i;

	i = 0;
	tab_len = ft_tab_len(data_str);
	if (tab_len == 1)
		write(1, "\n", 1);
	else if (echo_is_n(data_str[1]))
	{
		if (tab_len > 2)
		{
			i = 1;
			while (++i < tab_len)
			{				
				ft_printf("%s", data_str[i]);
				if (i != tab_len - 1)
					ft_printf(" ");
			}
		}
	}
	else
		aux_echo(data_str, tab_len);
	g_data.status_code = 0;
}
