/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:41:57 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 20:03:04 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_config	g_data;

void	minishell_loop(t_node *export, t_node *env,
	t_config *data, t_exec *exec)
{
	handle_path(&env, data);
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
		expansion(data, env);
		ft_lexer_tokens(&exec, data);
		dollar_sign(exec, env);
		unquotes(exec);
		empty_cmd_handle(exec);
		init_exec(exec, data, env, export);
	}
	reset_loop(export, env, data, exec);
}

int	reset_loop(t_node *export, t_node *env, t_config *data, t_exec *exec)
{
	if (exec != NULL)
	{
		free_exec_list(exec);
		exec = NULL;
	}
	free(data->str);
	ft_free_tab(data->paths);
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
	if (argc != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	(void)argv;
	g_data.tokens = NULL;
	g_data.status_code = 0;
	get_env(&env, envp);
	get_export(&export, envp);
	minishell_loop(export, env, &g_data, exec);
	return (0);
}
