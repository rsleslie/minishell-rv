/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:18:19 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/13 17:18:58 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_key_parser(char *key)
{
	char	**split_key;

	if (ft_lurkstr(key, '=') == 0)
	{
		split_key = ft_split(key, '=');
		if (split_key[1] == NULL)
			return (0);
		else
			return (1);
	}
	return (2);
}
