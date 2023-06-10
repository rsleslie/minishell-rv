#include "../../minishell.h"

// colocar o fd do pipe na data
int g_status_code;

int	minishell_loop(t_node *export, t_node *env, t_config *data, t_exec *exec)
{
	init_signals();
	data->str = readline("Habla$ ");
	// remove_empty(data);
	if (data->str == NULL)
	{
		// printf("fudeu\n");
		g_status_code = 139;
		free_exec_list(exec);
		terminate(env, export, data);
	}
	if (*data->str && check_space(data) != 0)
	{
		add_history(data->str);
		if (ft_exit(data, env, export, exec) == 1)
			reset_loop(export, env, data, exec);
		error_quotes(data);
		ft_lexer(data);
		if (parser(data) == 1)
			reset_loop(export, env, data, exec);
		expantion(data, env);
		ft_lexer_tokens(&exec, data);
		dollar_sign(exec, env);
		g_status_code = 0;
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
	t_config    data;
	t_exec		*exec = NULL;
	t_node		*env = NULL;
	t_node		*export = NULL;
	
	argc = 0;
	(void)argc;
	g_status_code = 0;
	data.tokens = NULL;
	(void)argv;
	init_signals();  
	get_env(&env, envp);
	get_export(&export, envp);
	handle_path(&env, &data);
	minishell_loop(export, env, &data, exec);
	return (0);
}

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell 

// valgrind -q --leak-check=full --show-leak-kinds=all --trace-children=yes --suppressions=readline.supp --track-fds=yes --track-origins=yes --trace-children-skip='/bin/,/sbin/' ./minishell