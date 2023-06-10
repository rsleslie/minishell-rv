/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:13:38 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/10 17:28:58 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// tem que expandir
int	heredoc(char *eof)
{
	int		fd = 0;
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
		fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while (1)
		{
			signal(SIGINT, handle_heredoc_sigint);
			buffer = readline("> ");
			//add_history(buffer);
			if (!buffer)
			{
				ft_putendl_fd("minishell: warning: here-document delimited by end-of-file", 2);
				dup2(bkp, 1);
				free(buffer);
				close(bkp);
				close(fd);
				exit(131);
			}
			if (ft_strncmp(buffer, eof, ft_strlen(eof) + 1) == 0)
			{
				free(buffer);
				dup2(bkp, 1);
				close(bkp);
				close(fd);
				exit(0);
			}
			dup2(fd, 1);
			ft_putendl_fd(buffer, fd);
			dup2(bkp, 1);
			free(buffer);
		}
		free(buffer);
		close(bkp);
		close(fd);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status_code = WEXITSTATUS(status);
	return(g_status_code); 
}
