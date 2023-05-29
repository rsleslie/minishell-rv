#include "../../minishell.h"

int g_status_code;

int	minishell_loop(t_node *export, t_node *env, t_config *data, t_exec *exec)
{
	data->str = readline("Habla$ ");
	if (data->str == NULL)
	{
		free_exec_list(exec);
		terminate(env, export, data, "exit");
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
	int			i;

	i = 0;
	argc = 0;
	g_status_code = 0;
	data.tokens = NULL;
	(void)argv;  
	get_env(&env, envp);
	get_export(&export, envp);
	handle_path(&env, &data);
	minishell_loop(export, env, &data, exec);
	// while (1)
	// {
	// 	data.str = readline("Habla$ ");
	// 	if (data.str == NULL)
	// 	{
	// 		free_exec_list(exec);
	// 		terminate(env, export, &data, "exit");
	// 	}
	// 	if (*data.str && check_space(&data) != 0)
	// 	{
	// 		add_history(data.str);
	// 		if (ft_exit(&data, env, export, exec) == 1)
	// 			continue ;
	// 		error_quotes(&data);
	// 		ft_lexer(&data);
	// 		if (parser(&data) == 1)
	// 			continue ;
	// 		expantion(&data, env);
	// 		ft_lexer_tokens(&exec, &data);
	// 		dollar_sign(exec, env);
	// 		unquotes(exec);
	// 		init_exec(exec, &data, env, export);
	// 	}

		// 

		// while (exec != NULL)
		// {
		// 	i = -1;
		// 	while (exec->cmd[++i])
		// 		printf("%s,", exec->cmd[i]);
		// 	i = -1;
		// 	printf("\n");
		// 	while (exec->redirect[++i])
		// 		printf("%s,", exec->redirect[i]);

		// 	printf("\n\nproximo->\n\n");
		// 	exec = exec->next;
		// }

		// if (exec != NULL)
		// {
		// 	free_exec_list(exec);
		// 	exec = NULL;
		// }
		// free(data.str);
		/*

		export não adiciona variavel na env somente na export
		arruamr o exit
		avaliador pode embaçar errno
		expansao $
		tirar aspas
		
		*/
//	}
	return (0);
}

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell 


// echo> << >> "    ranna" | $NAME| 

// echo < c.c > outfile bom dia