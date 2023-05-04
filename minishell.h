/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:57:27 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/04 11:36:06 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SIMPLE_QUOTE 39
# define DOUBLE_QUOTE 34

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

typedef struct s_config
{
	char	*str;
	char	**cmd;
	char	**paths;
	char	**tokens;
}	t_config;

typedef struct s_node
{
	char			*variable;
	char			*value;
	struct s_node	*next;
}	t_node;

typedef struct s_lexer
{
	int		i;
	int		j;
}	t_lexer;

// typedef struct s_lexer
// {
// }	t_lexer;

// check
void	ft_exit(t_config *data, t_node *env, t_node *export);
void	terminate(t_node *env, t_node *export, t_config *data, char *error_msg);

// utils
void	ft_free_tab(char **str);
void	ft_free_list(t_node *list);
void	ft_free_node(t_node *data);
void	arguments_unset(char **data_str, t_node *env, t_node *export);
void	arguments_export(char **data_str, t_node *env, t_node *export);
int		op_biultins(char *str);
int		counter_redirect(char *s);
void	is_null(char **str);

// linked list
t_node	*create_node(char *data);
t_node	*node_last(t_node *list);
void	link_node_end(t_node **list, t_node *node);
t_node	*create_node_null(char *data);
t_node	*create_node_quotes(char *data);

// handle
void	get_env(t_node **env, char **envp);
void	print_env(t_node *env);
char	**split_path(char *path);
void	handle_path(t_node **env, t_config *data);
int		cmd_exist(t_config *data, char *key);

//export
void	arguments_export(char **data_str, t_node *env, t_node *export);
void	arguments_unset(char **data_str, t_node *env, t_node *export);
void	parse_builtins(char **data_str, t_node *env, t_node *export, t_config *data);

//built-ins
void	ft_unset(t_node **list, char *key);
void	ft_export(t_node **env, char *key);
int		ft_key_parser(char *key);
void	ft_pwd(void);
void	ft_cd(char **data_str, t_node *env);
void	ft_echo(char **data_str);

//print e search foram add temporariamente
int		search_env(char *data, char *key);
void	get_export(t_node **export, char **envp);
void	print_export(t_node *export);

//token
int		op_redirect(char c);

// lexer
void	ft_lexer(t_config *data);

#endif