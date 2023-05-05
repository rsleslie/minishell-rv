/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:42:57 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/05 14:42:56 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int parser(t_config *data)
{
    if (quotes_parser(data) == 1)
    {
        ft_printf("=============\nQuotes error\n");
        return (1);
    }
	if (pipe_parser(data) == 1)
	{
		ft_printf("=============\nPipe error\n");
		return (1);
	}
	if (redirect_parser(data) == 1)
	{
		ft_printf("=============\nRedirect error\n");
		return (1);
	}
	if (builtin_parser(data, data->tokens[0]) == 1 && executables_parser(data, data->tokens[0]) == 1)
	{
		ft_printf("=============\nErro arguments\n");
		return (1);
	}
    return (0);
}

// essspaco enter
//
//enteer

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
				return (1);
			if (data->tokens[i + 1] && (data->tokens[i + 1][0] == '>' || data->tokens[i + 1][0] == '<'
				|| data->tokens[i + 1][0] == '|'))
				return (1);
		}
		i++;
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


// int	is_executable(t_config *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->tokens[i])
// 	{
// 		if (data->tokens[0][0] != '<' && data->tokens[0][0] != '>')
// 		{
// 			if (builtin_parser(data, data->tokens[0]) == 1 && executables_parser(data, data->tokens[0]) == 1)
// 				return (1);
// 		}
// 		if (data->tokens[i][0] == '|')
// 		{
// 			if (builtin_parser(data, data->tokens[i + 1]) == 1 && )
// 		}
// 		i++;
// 	}
// }