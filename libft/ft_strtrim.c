/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 00:28:36 by coder             #+#    #+#             */
/*   Updated: 2023/01/23 16:02:21 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size_s1;
	char	*str;

	size_s1 = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size_s1 = ft_strlen(s1);
	while (size_s1 && ft_strchr(set, s1[size_s1]))
		size_s1--;
	str = ft_substr((char *)s1, 0, size_s1 + 1);
	return (str);
}
