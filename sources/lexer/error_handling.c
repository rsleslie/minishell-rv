/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:31:16 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 20:39:18 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	move_quotes(t_config *data, int i)
{
	char	c;
	int		x;

	x = i + 1;
	c = data->str[i];
	if (data->str[i - 1] == '<')
		return ;
	while (data->str[x])
	{
		if (data->str[x] == 32 || data->str[x] == c)
			break ;
		x++;
	}
	if (data->str[x] == 32)
		move(data, i);
	if (data->str[x] == c)
		remov_quotes(data, i);
}

int	ft_strrchr_int(const char *s, int c, int position)
{
	int	i;

	i = position;
	while (s[++i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
	}
	return (i);
}

int	error_quotes_check(t_config *data)
{
	size_t	i;

	i = -1;
	while (data->str[++i])
	{
		if (data->str[i] == DOUBLE_QUOTE || data->str[i] == SIMPLE_QUOTE)
		{
			i = ft_strrchr_int(data->str, data->str[i], i);
			if (i == (ft_strlen(data->str)))
			{
				ft_putstr_fd("minishell: quotes error\n", 2);
				g_data.status_code = 0;
				return (1);
			}
		}
	}
	return (0);
}

int	double_quotes(t_config *data, int i)
{
	if ((data->str[i] == DOUBLE_QUOTE || data->str[i] == SIMPLE_QUOTE)
		&& data->str[i + 1] == data->str[i] && (i + 1) == 1)
	{
		g_data.status_code = 1;
		ft_putstr_fd("minishell: command not found\n", 2);
		return (1);
	}
	return (0);
}

int	error_quotes(t_config *data)
{
	int		i;

	i = -1;
	if (error_quotes_check(data) == 1)
		return (1);
	while (data->str && data->str[++i])
	{
		if (double_quotes(data, i) == 1)
			return (1);
		if (i != 0)
		{
			if ((data->str[i] == DOUBLE_QUOTE || data->str[i] == SIMPLE_QUOTE)
				&& data->str[i + 1] == data->str[i])
				rm_quotes(data, i);
			if ((data->str[i] == DOUBLE_QUOTE || data->str[i] == SIMPLE_QUOTE)
				&& data->str[i - 1] != 32 && data->str[i + 1] != 32)
				move_quotes(data, i);
			if ((data->str[i] == DOUBLE_QUOTE || data->str[i] == SIMPLE_QUOTE)
				&& i < (int)ft_strlen(data->str) - 1)
			{
				i = ft_strrchr_int(data->str, data->str[i], i);
			}
		}
	}
	return (0);
}
