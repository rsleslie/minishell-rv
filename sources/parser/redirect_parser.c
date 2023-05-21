/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverona- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:21:13 by rverona-          #+#    #+#             */
/*   Updated: 2023/05/20 21:21:16 by rverona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_iterator(t_config *data, int i)
{
	while (data->tokens[++i])
	{
		if (data->tokens[i][0] == '>' || data->tokens[i][0] == '<')
		{
			if (data->tokens[ft_tab_len(data->tokens) - 1][0] == '<'
				|| data->tokens[ft_tab_len(data->tokens) - 1][0] == '>')
				return (2);
			if (data->tokens[i + 1] && (data->tokens[i + 1][0] == '>'
				|| data->tokens[i + 1][0] == '<'
				|| data->tokens[i + 1][0] == '|'))
				return (2);
			if (data->tokens[i][0] == '<')
			{
				if (access(data->tokens[i + 1], F_OK) == -1)
				{
					printf("%s: No such file or directory\n",
						data->tokens[i + 1]);
					return (1);
				}
			}
		}
	}
	return (0);
}

int	redirect_parser(t_config *data)
{
	int	i;

	i = -1;
	if (redirect_iterator(data, i) == 1)
		return (1);
	else if (redirect_iterator(data, i) == 2)
		return (2);
	if (data->tokens[0][0] == '>' && ft_tab_len(data->tokens) == 2)
	{
		open(data->tokens[1], O_CREAT, 0644);
		return (1);
	}
	return (0);
}
