/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:30:07 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/12 19:56:03 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**strdup_tab(char **tab, int start, int end)
{
	int		size;
	char	**str;
	int		i;
	
	i = 0;
	size = end - start;
	str = (char **)malloc(sizeof(char *) * (end - start) + 1);
	while(i < size)
		str[i++] = ft_strdup(tab[start++]);
	str[i] = NULL;
	return (str);		
}

char	**strjoin_tab(char **s1, char **s2)
{
	char	**str;
	size_t	i;
	int		x;

	i = 0;
	x = 0;
	if (!s1)
	{
		s1 = (char **)malloc(sizeof(char *));
		s1 [0] = NULL;
	}
	str = (char **)malloc(sizeof(char *) * (ft_tab_len(s2) + ft_tab_len(s1)) + 1);
	if (str == NULL || !s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[x])
		str[i++] = s2[x++];
	str[i] = NULL;
	return ((char **)str);
}

char	**remove_str_tab(char **tokens, int start, int end)
{
	int		j;
	int		i;
	int		size;
	char	**ptr;
	
	i = 0;
	size = ft_tab_len( tokens) - (end - start);
	ptr = (char **)malloc(sizeof(char *) * size + 1);
	j = 0;
	while(i < size)
	{
		if (i == start)
			j = end;
		ptr[i++] = ft_strdup(tokens[j++]);
	}
	ptr[i] = NULL;
	ft_free_tab(tokens);
	return (ptr);
}
//mandar star + 1

void	test(t_config *data)
{
	int i;
	char 	**redirect;
	
	i = 0;
	redirect = NULL;
	while(data->tokens[i])
	{
		if (op_redirect(data->tokens[i][0]) == 2 || op_redirect(data->tokens[i][0]) == 1)
		{
			if (!redirect)
				redirect = strdup_tab(data->tokens, i, i + 2);
			else 
				redirect = strjoin_tab(redirect, strdup_tab(data->tokens, i, i + 2));
			data->tokens = remove_str_tab(data->tokens, i, i + 2);
			if (i != 0)
				i -= 2;
			else
				i -= 1;
		}
		i++;
	}
	if (redirect)
	{
		i = 0;
		while(redirect[i])
			printf("cmd:  %s\n", redirect[i++]);
	}
}

void	lexer_tokens(t_exec **exec, t_config *data)
{
	int		i;
	char	**cmd;
	char	**redirect;
	int		index;
	int		j;
	int		start;
	int		end;
	
	index = 0;
	cmd = NULL;
	redirect = NULL;
	i = 0;
	j = 0;
	while (data->tokens[i])
	{
		if(data->tokens[i][0] == '|' || !data->tokens[i + 1])
		{
			start = j;
			while ( j < i)
			{
				if (op_redirect(data->tokens[j][0]) == 2 || op_redirect(data->tokens[j][0]) == 1)
				{
					if (!cmd)
						cmd = strdup_tab(data->tokens, j, j + 2);
					else 
						cmd = strjoin_tab(cmd, strdup_tab(data->tokens, j, j + 2));
					data->tokens = remove_str_tab(data->tokens, j, j + 2);
					if (j != 0)
					{
						i -= 2;
						j -= 2;
					}
					else
					{
						i -= 1;
						j -= 1;
					}
				}
				j++;
			}
			cmd = strdup_tab(data->tokens, start, i - 1);
			end = ft_tab_len(cmd);
			exec_link_node_end(exec, create_node_exec(strdup_tab(data->tokens, start, i - 1), redirect, op_builtins(cmd[0]), index));
			index++;
			i = end + 1;
			j = i;
			ft_free_tab(cmd);
		}
		ft_free_tab(redirect);
		i++;
	}
}

/*
	< Makefile > file grep NAME | alguma coisa

	
	<  --------|
	Makefile   |
	>          |
	file	   | no
	greP       |
	NAME       |
	           |
	-----------|
	|
	-----------|
	alguma	   | no
	coisa	   |
	-----------|
*/ 