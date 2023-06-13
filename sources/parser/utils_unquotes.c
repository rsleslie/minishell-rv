/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:51:42 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/13 11:52:00 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_key_heredoc(char *ptr, int j)
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
	while (ptr[j] && ptr[j] != 32)
		key[++i] = ptr[j++];
	key[++i] = '\0';
	return (key);
}

char	*norm_expantion_heredoc(int j, char *ptr, t_node *env)
{
	char	*value;
	char	*key;

	value = NULL;
	if (ptr[j] == '$' && ptr[j + 1])
	{
		key = get_key_heredoc(ptr, j + 1);
		value = search_expansion(ptr, env, key, j);
		value = refresh_value(ptr, value, j,
				ft_strlen(key));
		free(ptr);
		ptr = ft_strdup(value);
		free(key);
		free(value);
		return (ptr);
	}
	return (ptr);
}

char	*expantion_heredoc(char *ptr, t_node *env)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_strdup(ptr);
	while (new[i] != '\0')
	{
		new = norm_expantion_heredoc(i, new, env);
		i++;
	}
	return (new);
}
