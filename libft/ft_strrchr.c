/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:11:49 by coder             #+#    #+#             */
/*   Updated: 2023/01/23 16:02:16 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	if ((unsigned char)c == '\0')
		return ((void *)s + ft_strlen(s));
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((void *)s + i);
		i--;
	}
	return (NULL);
}
