/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:41:57 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/13 20:19:02 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_config	g_data;

int	minishell_loop(t_node *export, t_node *env, t_config *data, t_exec *exec)
{
	init_signals();
	data->str = readline("Habla$ ");
	if (data->str == NULL)
	{
		data->status_code = 0;
		free_exec_list(exec);
		terminate(env, export, data);
	}
	if (*data->str && check_space(data) != 0)
	{
		add_history(data->str);
		if (error_quotes(data) == 1)
			reset_loop(export, env, data, exec);
		ft_lexer(data);
		if (parser(data) == 1)
			reset_loop(export, env, data, exec);
		expantion(data, env);
		ft_lexer_tokens(&exec, data);
		dollar_sign(exec, env);
		unquotes(exec);
		init_exec(exec, data, env, export);
	}
	reset_loop(export, env, data, exec);
	return (0);
}

int	reset_loop(t_node *export, t_node *env, t_config *data, t_exec *exec)
{
	if (exec != NULL)
	{
		free_exec_list(exec);
		exec = NULL;
	}
	free(data->str);
	minishell_loop(export, env, data, exec);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec		*exec;
	t_node		*env;
	t_node		*export;

	exec = NULL;
	env = NULL;
	export = NULL;
	(void)argc;
	(void)argv;
	g_data.tokens = NULL;
	g_data.status_code = 0;
	get_env(&env, envp);
	get_export(&export, envp);
	handle_path(&env, &g_data);
	minishell_loop(export, env, &g_data, exec);
	return (0);
}

// echo kk > ola | echo 8787 > ola
// expandir sem aspas
// variavel q nao existe = \n 
