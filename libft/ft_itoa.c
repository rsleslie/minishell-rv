/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 00:41:25 by coder             #+#    #+#             */
/*   Updated: 2023/01/23 16:01:11 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_size(int n)
{
	int	x;
	int	i;

	i = n;
	x = 0;
	if (n <= 0)
		x = 1;
	if (n < 0)
		n *= -1;
	while (i != 0)
	{
		i = i / 10;
		x++;
	}
	return (x);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		x;
	int		j;

	x = ft_size(n);
	j = n;
	if (n < 0)
		n *= -1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * x + 1);
	i = x - 1;
	while (i >= 0)
	{
		str[i--] = (n % 10) + '0';
		n = n / 10;
	}
	str[x] = '\0';
	if (j < 0)
		str[0] = '-';
	return ((char *)str);
}
