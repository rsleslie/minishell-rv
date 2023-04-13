#include "../../minishell.h"

void    parse_unset(char **input)
{
    int i;

    i = 0;
    while (input[i])
    {
        i++;
    }
    
}

void parse_temporario(t_config *data, t_node *env, t_node *export)
{
    char    **input_term;
    int     i;

    i = 1;
    input_term = ft_split(data->str, ' ');
    if (ft_strncmp(input_term[0], "env", ft_strlen(input_term[0])) == 0 && !input_term[1])
        print_env(env);
    else if (ft_strncmp(input_term[0], "export", ft_strlen(input_term[0])) == 0 && !input_term[1])
        print_export(export);
    else if (ft_strncmp(input_term[0], "export", ft_strlen(input_term[0])) == 0)
    {
        ft_export(&export, input_term[i]);
    } 
    else if (ft_strncmp(input_term[0], "unset", ft_strlen(input_term[0])) == 0 && !input_term[1])
        printf("unset: not enough arguments\n");
    else if (ft_strncmp(input_term[0], "unset", ft_strlen(input_term[0])) == 0)
    {
        ft_unset(&export, input_term[1]);
        ft_unset(&env, input_term[1]);
    }
    ft_free_tab(input_term);
}

int	main(int argc, char **argv, char **envp)
{
    t_config    data;
	t_node	*env = NULL;
    t_node	*export = NULL;

    argc = 0;
    (void)argv;  

    get_env(&env, envp);
    get_export(&export, envp);
    while (1)
	{
		data.str = readline("Habla$ ");
		add_history(data.str);
        parse_temporario(&data, env, export);
		ft_exit(&data, env, export);	
	}
    // lembrar de jogar o env e o export no exit
	ft_free_list(env);
    ft_free_list(export);
}

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell 