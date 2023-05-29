#include "../../minishell.h"

int	heredoc(t_exec *exec, t_config *data, int i)
{
	int		fd;
	char	*user_input;

	(void)data;
	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		user_input = readline("> ");
		if (ft_strncmp(user_input, exec->redirect[i], (ft_strlen(exec->redirect[i]) + 1)== 0))
			break ;
		else
		{
			ft_putendl_fd(user_input, fd);
			free(user_input);
		}
	}
	free(user_input);
	close(fd);
	return (1);
}

void	input_heredoc_pipe(t_config *data, t_exec *exec, int i)
{
	t_config	vars;
	extern char	**environ;

	if (heredoc(exec, data, i))
	{
		vars.fd = open("heredoc", O_RDONLY);
		if (vars.fd == -1)
			//fazer error
		dup2(vars.fd, 0);
		if (execve(exec_path(data, exec), exec->cmd, environ) == -1)
		{
			g_status_code = 127;
			//free_var(env, export, data, exec);
			ft_putstr_fd("error", 2);// matar o processo
			exit(g_status_code);
		}
		close(vars.fd);
		g_status_code = 0;
	}
}