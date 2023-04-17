/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:35:40 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/17 14:44:17 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lexer(t_config *data, t_node *env, t_node *export)
{
	char	**split_data_str;
	int		i;

	i = 0;
	split_data_str = ft_split(data->str, 32);
	while (split_data_str[i])
		i++;
	parse_builtins(split_data_str, env, export);
	ft_free_tab(split_data_str);
}
