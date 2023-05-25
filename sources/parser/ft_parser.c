/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:42:57 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/20 19:05:25 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int parser(t_config *data)
{
	if (redirect_parser(data) == 1)
		return (1);
	if (redirect_parser(data) == 2)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (1);
	}
	if (quotes_parser(data) == 1)
	{
		ft_printf("Minishell: Quotes error\n");
		return (1);
	}
	if (pipe_parser(data) == 1)
	{
		ft_printf("Mnishell: syntax error near unexpected token \n");
		return (1);
	}
	if ((builtin_parser(data, data->tokens[0]) == 1 && executables_parser(data, data->tokens[0]) == 1))
	{	
		ft_printf("%s: Command not found\n", data->tokens[0]);
		return (1);
	}
    return (0);
}

int quotes_parser(t_config *data)
{
    int i;

    i = 0;
    while (data->tokens[i])
    {
        if ((data->tokens[i][0] == SIMPLE_QUOTE || data->tokens[i][0]
            == DOUBLE_QUOTE) && ft_char_counter(data->tokens[i], data->tokens[i][0]) == 1)
            return (1); 
        i++;
    }
    return (0);
}

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
			return (1);
		if (data->tokens[ft_tab_len(data->tokens) - 1][0] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	redirect_parser(t_config *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		if (data->tokens[i][0] == '>' || data->tokens[i][0] == '<')
		{
			if (data->tokens[ft_tab_len(data->tokens) - 1][0] == '<'
				|| data->tokens[ft_tab_len(data->tokens) - 1][0] == '>')
				return (2);
			if (data->tokens[i + 1] && (data->tokens[i + 1][0] == '>' || data->tokens[i + 1][0] == '<'
				|| data->tokens[i + 1][0] == '|'))
				return (2);
			if (data->tokens[i][0] == '<')
			{
				if (access(data->tokens[i + 1], F_OK) == -1)
				{
					printf("%s: No such file or directory\n", data->tokens[i + 1]);
					return (1);
				}
			}
		}
		i++;
	}
	
	if (data->tokens[0][0] == '>' && ft_tab_len(data->tokens) == 2)
	{
		open(data->tokens[1], O_CREAT, 0644);
		return (1);
	}
	return (0);
}

int builtin_parser(t_config *data, char *s)
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
		if (access(data->tokens[0], X_OK) != -1)
			return (0);
		path_check = ft_strdup(data->paths[i]);
		path_check = ft_strjoin(path_check, "/");
		path_check = ft_strjoin(path_check, s);
		if (access(path_check, X_OK) != -1)
		{
			free(path_check);
			return (0);
		}
		i++;
		free(path_check);
	}
	return (1);
}
