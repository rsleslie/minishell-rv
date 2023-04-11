/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:53:24 by coder             #+#    #+#             */
/*   Updated: 2023/01/23 16:02:13 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{	
		if (big[i] == little[0])
		{
			if ((size + i) <= len)
				if (ft_strncmp(big + i, little, ft_strlen(little)) == 0)
					return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
