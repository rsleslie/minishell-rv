/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 03:10:29 by coder             #+#    #+#             */
/*   Updated: 2023/04/06 18:50:08 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_split_counter(char const *s, char c)
{
	size_t			i;
	int				counter;

	i = 0;
	counter = 0;
	if (ft_strlen(s) == 0)
		return (0);
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			counter++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		counter++;
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	size_t			i;
	size_t			start;
	int				counter;
	char			**tab;

	i = 0;
	start = 0;
	tab = (char **)malloc((ft_split_counter((char *)s, c) + 1) \
	* sizeof(char *));
	counter = 0;
	if (tab == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			tab[counter++] = ft_substr(s, start, (i - start));
		}
		else
			i++;
	}
	return (tab[counter] = NULL, tab);
}
