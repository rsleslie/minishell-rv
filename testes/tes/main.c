#include "../../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_config    data;
	t_exec		*exec = NULL;
	t_node		*env = NULL;
	t_node		*export = NULL;
	int			i;

	i = 0;
	argc = 0;
	init_signals();
	data.tokens = NULL;
	(void)argv;  
	get_env(&env, envp);
	get_export(&export, envp);
	handle_path(&env, &data);
	while (1)
	{
		data.str = readline("Habla$ ");
		add_history(data.str);
		if (data.str == NULL)
		{
			freeLinkedList(exec);
			terminate(env, export, &data, "exit\n");
		}
		if (*data.str && check_space(&data) != 0)
		{
			ft_exit(&data, env, export, exec);
			ft_lexer(&data);
			parser(&data);
			ft_free_exec(exec);
			exec = NULL;
			ft_lexer_tokens(&exec, &data);
		}
	}
	
	
	return (0);
}

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell 
