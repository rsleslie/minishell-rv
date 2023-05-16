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
		if (data.str == NULL)
		{
			printf("readline");//olha aaaaaqui tem que tirar
			free_exec_list(exec);
			terminate(env, export, &data, "exit\n");
		}
		if (*data.str && check_space(&data) != 0)
		{
			add_history(data.str);
			ft_exit(&data, env, export, exec);
			ft_lexer(&data);
			if (parser(&data) == 1)
				continue ;
			free_exec_list(exec);
			exec = NULL;
			ft_lexer_tokens(&exec, &data);
			dollar_sign(exec, env);
			init_exec(exec, &data, env, export);
		}
		
		/*
		export não adiciona variavel na env somente na export
		limpar prompt do ctrl+C
		arruamr o exit
		avaliador pode embaçar errno
		expansao $
		tirar aspas

		*/


		// i = 0;
		// while(data.tokens[i])
		// 	printf("%s,", data.tokens[i++]);
		// printf("\n");
		// i = 0;
		// while(data.tokens[i])
		// 	printf("%s,", data.tokens[i++]);
		
		// printf("\nredirect:   ->\n\n");

		// i = 0;
		// while(exec->redirect[i])
		// 	printf("%s\n", exec->redirect[i++]);
		// printf("\ncmd\n");
		// while(exec != NULL)
		// {
		// 	i = 0;
		// 	while(exec->cmd[i])
		// 		printf("%s,", exec->cmd[i++]);
		// 	printf("\nproximo\n");
		// 	exec = exec->next;
		// }
		
		// lexer_tokens(&exec, &data);
		// i = 0;
		// printf("cmd: \n");
		// while(data.tokens[i])
		// 	printf("%s\n", data.tokens[i++]);
	}
	
	
	return (0);
}

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell 


// echo> << >> "    ranna" | $NAME| 

// echo < c.c > outfile bom dia