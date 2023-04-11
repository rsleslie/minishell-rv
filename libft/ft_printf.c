/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:31:59 by rleslie-          #+#    #+#             */
/*   Updated: 2023/01/23 16:01:30 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *ptr, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, ptr);
	while (ptr[i] != '\0')
	{
		if (ptr[i] == '%')
		{
			i++;
			len = ft_format(args, ptr[i], len);
		}
		else
		{
			write(1, &ptr[i], 1);
			len += 1;
		}
		i++;
	}
	va_end(args);
	return (len);
}
