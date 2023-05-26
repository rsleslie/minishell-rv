/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:55:36 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/25 20:30:48 by rleslie-         ###   ########.fr       */
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
	i += 2;
	while (data->str[i])
		ptr[j++] = data->str[i++];
	ptr[j] = '\0';
	free(data->str);
	data->str = ft_strdup(ptr);
	free(ptr);
}

void	move(t_config *data, int j)
{
	char	c;
	int		i;
	char	*ptr;

	i = -1;
	c = data->str[j];
	ptr = calloc(sizeof(char *), ft_strlen(data->str) + 1);
	while (++i < j)
		ptr[i] = data->str[i];
	j++;
	while (data->str[j] != 32)
		ptr[i++] = data->str[j++];
	ptr[i++] = c;
	while (data->str[j])
		ptr[i++] = data->str[j++];
	ptr[i] = '\0';
	free(data->str);
	data->str = ft_strdup(ptr);
	free(ptr);
}

void	remov_quotes(t_config *data, int j)
{
	char	c;
	int		i;
	char	*ptr;

	i = -1;
	c = data->str[j];
	ptr = calloc(sizeof(char *), ft_strlen(data->str) - 1);
	while (++i < j)
		ptr[i] = data->str[i];
	j++;
	while (data->str[j] != c)
		ptr[i++] = data->str[j++];
	j++;
	while (data->str[j])
		ptr[i++] = data->str[j++];
	ptr[i] = '\0';
	free(data->str);
	data->str = ft_strdup(ptr);
	free(ptr);
}

void	move_quotes(t_config *data, int i)
{
	char	c;
	int		x;

	x = i + 1;
	c = data->str[i];
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
		if ((c == DOUBLE_QUOTE || c == SIMPLE_QUOTE)
			&& data->str[i - 1] != 32 && data->str[i + 1] != 32)
			move_quotes(data, i);
	}
}
