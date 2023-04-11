/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 21:17:24 by coder             #+#    #+#             */
/*   Updated: 2023/01/29 12:24:29 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start > ft_strlen(s))
	{
		len = 0;
		start = ft_strlen(s);
	}
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(sizeof(char ) * len + 1);
	if (!ptr || !s)
		return (NULL);
	else
	{
		while (s[start] != '\0' && i < len)
			ptr[i++] = s[start++];
	}
	ptr[i] = '\0';
	return (ptr);
}
