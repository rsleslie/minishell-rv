/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:59:29 by rleslie-          #+#    #+#             */
/*   Updated: 2023/01/27 18:45:19 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int n)
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

int	ft_format(va_list args, char format, int len)
{
	if (format == 'i' || format == 'd')
		len += ft_putnbr(va_arg(args, int));
	else if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	if (format == 'u')
		len += ft_putnbr_u(va_arg(args, int));
	else if (format == '%')
		len += (ft_putchar(format));
	if (format == 'x')
		len += ft_hex(va_arg(args, int), 32, 0, 0);
	if (format == 'X')
		len += ft_hex(va_arg(args, int), 0, 0, 0);
	if (format == 'p')
		len += ft_ptr(va_arg(args, unsigned long), 32);
	return (len);
}

void	ft_putchar_ptr(char *div, int x)
{
	ft_putchar('0');
	ft_putchar('x');
	while (x != 0)
	{
		x--;
		ft_putchar(div[x]);
	}
}

int	ft_putnbr_u(unsigned int n)
{
	int	x;

	x = 0;
	if (n >= 0 && n <= 9)
	{
		ft_putchar (n + '0');
		x++;
	}
	else
	{
		if (n > 9)
		{
			x += ft_putnbr(n / 10);
			n = n % 10;
		}
		x += ft_putchar(n + '0');
	}
	return (x);
}

int	ft_putnbr(int n)
{
	int	x;

	x = ft_size(n);
	if (n == -2147483648)
	{
		write(1, "-2", 2);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n >= 0 && n <= 9)
		ft_putchar (n + '0');
	else
	{
		if (n > 9)
		{
			ft_putnbr(n / 10);
			n = n % 10;
		}
		ft_putchar(n + '0');
	}
	return (x);
}
