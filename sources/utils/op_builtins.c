/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_biultins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:16:44 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/25 15:22:34 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	op_biultin(char *str)
{
	if (ft_strncmp(&str[0], "echo", ft_strlen(&str[0])) == 0)
		return (1);
	if (ft_strncmp(&str[0], "pwd", ft_strlen(&str[0])) == 0)
		return (2);
	if (ft_strncmp(&str[0], "cd", ft_strlen(&str[0])) == 0)
		return (3);
	else if (ft_strncmp(&str[0], "env", ft_strlen(&str[0])) == 0
		&& !str[1])
		return (4);
	else if (ft_strncmp(&str[0], "export", ft_strlen(&str[0])) == 0
		&& !str[1])
		return (5);
	else if (ft_strncmp(&str[0], "export", ft_strlen(&str[0])) == 0)
		return (6);
	else if (ft_strncmp(&str[0], "unset", ft_strlen(&str[0])) == 0
		&& !str[1])
		return (7);
	else if (ft_strncmp(&str[0], "unset", ft_strlen(&str[0])) == 0)
		return (8);
	return (0);
}
