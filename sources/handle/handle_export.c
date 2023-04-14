/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:38:54 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/14 16:20:13 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	arguments_export(char **data_str, t_node *env, t_node *export)
{
	int	i;

	i = 1;
	while (data_str[i])
	{
		if (ft_lurkstr(data_str[i], '=') == 1)
			ft_export(&export, data_str[i]);
		else
		{
			ft_export(&export, data_str[i]);
			ft_export(&env, data_str[i]);
		}
		i++;
	}
}

void	arguments_unset(char **data_str, t_node *env, t_node *export)
{
	int	i;

	i = 1;
	while (data_str[i])
	{
		ft_unset(&export, data_str[i]);
		ft_unset(&env, data_str[i]);
		i++;
	}
}

void	parse_unset_export(char **data_str, t_node *env, t_node *export)
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

void	split_data_str(t_config *data, t_node *env, t_node *export)
{
	char	**split_data_str;
	int		i;

	i = 0;
	split_data_str = ft_split(data->str, 32);
	while (split_data_str[i])
		i++;
	parse_unset_export(split_data_str, env, export);
	ft_free_tab(split_data_str);
}
