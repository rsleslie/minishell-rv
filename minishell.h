/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:57:27 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 20:03:21 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SIMPLE_QUOTE 39
# define DOUBLE_QUOTE 34

# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

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
	int		builtins;
	int		index;
}	t_lexer;

typedef struct s_exec {
	int				**fd;
	char			**cmd;
	char			**redirect;
	int				is_builtin;
	int				index;
	int				fd_input;
	int				fd_output;
	struct s_exec	*next;
}	t_exec;

typedef struct s_config
{
	char			*str;
	char			**paths;
	char			**tokens;
	int				fd;
	int				bkp;
	int				status;
	int				i;
	int				**fd_pipe;
	long long		status_code;
	t_exec			*node_exec;
	t_node			*node_env;
	t_node			*node_export;
	pid_t			pid;
	pid_t			*pid_array;
}	t_config;

//main
extern t_config	g_data;

int		reset_loop(t_node *export, t_node *env, t_config *data, t_exec *exec);

// free

void	free_var(t_node *env, t_node *export, t_config *data, t_exec *exec);

// check

int		ft_exit(t_config *data);
void	terminate(t_node *env, t_node *export, t_config *data);
int		check_space(t_config *data);
int		ft_init_exit(t_config *data, char **split_exit);
void	trim_quotes(char **split_exit);
int		exit_norm(char **split_exit, t_exec *exec);
void	norminette_exit(char **s, t_config *data, t_node *env, t_node *export);

// utils
void	free_exec_list(t_exec *head);
void	ft_free_tab(char **str);
void	ft_free_list(t_node *list);
void	ft_free_node(t_node *data);
void	arguments_unset(char **data_str, t_node *env, t_node *export);
int		op_builtins(char *str);
int		counter_redirect(char *s);
void	is_null(char **str);
int		ft_char_counter(char *s, char c);
char	*strdup_empty(char *dst, char *exec);
char	*search_var_quotes(t_node *list, char *exec, char *key);
void	dollar_quotes(t_node *env, t_exec *exec, int size);
char	*remove_quotes(char *str);
int		ft_len_dollar(char *str);
char	*strdup_quotes(char *dst, char *exec, char *value);
void	ft_free_tab_int(int **str, int size);
int		parse_export(t_node **list, char *key);
int		error_equal(char *key);
void	is_null(char **fd);

// linked list
t_node	*create_node(char *data);
t_node	*node_last(t_node *list);
void	link_node_end(t_node **list, t_node *node);
t_node	*create_node_null(char *data);
t_node	*create_node_quotes(char *data);

//linked list exec

t_exec	*create_node_exec(char **str_cmd, char **str_redirect, t_lexer *exec);
t_exec	*exec_node_last(t_exec *list);
void	exec_link_node_end(t_exec **list, t_exec *node);

// handle
void	get_env(t_node **env, char **envp);
void	print_env(t_node *env);
char	**split_path(char *path);
void	handle_path(t_node **env, t_config *data);
int		cmd_exist(t_config *data, char *key);
void	remov_quotes(t_config *data, int j);
void	move(t_config *data, int j);
void	rm_quotes(t_config *data, int i);

//export
void	arguments_export(char **data_str, t_node *env, t_node *export);
void	arguments_unset(char **data_str, t_node *env, t_node *export);
void	parse_builtins(char **data_str, t_node *env,
			t_node *export, t_config *data);

//built-ins
void	ft_unset(t_node **list, char *key);
void	ft_export(t_node **env, char *key);
int		ft_key_parser(char *key);
void	ft_pwd(void);
void	ft_cd(char **data_str, t_node *env);
void	ft_echo(char **data_str);
void	exec_builtins(t_exec *exec, t_node *env,
			t_node *export, t_config *data);

//print e search foram add temporariamente
int		search_env(char *data, char *key);
void	get_export(t_node **export, char **envp);
void	print_export(t_node *export);

//token
int		op_redirect(char c);

// lexer
void	ft_lexer(t_config *data);
void	lexer_tokens(t_exec **exec, t_config *data);
char	**strjoin_tab(char **s1, char **s2);

// parsa
int		parser(t_config *data);
int		quotes_parser(t_config *data);
int		error_quotes(t_config *data);
int		pipe_parser(t_config *data);
int		redirect_parser(t_config *data);
int		builtin_parser(t_config *data, char *s);
int		executables_parser(t_config *data, char *s);
void	unquotes(t_exec *exec);
void	dollar_sign(t_exec *exec, t_node *env);
char	*dollar_refesh(char *cmd);
void	status_code(t_exec *exec, int i);
char	*search_var(t_node *list, char *exec, char *key);
char	*refresh_value(char *s1, char *s2, int j, int size);
char	*get_key(char *ptr, int j);
char	*search_expansion(char *data, t_node *list, char *key, int j);

//signal

void	handle_sigint(int signal, siginfo_t *info, void *context);
void	init_signals(void);
void	handle_heredoc_sigint(int signal);
void	signal_handler_child_heredoc(void);
void	signal_handler_child(void);
void	handler_child(int signal);
void	broken_pipe(int signal);

//teste
char	**strdup_tab(char **tab, int start, int end);
void	ft_lexer_tokens(t_exec **exec, t_config *data);
void	expansion(t_config *data, t_node *env);

// executor

void	pipex(t_exec *exec, int **fd, int i, t_config *data);
int		pipe_counter(char **tokens);
void	pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export);
void	init_exec(t_exec *exec, t_config *data, t_node *env, t_node *export);
int		cmd_acess(char *str);
int		output_redirection(t_config *data, t_exec *exec,
			t_node *env, t_node *export);
int		input_redirection(t_config *data, t_exec *exec,
			t_node *env, t_node *export);
char	*exec_path(t_config *data, t_exec *exec);
void	norm_executor_redirect(t_exec *exec, t_config *data,
			t_node *env, t_node *export);
int		executor_redirect(t_exec *exec, t_config *data,
			t_node *env, t_node *export);
int		executor(t_exec *exec, t_config *data, t_node *env, t_node *export);
void	executor_pipe(t_exec *exec, t_config *data,
			t_node *env, t_node *export);
int		validation_cmd(t_exec *exec, t_config *data);
int		validation_fd_inp(char *fd);
int		validation_fd_out(char *fd);
int		aux_validation(t_config *data, t_exec *exec);
int		aux_get_fd_output(t_exec *exec, int fd, int i);
void	get_redirect(t_exec *exec, t_config *data);
int		get_fd_output(t_exec *exec);
int		get_fd_input(t_exec *exec, t_config *data);
void	empty_cmd_handle(t_exec *exec);

// heredoc
int		heredoc(char *eof, t_config *data);
int		reset_heredoc(char *eof, char *buffer, t_config *data);
int		heredoc_loop(char *eof, char *buffer, t_config *data);

void	close_fd(int **fd, t_config *data);

char	*expansion_heredoc(char *ptr, t_node *env);
char	*norm_expansion_heredoc(int j, char *ptr, t_node *env);
char	*get_key_heredoc(char *ptr, int j);

void	norm_aux_exec_redirect(t_exec *exec,
			t_config *data, t_node *env, t_node *export);
void	close_redirect(t_exec *exec);

#endif