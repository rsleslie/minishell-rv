/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 01:26:37 by coder             #+#    #+#             */
/*   Updated: 2023/01/23 16:01:58 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{	
	size_t	orig;
	size_t	buffer;
	size_t	size_dst;

	orig = 0;
	buffer = ft_strlen(dst);
	size_dst = ft_strlen(dst);
	if (buffer >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (src[orig] && buffer < dstsize - 1)
	{
		dst[buffer] = src[orig];
		buffer++;
		orig++;
	}	
	dst[buffer] = '\0';
	return (ft_strlen(src) + size_dst);
}
