/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:13:38 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/13 12:34:07 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ctrl_d_heredoc(int bkp, char *buffer, t_config *data)
{
	ft_putendl_fd("minishell: warning: here-document delimited by end-of-file",
		2);
	dup2(bkp, 1);
	free(buffer);
	close(bkp);
	close(data->fd);
	ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
	free_var(data->node_env, data->node_export, data, data->node_exec);
}

void	eof_heredoc(int bkp, char *buffer, t_config *data)
{
	free(buffer);
	dup2(bkp, 1);
	close(bkp);
	close(data->fd);
	ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
	free_var(data->node_env, data->node_export, data, data->node_exec);
}

int	heredoc_loop(char *eof, char *buffer, t_config *data, int bkp)
{
	char	*test;

	signal(SIGINT, handle_heredoc_sigint);
	buffer = readline("> ");
	add_history(buffer);
	if (!ft_lurkstr(buffer, '$'))
	{
		test = expantion_heredoc(buffer, data->node_env);
		free (buffer);
		buffer = ft_strdup(test);
		free(test);
	}
	if (!buffer)
	{
		ctrl_d_heredoc(bkp, buffer, data);
		return (131);
	}
	if (ft_strncmp(buffer, eof, ft_strlen(eof) + 1) == 0)
	{
		eof_heredoc(bkp, buffer, data);
		return (0);
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
	return (data->status_code);
}
