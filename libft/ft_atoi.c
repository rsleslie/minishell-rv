/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:53:39 by coder             #+#    #+#             */
/*   Updated: 2023/04/11 14:33:33 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	signal;
	int	result;
	int	aux;
	int	i;

	i = 0;
	result = 0;
	signal = 1;
	aux = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = signal * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		aux = result + (str[i] - '0');
		result = aux * 10;
		i++;
	}
	return (aux * signal);
}
