/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:16:58 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/25 21:26:35 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	op_redirect(char c)
{
	if (ft_strcmp(c, '<') == 0)
		return (1);
	else if (ft_strcmp(c, '>') == 0)
		return (2);
	else if (ft_strcmp(c, '|') == 0)
		return (3);
	else if (ft_strcmp(c, '$') == 0)
		return (4);
	return (0);
}

int	ft_len_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$')
		i++;
	return (i);
}
