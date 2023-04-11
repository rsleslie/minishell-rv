/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:11:29 by coder             #+#    #+#             */
/*   Updated: 2023/01/23 16:01:19 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*orig;

	dest = (unsigned char *)dst;
	orig = (unsigned char *)src;
	while (n-- && (dest != 0 || orig != 0))
		*dest++ = *orig++;
	return (dst);
}
