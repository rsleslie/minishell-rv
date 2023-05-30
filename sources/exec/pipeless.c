/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeless.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:14:00 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/30 20:22:27 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	execute_cmd_pipeless(t_exec *exec, t_config *data, int i)
// {
// 	t_config		vars;
// 	extern char		**environ;

// 	if (ft_strncmp(exec->redirect[i - 1], ">",
// 			ft_strlen(exec->redirect[i - 1])) == 0)
// 		vars.fd = open(exec->redirect[i], O_RDWR
// 				| O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, 0644);
// 	if (ft_strncmp(exec->redirect[i - 1], ">>",
// 			ft_strlen(exec->redirect[i - 1])) == 0)
// 		vars.fd = open(exec->redirect[i], O_RDWR
// 				| O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
// 	if (ft_strncmp(exec->redirect[i - 1], "<",
// 			ft_strlen(exec->redirect[i - 1])) == 0)
// 	{
// 		if (input_redirection(data, exec, i) == 1)
// 			return (1);
// 		return (0);
// 	}
// 	if (vars.fd == -1)
// 	{
// 		g_status_code = 1;
// 		return (1);
// 	}
// 	if (i == (ft_tab_len(exec->redirect) - 1))
// 	{
// 		vars.pid = fork();
// 		if (vars.pid == 0)
// 		{
// 			vars.bkp = dup(1);
// 			dup2(vars.fd, 1);
// 			if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
// 			{
// 				dup2(vars.bkp, 1);
// 				close(vars.fd);
// 				close(vars.bkp);
// 				g_status_code = 127;
// 				return (1);
// 			}
// 			dup2(vars.bkp, 1);
// 			close(vars.fd);
// 			close(vars.bkp);
// 		}
// 		vars.status = 0;
// 		waitpid(vars.pid, &vars.status, 0);
// 		if (WIFEXITED(vars.status))
// 			g_status_code = WEXITSTATUS(vars.status);
// 	}
// 	return (0);	
// }

// int counter_redect(char *key, t_exec *exec)
// {
// 	int i;
// 	int	counter;
	
// 	i = -1;
// 	counter = 0;
// 	while(exec->redirect[++i])
// 	{
// 		if(ft_strncmp(exec->redirect[i - 1], key, ft_strlen(exec->redirect[i])) == 0)
// 			counter++;
// 	}
// 	return (counter);
// }

// void	norm_pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export)
// {
// 	t_config	vars;
// 	extern char	**environ;

// 	vars.pid = fork();
// 	if (vars.pid == 0)
// 	{
// 		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
// 		{
// 			g_status_code = 127;
// 			ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
// 			free_var(env, export, data, exec);
// 			ft_putstr_fd("error", 2);
// 			exit(g_status_code);
// 		}
// 	}
// 	vars.status = 0;
// 	waitpid(vars.pid, &vars.status, 0);
// 	if (WIFEXITED(vars.status))
// 		g_status_code = WEXITSTATUS(vars.status);
// }

// void	norminette_exec_builtins(int fd, t_exec *exec,
// 	t_node *env, t_node *export)
// {
// 	int			bkp;

// 	bkp = dup(1);
// 	dup2(fd, 1);
// 	exec_builtins(exec, env, export);
// 	dup2(bkp, 1);
// 	close(fd);
// 	close(bkp);
// }


// void	norminette_exec_builtins(int fd, t_exec *exec,
// 	t_node *env, t_node *export)
// {
// 	int			bkp;

// 	bkp = dup(1);
// 	dup2(fd, 1);
// 	exec_builtins(exec, env, export);
// 	dup2(bkp, 1);
// 	close(fd);
// 	close(bkp);
// }


// void	execute_builtins(t_exec *exec, t_node *env, t_node *export)
// {
// 	int	fd_input;
// 	int	fd_output;
	
// 	if (exec->redirect[0][0] != '-')
// 	{	
// 		fd_input = get_fd_input(exec);
// 		fd_output = get_fd_output(exec);
// 		if (fd_input == -1)
// 		{
// 			g_status_code = 1;
// 			ft_putstr_fd("No such file or directory", 2);
// 			return ;
// 		}
// 		// norminette_exec_builtins(fd_input, fd_output, exec);

// 	}
// 	else
// 		exec_builtins(exec, env, export);
// }




//-------------------

