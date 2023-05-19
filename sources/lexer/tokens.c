/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:30:07 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/19 15:33:20 by rleslie-         ###   ########.fr       */
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
	str = (char **)malloc(sizeof(char *) * ((end - start) + 1));
	while(i < size)
	{
		
		str[i] = ft_strdup(tab[start++]);
		i++;
	}
	str[i] = NULL;
	if (!tab)
		ft_tab_len(tab);
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
	size = ft_tab_len(tokens) - (end - start);
	ptr = (char **)malloc(sizeof(char *) * (size + 1));
	j = 0;
	while(i < size)
	{
		if (i == start)
			j = end;
		ptr[i] = ft_strdup(tokens[j]);
		i++;
		j++;
	}
	ft_tab_len(tokens);
	ptr[i] = NULL;
	return (ptr);
}

t_exec *node_exec(char **str, int index)
{
	int		i;
	char	**redirect;
	t_exec	*node;
	char	**if_null= (char *[]){"-1", 0};
	
	i = 0;
	redirect = NULL;
	while(str[i])
	{
		if (op_redirect(str[i][0]) == 2 || op_redirect(str[i][0]) == 1 )
		{
			
			if (!redirect)
				redirect = strdup_tab(str, i, i + 1);
			else 
				redirect = strjoin_tab(redirect, strdup_tab(str, i, i + 1));
			str = remove_str_tab(str, i, i + 2);
			if (i != 0)
				i -= 2;
			else
				i -= 1;
		}
		i++;
	}
	
	node = malloc(sizeof(t_exec));
	node->cmd =strdup_tab(str, 0, i);
	if (!redirect)
		node->redirect = strdup_tab(if_null, 0, ft_tab_len(if_null));
	else
		node->redirect = strdup_tab(redirect, 0,ft_tab_len(redirect));
	node->is_builtin = op_builtins(str[0]);
	node->index = index;
	node->next = NULL;
	return(node);
}

void ft_lexer_tokens(t_exec **exec, t_config *data)
{
	int		i;
	int		start;
	char	**temp;
	int		index;

	i = 0;
	start = 0;
	index = 0;
	while(data->tokens[i])
	{
		if (op_redirect(data->tokens[i][0]) == 3 || !data->tokens[i + 1])
	 	{
			if (!data->tokens[i + 1])
				temp = strdup_tab(data->tokens, start, i + 1);
			else 
				temp = strdup_tab(data->tokens, start, i);			
			exec_link_node_end(exec, node_exec(temp, index));
			if (temp)
				is_null(temp);
	 		if (op_redirect(data->tokens[i][0]) == 3)
				start = i + 1;
			else
				start = i;
			index++;
		}
	 	i++;
	}
}
