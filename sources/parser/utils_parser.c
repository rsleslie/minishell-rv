/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:02:47 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/07 16:43:31 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parser(t_config *data)
{
	if (redirect_parser(data) == 1)
		return (1);
	if (redirect_parser(data) == 2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (1);
	}
	if (quotes_parser(data) == 1)
	{
		ft_putstr_fd("Minishell: Quotes error\n", 2);
		g_status_code = 1;
		return (1);
	}
	if (pipe_parser(data) == 1)
	{
		ft_putstr_fd("Mnishell: syntax error near unexpected token \n", 2);
		return (1);
	}
	return (0);
}

int	quotes_parser(t_config *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		if ((data->tokens[i][0] == SIMPLE_QUOTE
			|| data->tokens[i][0] == DOUBLE_QUOTE)
				&& ft_char_counter(data->tokens[i], data->tokens[i][0]) == 1)
			return (1);
		i++;
	}
	return (0);
}
