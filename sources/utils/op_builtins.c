/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:16:44 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/25 21:06:09 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	op_builtins(char *str)
{
	if (ft_strncmp(&str[0], "echo", ft_strlen(&str[0])) == 0)
		return (1);
	if (ft_strncmp(&str[0], "pwd", ft_strlen(&str[0])) == 0)
		return (1);
	if (ft_strncmp(&str[0], "cd", ft_strlen(&str[0])) == 0)
		return (1);
	else if (ft_strncmp(&str[0], "env", ft_strlen(&str[0])) == 0)
		return (1);
	else if (ft_strncmp(&str[0], "export", ft_strlen(&str[0])) == 0)
		return (1);
	else if (ft_strncmp(&str[0], "unset", ft_strlen(&str[0])) == 0
		&& !str[1])
		return (1);
	else if (ft_strncmp(&str[0], "unset", ft_strlen(&str[0])) == 0)
		return (1);
	return (0);
}

void	is_null(char **fd)
{
	if (fd == NULL || *fd == NULL)
		return ;
	if (fd && *fd)
		ft_free_tab(fd);
}
