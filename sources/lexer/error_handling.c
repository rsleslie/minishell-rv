/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:55:36 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/24 22:25:15 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	rm_quotes(t_config *data, int i)
{
	char	*ptr;
	int		j;

	j = -1;
	ptr = calloc(sizeof(char *), (ft_strlen(data->str) - 1));	
	while (++j < i)
		ptr[j] = data->str[j];
	i += 1;
	while (data->str[i])
		ptr[j++] = data->str[++i];
	ptr[j] = '\0';
	free(data->str);
	data->str = ft_strdup(ptr);
	free(ptr);
}

void	error_quotes(t_config *data)
{
	int		i;
	char	c;
	
	i = -1;
	while (data->str[++i])
	{
		c = data->str[i];
		if ((c == DOUBLE_QUOTE || c == SIMPLE_QUOTE)
			&& data->str[i + 1] == c && data->str[i - 1] != 32)
			rm_quotes(data, i);
		// if ((c == DOUBLE_QUOTE || c == SIMPLE_QUOTE)
		// 	&& data->str[i - 1] != 32)
		// 	move_quotes(data, i);
	}
}