/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 23:48:07 by coder             #+#    #+#             */
/*   Updated: 2023/01/23 16:01:55 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	int		x;

	i = 0;
	x = 0;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char *));
		s1 [0] = '\0';
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s2) + ft_strlen(s1)) + 1);
	if (str == NULL || !s1 || !s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[x] != '\0')
		str[i++] = s2[x++];
	free(s1);
	str[i] = '\0';
	return ((char *)str);
}
