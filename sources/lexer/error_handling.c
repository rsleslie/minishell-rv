/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:31:16 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/12 11:31:59 by rleslie-         ###   ########.fr       */
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

void	error_quotes(t_config *data)
{
	int		i;
	char	c;

	i = -1;
	while (data->str[++i])
	{
		c = data->str[i];
		if ((c == DOUBLE_QUOTE || c == SIMPLE_QUOTE) && i == 0)
			i = ft_strrchr_int(data->str, c, i);
		if ((c == DOUBLE_QUOTE || c == SIMPLE_QUOTE)
			&& data->str[i + 1] == c && data->str[i - 1] != 32)
			rm_quotes(data, i);
		if ((c == DOUBLE_QUOTE || c == SIMPLE_QUOTE)
			&& data->str[i - 1] != 32 && data->str[i + 1] != 32)
			move_quotes(data, i);
	}
}
