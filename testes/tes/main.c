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
			ft_free_exec(exec);
			terminate(env, export, &data, "exit\n");
		}
		if (*data.str && check_space(&data) != 0)
		{
			ft_exit(&data, env, export);
			ft_lexer(&data);
			parser(&data);
		}


		// i = 0;
		// while(data.tokens[i])
		// 	printf("%s,", data.tokens[i++]);
		ft_free_exec(exec);
		exec = NULL;
		ft_lexer_tokens(&exec, &data);
		// printf("\n");
		// i = 0;
		// while(data.tokens[i])
		// 	printf("%s,", data.tokens[i++]);
		
		// printf("\nteste:   ->\n\n");

		// i = 0;
		// while(data.tokens[i])
		// 	printf("%s\n", data.tokens[i++]);
		
		
		
		// // lexer_tokens(&exec, &data);
		// i = 0;
		// printf("cmd: \n");
		// while(exec.cmd[i])
		// 	printf("%s\n", exec.cmd[i++]);
	}
	
	
	return (0);
}

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell 


// echo> << >> "    ranna" | $NAME| 

// echo < c.c > outfile bom dia