char	*exec_path(t_config *data, t_exec *exec)
{
	char	*path_check;
	int		i;

	i = -1;
	while (data->paths[++i])
	{
		if (access(exec->cmd[0], X_OK) != -1)
		{
			g_status_code = 1;
			return (0);
		}
		path_check = ft_strdup(data->paths[i]);
		path_check = ft_strjoin(path_check, "/");
		path_check = ft_strjoin(path_check, exec->cmd[0]);
		if (access(path_check, X_OK) != -1)
		{
			g_status_code = 1;
			free(exec->cmd[0]);
			exec->cmd[0] = ft_strdup(path_check);
			free(path_check);
			return (exec->cmd[0]);
		}
		free(path_check);
	}
	return (0);
}

//-----------------




int	input_redirection(t_config *data, t_exec *exec, t_node *env, t_node *export)
{
	extern char	**environ;
	
	dup2(data->fd_input, 0);
	if (op_builtins(exec->cmd[0]) != 0)
		exec_builtins(exec, env, export);
	else
	{
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
			return (1);
	}
	close(data->fd_input);
	return (0);
}

int	output_redirection(t_config *data, t_exec *exec, t_node *env, t_node *export)
{
	int			bkp;
	extern char	**environ;
	
	bkp = dup(1);
	dup2(data->fd_output, 1);
	if (op_builtins(exec->cmd[0]) != 0)
		exec_builtins(exec, env, export);
	else
	{
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
			return (1);
	}
	dup2(bkp, 1);
	close(data->fd_output);
	close(bkp);
	return (0);
}

int cmd_acess(char *str)
{
	// (void)str;
	if (access(str, F_OK) == -1)
	{
		ft_putstr_fd("Permission denied\n", 2);
		g_status_code = 126;
		return (1);
	}
	if (access(str, X_OK) == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		g_status_code = 127;
		return (1);
	}
	return (0);
}

int	validation_cmd(t_exec *exec, t_config *data)
{
	char	*path_check;
	int		i;

	i = 0;
	if (exec->cmd[0][0] != '.' && exec->cmd[0][0] != '/')
	{
		while(data->paths[i])
		{
			path_check = ft_strdup(data->paths[i]);
			path_check = ft_strjoin(path_check, "/");
			path_check = ft_strjoin(path_check, exec->cmd[0]);
			if (access(path_check, F_OK) == 0)
			{
				if (access(path_check, X_OK) == -1)
				{
					ft_putstr_fd("Permission denied\n", 2);
					g_status_code = 127;
					return (1);
				}
				free(path_check);
				return (0);
			}
			i++;
			free(path_check);
		}
	}
	else
	{
		if ((cmd_acess(data->tokens[0])) == 0)
			return (0);
	}
	if (op_builtins(data->tokens[0]) != 0)
		return (0);
	ft_putstr_fd("No such file or directory\n", 2);
	g_status_code = 1;
	return (1);
}

int	get_fd(t_exec *exec, t_config *data)
{
	data->fd_input = 0;
	data->fd_output = 0;
	if (exec->redirect[0][0] != '-')
	{
		data->fd_input = get_fd_input(exec);
		data->fd_output = get_fd_output(exec);
		if (data->fd_input == -1)
		{
			g_status_code = 1;
			ft_putstr_fd("No such file or directory", 2);
			if (data->fd_output != 0)
				close(data->fd_output);
			close(data->fd_input);
			return (1);
		}
	}
	return (0);
}

int	exec_redirect(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char	**environ;
	
	if (data->fd_input != 0 && data->fd_output != 0)
	{
		dup2(data->fd_input, 0);
		dup2(data->fd_output, 1);
		if (op_builtins(exec->cmd[0]) != 0)
			exec_builtins(exec, env, export);
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			close(data->fd_input);
			close(data->fd_output);
			ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
			free_var(env, export, data, exec);
			g_status_code = 127;
			exit (g_status_code);
		}
		close(data->fd_input);
		close(data->fd_output);
		exit(g_status_code);
		return (1);
	}
	else if (data->fd_input != 0)
	{
		input_redirection(data, exec, env, export);
		exit(g_status_code);
		return (1);
	}
	return (0);
}

void	pipeless(t_exec *exec, t_config *data, t_node *env, t_node *export)
{
	extern char	**environ;
	
	if (get_fd(exec, data) == 1)
		return ;
	if (validation_cmd(exec, data) == 0)
	{
		if (exec_redirect(exec, data, env, export) == 0)
		{
			if (data->fd_output != 0)
			{
				output_redirection(data, exec, env, export);
				exit(g_status_code);
			}
			else
			{
				if (op_builtins(exec->cmd[0]) != 0)
					exec_builtins(exec, env, export);
				else if(execve(exec_path(data, exec), exec->cmd, environ) == -1)
				{
					ft_free_tab_int(exec->fd, pipe_counter(data->tokens));
					free_var(env, export, data, exec);
					g_status_code = 127;
					exit (g_status_code);
				}
			}
		}
	}
}

//export e cd unset 