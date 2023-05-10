#include "../../minishell.h"

void	handle_sigint(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signals(void)
{
	struct sigaction sigact;
	sigset_t set;

	sigact = (struct sigaction){0};
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = handle_sigint;
	sigaction(SIGINT, &sigact, NULL);
	sigemptyset(&sigact.sa_mask);
	sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    sigprocmask(SIG_BLOCK, &set, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
}

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
			write(1, "\n", 1);
			exit(1);
		}
		if (*data.str && check_space(&data) != 0)
		{
			ft_exit(&data, env, export);
			ft_lexer(&data);
			parser(&data);
		}

		// i = 0;
		// while(data.tokens[i])
		// 	printf("%s\n", data.tokens[i++]);
		// parse_builtins(ft_split(data.str, 32), env, export, &data);
	}
	return (0);
}

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell 


// echo> << >> "    ranna" | $NAME| 

// echo < c.c > outfile bom dia