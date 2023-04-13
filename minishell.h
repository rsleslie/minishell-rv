/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:57:27 by rleslie-          #+#    #+#             */
/*   Updated: 2023/04/12 17:46:49 by rleslie-         ###   ########.fr       */
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

typedef struct s_config
{
	char	*str;
	char	**str_command;
	char	**paths;
}	t_config;

typedef struct s_node
{
	char			*variable;
	char			*value;
	struct s_node	*next;
}	t_node;

// check
void	ft_exit(t_config *data, t_node *env, t_node *export);

// utils
void	ft_free_tab(char **str);
void	ft_free_list(t_node *list);
void	ft_free_node(t_node *data);

// linked list
t_node	*create_node(char *data);
t_node	*node_last(t_node *list);
void	link_node_end(t_node **list, t_node *node);
t_node	*create_node_null(char *data);
t_node	*create_node_quotes(char *data);

// handle
void	get_env(t_node **env, char **envp);
void	print_env(t_node *env);

//export test
void	parse_data_str(char **split_data_str, t_node *env, t_node *export);

//built-ins
void	ft_unset(t_node **list, char *key);
void	ft_export(t_node **env, char *key);
int		ft_key_parser(char *key);
// void	ft_add_export(t_node **list, t_node *node);

//print e search foram add temporariamente
int		search_env(char *data, char *key);
void	get_export(t_node **export, char **envp);
void	print_export(t_node *export);

#endif