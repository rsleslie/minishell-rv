/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 21:09:36 by coder             #+#    #+#             */
/*   Updated: 2023/01/23 16:00:52 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*ptr;

	if (nitems == 0 || size == 0 || size > SIZE_MAX / nitems)
		return (NULL);
	ptr = (char *)malloc(nitems * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, nitems * size);
	return (ptr);
}
