/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:41:57 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/13 18:47:11 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_config	data;
	t_node		*env;
	t_node		*export;

	env = NULL;
	(void)argv;
	if (argc != 1)
		return (0);
	get_env(&env, envp);
	get_export(&export, envp);
	while (1)
	{
		data.str = readline("Habla$ ");
		add_history(data.str);
		ft_exit(&data, env, export);
		split_data_str(&data, env, export);
	}
}
