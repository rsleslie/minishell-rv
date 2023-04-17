/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:42:57 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/17 14:54:49 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_builtins(char **data_str, t_node *env, t_node *export)
{
	if (ft_strncmp(data_str[0], "echo", ft_strlen(data_str[0])) == 0)
		ft_echo(data_str);
	if (ft_strncmp(data_str[0], "pwd", ft_strlen(data_str[0])) == 0)
		ft_pwd();
	if (ft_strncmp(data_str[0], "cd", ft_strlen(data_str[0])) == 0)
		ft_cd(data_str, env);
	else if (ft_strncmp(data_str[0], "env", ft_strlen(data_str[0])) == 0
		&& !data_str[1])
		print_env(env);
	else if (ft_strncmp(data_str[0], "export", ft_strlen(data_str[0])) == 0
		&& !data_str[1])
		print_export(export);
	else if (ft_strncmp(data_str[0], "export", ft_strlen(data_str[0])) == 0)
		arguments_export(data_str, env, export);
	else if (ft_strncmp(data_str[0], "unset", ft_strlen(data_str[0])) == 0
		&& !data_str[1])
		printf("unset: not enough arguments\n");
	else if (ft_strncmp(data_str[0], "unset", ft_strlen(data_str[0])) == 0)
		arguments_unset(data_str, env, export);
}
