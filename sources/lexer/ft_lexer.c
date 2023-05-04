/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:35:40 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/04 11:36:24 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	aux_aux_lexer(char *ptr, t_config *data, t_lexer *counter)
{
	char	c;

	if (data->str[counter->i] == 34 || data->str[counter->i] == 39)
	{
		c = data->str[counter->i];
		ptr[counter->j++] = '*';
		ptr[counter->j++] = data->str[counter->i++];
		while (data->str[counter->i] && data->str[counter->i] != c)
			ptr[counter->j++] = data->str[counter->i++];
	}
}

void	aux_lexer(char *ptr, t_config *data, t_lexer *counter, int size)
{
	char	c;
	
	while (data->str[counter->i] && counter->j <= size)
	{
		aux_aux_lexer(ptr, data, counter);
		if ((op_redirect(data->str[counter->i]) != 0 && op_redirect(data->str[counter->i]) != 4 ))
		{
			c = data->str[counter->i];
			counter->i++;
			ptr[counter->j] = '*';
			counter->j++;
			ptr[counter->j] = c;
			counter->j++;
			if (data->str[counter->i] == c )
			{
				ptr[counter->j] = data->str[counter->i];
				counter->j++;
				counter->i++;
				if (counter->j > size)
				break;
			}
			ptr[counter->j] = '*';
			counter->j++;
		}
		else if (data->str[counter->i] == 32 || data->str[counter->i] == 9)
		{
			ptr[counter->j] = '*';
			counter->j++;
			counter->i++;
		}
		else
		{
			ptr[counter->j] = data->str[counter->i];
			counter->j++;
			counter->i++;
		}
	}
	is_null(data->tokens);
	data->tokens = ft_split(ptr, '*');
	free(ptr);
}

void	ft_lexer(t_config *data)
{
	t_lexer	counter;
	char	*ptr;
	int		size;
	
	size = ft_strlen(data->str) + (counter_redirect(data->str)* 2);
	counter.i = 0;
	counter.j = 0;
	ptr = calloc(sizeof(char), size + 2);
	ptr[size] = '\0';
	aux_lexer(ptr, data, &counter, size);
}

