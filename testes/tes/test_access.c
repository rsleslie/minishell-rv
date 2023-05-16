char	*exec_path(t_config *data, t_exec *exec)
{
	char	*path_check;
	int		i;

	i = 0;
	while (data->paths[i])
	{
		if (access(exec->cmd[0], X_OK) != -1)
			return (0);
		path_check = ft_strdup(data->paths[i]);
		path_check = ft_strjoin(path_check, "/");
		path_check = ft_strjoin(path_check, exec->cmd[0]);
		if (access(path_check, X_OK) != -1)
		{
			free(exec->cmd[0]);
			exec->cmd[0] = ft_strdup(path_check);
			free(path_check);
			return (exec->cmd[0]);
		}
		i++;
		free(path_check);
	}
	return (0);
}

int main()
{

}