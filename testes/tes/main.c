#include "../../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_config    data;
	t_node		*env = NULL;
	t_node		*export = NULL;
	int			i;

	i = 0;
	argc = 0;
	data.tokens = NULL;
	(void)argv;  
	get_env(&env, envp);
	get_export(&export, envp);
	while (1)
	{
		data.str = readline("Habla$ ");
		add_history(data.str);
		ft_exit(&data, env, export);
		ft_lexer(&data);
		// handle_path(&env, &data);
		// parser(&data);
		i = 0;
		while(data.tokens[i])
			printf("%s\n", data.tokens[i++]);
		// parse_builtins(ft_split(data.str, 32), env, export, &data);
	}
	return (0);
}

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell 


// echo> << >> "    ranna" | $NAME| 