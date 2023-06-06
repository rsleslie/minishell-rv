/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:13:38 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/06 19:27:41 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// tem que expandir
int	heredoc(char *eof)
{
	int		fd;
	char	*buffer;
	int		bkp;
	// int		pid;
	
	buffer = NULL;
	// pid = fork();
	signal_handler_child();
	// if (pid == 0)
	// {
		signal(SIGINT, handle_heredoc_sigint);
		fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		bkp = dup(1);
		while (1)
		{
			buffer = readline("> ");
			if (!buffer)
			{
				ft_putendl_fd("minishell: warning: here-document delimited by end-of-file", 2);
				free(buffer);
				close(bkp);
				close(fd);
				exit(131);
			}
			if (ft_strncmp(buffer, eof, ft_strlen(eof) + 1) == 0)
				break ;
			dup2(fd, 1);
			ft_putendl_fd(buffer, fd);
			dup2(bkp, 1);
			free(buffer);
		}
		free(buffer);
		close(bkp);
		close(fd);
	// }
	// int status = 0;
	// waitpid(pid, &status, 0);
	// if (WIFEXITED(status))
	// 	g_status_code = WEXITSTATUS(status);
	return(g_status_code); 
}
