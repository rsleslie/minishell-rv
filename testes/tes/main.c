#include "../../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_config    data;
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
			write(1, "exit", 4);
			write(1, "\n", 1);
			exit(1);
		}
		if (*data.str && check_space(&data) != 0)
		{
			ft_exit(&data, env, export);
			ft_lexer(&data);
			parser(&data);
		}
	}
	return (0);
}

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell 


// echo> << >> "    ranna" | $NAME| 

// echo < c.c > outfile bom dia