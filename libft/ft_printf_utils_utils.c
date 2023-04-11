/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:41:50 by rleslie-          #+#    #+#             */
/*   Updated: 2023/01/27 18:48:05 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_hex(unsigned int n, int j, int x, int i)
{
	char	div[17];

	x = 0;
	if (n == 0)
	{
		div[x] = '0';
		x++;
	}
	while (n != 0)
	{
		i = n % 16;
		n = n / 16;
		if (i <= 9)
			div[x] = i + '0';
		else
			div[x] = i + '7' + j;
		x++;
	}
	div[x] = '\0';
	while (x != 0)
	{
		x--;
		ft_putchar(div[x]);
	}
	return (ft_strlen(div));
}

int	ft_ptr(unsigned long n, int j)
{
	char	div[32];
	int		i;
	int		x;

	x = 0;
	if (n == 0)
		return (write(1, "(nil)", 5));
	while (n != 0)
	{
		i = n % 16;
		n = n / 16;
		if (i <= 9)
			div[x] = i + '0';
		else
			div[x] = i + '7' + j;
		x++;
	}
	div[x] = '\0';
	ft_putchar_ptr(div, x);
	x = ft_strlen(div) + 2;
	return (x);
}

int	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
	{
		return (write(1, "(null)", 6));
		i = 6;
	}
	else
	{
		while (s[i] != '\0')
		{
			ft_putchar(s[i]);
			i++;
		}
	}
	return (i);
}
