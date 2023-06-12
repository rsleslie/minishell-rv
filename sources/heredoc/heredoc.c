/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:13:38 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/12 15:08:09 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// tem que expandir
int	heredoc_loop(char *eof, char *buffer, t_config *data, int bkp)
{
	signal(SIGINT, handle_heredoc_sigint);
	buffer = readline("> ");
	add_history(buffer);
	if (!buffer)
	{
		ft_putendl_fd("minishell: warning: here-document delimited by end-of-file", 2);
		dup2(bkp, 1);
		free(buffer);
		close(bkp);
		close(data->fd);
		ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
		free_var(data->node_env, data->node_export, data, data->node_exec);
		return(131);
	}
	if (ft_strncmp(buffer, eof, ft_strlen(eof) + 1) == 0)
	{
		free(buffer);
		dup2(bkp, 1);
		close(bkp);
		close(data->fd);
		ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
		free_var(data->node_env, data->node_export, data, data->node_exec);
		return(0);
	}
	reset_heredoc(eof, buffer, data, bkp);
	return (0);
}

int	reset_heredoc(char *eof, char *buffer, t_config *data, int bkp)
{
	dup2(data->fd, 1);
	ft_putendl_fd(buffer, data->fd);
	dup2(bkp, 1);
	free(buffer);
	heredoc_loop(eof, buffer, data, bkp);
	return (0);
}

int	heredoc(char *eof, t_config *data)
{
	char	*buffer;
	int		bkp;
	int		pid;
	int		status;

	status = 0;	
	buffer = NULL;
	bkp = dup(1);
	pid = fork();
	signal_handler_child_heredoc();
	if (pid == 0)
	{
		data->fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		exit(heredoc_loop(eof, buffer, data, bkp));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->status_code = WEXITSTATUS(status);
	return(data->status_code); 
}

		// while (1)
		// {
		// 	signal(SIGINT, handle_heredoc_sigint);
		// 	buffer = readline("> ");
		// 	add_history(buffer);
		// 	if (!buffer)
		// 	{
		// 		ft_putendl_fd("minishell: warning: here-document delimited by end-of-file", 2);
		// 		dup2(bkp, 1);
		// 		free(buffer);
		// 		close(bkp);
		// 		close(fd);
		// 		exit(131);
		// 	}
		// 	if (ft_strncmp(buffer, eof, ft_strlen(eof) + 1) == 0)
		// 	{
		// 		free(buffer);
		// 		dup2(bkp, 1);
		// 		close(bkp);
		// 		close(fd);
		// 		exit(0);
		// 	}
		// 	dup2(fd, 1);
		// 	ft_putendl_fd(buffer, fd);
		// 	dup2(bkp, 1);
		// 	free(buffer);
		// }
		// free(buffer);
		// close(bkp);
		// close(fd);