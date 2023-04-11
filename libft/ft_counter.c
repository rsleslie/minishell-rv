/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_counter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:59:11 by rleslie-          #+#    #+#             */
/*   Updated: 2023/01/24 20:26:12 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_counter(char const *s, char c)
{
	size_t			i;
	int				counter;

	i = 0;
	counter = 0;
	if (ft_strlen(s) == 0)
		return (0);
	while (s[i] == c)
		i++;
	while (s[i] != '\n')
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
