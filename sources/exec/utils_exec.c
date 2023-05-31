/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:37:28 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/30 20:37:42 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
