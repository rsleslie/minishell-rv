#include "../../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_config    data;
	t_node		*env;
	t_node		*export;

	env = NULL;
	export = NULL;
	argc = 0;
	(void)argv;  
	get_env(&env, envp);
	get_export(&export, envp);
	while (1)
	{
		data.str = readline("Habla$ ");
		add_history(data.str);
		ft_exit(&data, env, export);
		ft_lexer(&data, env, export);	
	}
	return (0);
}

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell 