/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:42:57 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/12 15:08:09 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipe_parser(t_config *data)
{
	int	i;

	i = 0;
	if (data->tokens[i][0] == '|')
		return (1);
	while (data->tokens[i])
	{
		if (data->tokens[i][0] == '|' && (data->tokens[i + 1][0] == '|'
			|| data->tokens[i][1] == '|'))
		{
			data->status_code = 2;
			return (1);
		}
		if (data->tokens[ft_tab_len(data->tokens) - 1][0] == '|')
		{
			data->status_code = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int	aux_redirect_parser(t_config *data, int i)
{
	if (data->tokens[ft_tab_len(data->tokens) - 1][0] == '<'
		|| data->tokens[ft_tab_len(data->tokens) - 1][0] == '>')
	{
		data->status_code = 2;
		return (2);
	}
	if (data->tokens[i + 1] && (data->tokens[i + 1][0] == '>'
		|| data->tokens[i + 1][0] == '<'
			|| data->tokens[i + 1][0] == '|'))
	{
		data->status_code = 2;
		return (2);
	}
	return (0);
}

int	redirect_parser(t_config *data)
{
	int	i;

	i = -1;
	while (data->tokens[++i])
	{
		if (data->tokens[i][0] == '>' || data->tokens[i][0] == '<')
		{
			if (aux_redirect_parser(data, i) == 2)
				return (2);
		}
	}
	if (data->tokens[0][0] == '>' && ft_tab_len(data->tokens) == 2)
	{
		open(data->tokens[1], O_CREAT, 0644);
		data->status_code = 0;
		return (1);
	}
	return (0);
}

int	builtin_parser(t_config *data, char *s)
{
	(void)data;
	if (ft_strncmp(s, "echo", ft_strlen(s)) == 0)
		return (0);
	else if (ft_strncmp(s, "pwd", ft_strlen(s)) == 0)
		return (0);
	else if (ft_strncmp(s, "cd", ft_strlen(s)) == 0)
		return (0);
	else if (ft_strncmp(s, "env", ft_strlen(s)) == 0)
		return (0);
	else if (ft_strncmp(s, "export", ft_strlen(s)) == 0)
		return (0);
	else if (ft_strncmp(s, "unset", ft_strlen(s)) == 0)
		return (0);
	return (1);
}

int	executables_parser(t_config *data, char *s)
{
	char	*path_check;
	int		i;

	i = 0;
	while (data->paths[i])
	{
		if (access(data->tokens[0], F_OK | X_OK) != -1)
		{
			data->status_code = 127;
			return (0);
		}
		path_check = ft_strdup(data->paths[i]);
		path_check = ft_strjoin(path_check, "/");
		path_check = ft_strjoin(path_check, s);
		if (access(path_check, X_OK) != -1)
		{
			data->status_code = 127;
			free(path_check);
			return (0);
		}
		i++;
		free(path_check);
	}
	data->status_code = 0;
	return (1);
}
