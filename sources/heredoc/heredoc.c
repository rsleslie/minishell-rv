/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:13:38 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/15 20:03:41 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ctrl_d_heredoc(char *buffer, t_config *data)
{
	ft_putendl_fd("minishell: warning: here-document delimited by end-of-file",
		2);
	if (buffer)
		free(buffer);
	close(g_data.fd);
	ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
	free_var(data->node_env, data->node_export, data, data->node_exec);
}

void	eof_heredoc(char *buffer, t_config *data)
{
	if (buffer)
		free(buffer);
	close(g_data.fd);
	ft_free_tab_int(data->fd_pipe, pipe_counter(data->tokens));
	free_var(data->node_env, data->node_export, data, data->node_exec);
}

int	heredoc_loop(char *eof, char *buffer, t_config *data)
{
	char	*test;

	signal(SIGINT, handle_heredoc_sigint);
	buffer = readline("> ");
	if (buffer && !ft_lurkstr(buffer, '$')
		&& (eof[0] != '\'' && eof[0] != '\"'))
	{
		test = expansion_heredoc(buffer, data->node_env);
		free (buffer);
		buffer = ft_strdup(test);
		free(test);
	}
	if (!buffer)
	{
		ctrl_d_heredoc(buffer, data);
		return (131);
	}
	if (ft_strncmp(buffer, eof, ft_strlen(eof) + 1) == 0)
	{
		eof_heredoc(buffer, data);
		exit (0);
	}
	reset_heredoc(eof, buffer, data);
	return (0);
}

int	reset_heredoc(char *eof, char *buffer, t_config *data)
{
	ft_putendl_fd(buffer, g_data.fd);
	free(buffer);
	heredoc_loop(eof, buffer, data);
	return (0);
}

int	heredoc(char *eof, t_config *data)
{
	char	*buffer;
	int		pid;
	int		status;

	status = 0;
	buffer = NULL;
	pid = fork();
	signal_handler_child_heredoc();
	if (pid == 0)
	{
		g_data.fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		exit(heredoc_loop(eof, buffer, data));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->status_code = WEXITSTATUS(status);
	return (data->status_code);
}
