/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:19:01 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/12 15:11:55 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*search_expansion(char *data, t_node *list, char *key, int j)
{
	t_node	*aux;

	aux = list;
	while (aux != NULL)
	{
		if (search_env(key, aux->variable) == 0)
			return (ft_strdup(aux->value));
		aux = aux->next;
	}
	if (data[j] == '$' && data[j + 1] == '?')
		return (ft_itoa(g_data.status_code));
	if (data[j] == '$' && (data[j + 1] == 32
			|| data[j + 1] == DOUBLE_QUOTE || data[j + 1] == SIMPLE_QUOTE))
		return (ft_strdup("$"));
	return (ft_strdup(" "));
}

char	*get_key(char *ptr, int j)
{
	int		i;
	char	*key;

	i = 0;
	while (ptr[j + 1] && ptr[j] != 32)
	{
		i++;
		j++;
	}
	key = calloc(sizeof(char *), i + 1);
	j -= i;
	i = -1;
	while (ptr[j + 1] && ptr[j] != 32)
		key[++i] = ptr[j++];
	key[++i] = '\0';
	return (key);
}

char	*refresh_value(char *s1, char *s2, int j, int size)
{
	int		i;
	int		x;
	char	*dst;

	i = -1;
	x = 0;
	dst = calloc(sizeof(char *), (ft_strlen(s1)+ ft_strlen(s2) + 1) - size);
	while (++i < j)
		dst[i] = s1[i];
	while (s2[x])
		dst[i++] = s2[x++];
	j += (size + 1);
	while (s1[j])
		dst[i++] = s1[j++];
	dst[i] = '\0';
	if (s2)
		free(s2);
	return (dst);
}

void	norm_expantion(int i, int j, t_config *data, t_node *env)
{
	char	*value;
	char	*key;

	if (data->tokens[i][j] == '$' && data->tokens[i][j + 1])
	{
		key = get_key(data->tokens[i], j + 1);
		value = search_expansion(data->tokens[i], env, key, j);
		value = refresh_value(data->tokens[i], value, j,
				ft_strlen(key));
		free(data->tokens[i]);
		data->tokens[i] = ft_strdup(value);
		free(value);
		free(key);
	}
}

void	expantion(t_config *data, t_node *env)
{
	int		i;
	int		j;

	i = -1;
	while (data->tokens[++i])
	{
		if (data->tokens[i][0] == DOUBLE_QUOTE)
		{
			j = -1;
			while (data->tokens[i][++j])
			{
				norm_expantion(i, j, data, env);
			}
		}
	}
}
