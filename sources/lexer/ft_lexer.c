/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:35:40 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/03 16:09:02 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	split_lexer(char *ptr, t_config *data, int i, int j)
{
	int		c;

	free(data->str);
	data->str = (char *)malloc(sizeof(char) * (ft_strlen(ptr) + 1));
	while (ptr[i])
	{
		if (ptr[i] == '*' || ptr[i] == 32)
		{
			data->str[j++] = ptr[i++];
			while (ptr[i] == '*' || ptr[i] == 32)
				i++;
		}
		if (ptr[i] == 34 || ptr[i] == 39)
		{
			c = ptr[i];
			data->str[j++] = ptr[i++];
			while (ptr[i] && ptr[i] != c)
				data->str[j++] = ptr[i++];
		}
		data->str[j++] = ptr[i++];
	}
	data->str[j] = '\0';
	printf("%s\n", data->str);
	data->tokens = ft_split(data->str, '*');
	free(ptr);
}

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

void	aux_lexer(char *ptr, t_config *data, t_lexer *counter)
{
	while (data->str[counter->i])
	{
		aux_aux_lexer(ptr, data, counter);
		if (op_redirect(data->str[counter->i]) != 0
			&& op_redirect(data->str[counter->i]) != 4)
		{
			ptr[counter->j++] = '*';
			if ((op_redirect(data->str[counter->i]) != 0)
				&& (ft_strcmp(data->str[counter->i], data->str[counter->i + 1])
					== 0))
				ptr[counter->j++] = data->str[counter->i++];
			ptr[counter->j++] = data->str[counter->i++];
			ptr[counter->j++] = '*';
		}
		if (data->str[counter->i] == 32 || data->str[counter->i] == 9)
		{
			ptr[counter->j++] = '*';
			while (data->str[counter->i] != 32 && data->str[counter->i] != 9)
				counter->i++;
		}
		ptr[counter->j] = data->str[counter->i];
		counter->j++;
		counter->i++;
	}
	while (ptr[counter->j] != '\0')
		ptr[counter->j++] = '\0';
	split_lexer(ptr, data, 0, 0);
}

void	ft_lexer(t_config *data)
{
	t_lexer	counter;
	char	*ptr;

	counter.i = 0;
	counter.j = 0;
	ptr = (char *)malloc(sizeof(char)
			* (ft_strlen(data->str) + counter_redirect(data->str) + 1));
	ptr[ft_strlen(data->str) + counter_redirect(data->str)] = '\0';
	aux_lexer(ptr, data, &counter);
}
