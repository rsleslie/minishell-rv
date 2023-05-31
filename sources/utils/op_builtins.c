/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:16:44 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/30 21:13:35 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	op_builtins(char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		return (1);
	if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		return (1);
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0
		&& !str[1])
		return (1);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
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
