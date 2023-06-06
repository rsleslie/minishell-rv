/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:34:28 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/06 13:49:52 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**strjoin_tab(char **s1, char **s2)
{
	char	**str;
	size_t	i;
	int		x;

	i = 0;
	x = 0;
	if (!s1)
	{
		s1 = (char **)calloc(sizeof(char *), 1);
		s1 [0] = NULL;
	}
	str = (char **)calloc(sizeof(char **), (1 + ft_tab_len(s1)) + 1);
	if (str == NULL || !s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		str[i] = ft_strdup(s1[i]);
		i++;
	}
	while (x < 1)
		str[i++] = ft_strdup(s2[x++]);
	str[i] = NULL;
	if (s1)
		ft_free_tab(s1);
	return ((char **)str);
}

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
