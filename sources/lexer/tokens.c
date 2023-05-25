/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:30:07 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/25 13:57:31 by rleslie-         ###   ########.fr       */
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
		s1 = (char **)calloc(sizeof(char *), 1);
		s1 [0] = NULL;
	}
	str = (char **)calloc(sizeof(char **) , ( 1 + ft_tab_len(s1)) + 1);
	if (str == NULL || !s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		str[i] = ft_strdup(s1[i]);
		i++;
	}
	while (x < 1)
		str[i++] = ft_strdup(s2[x++]);
	str[i] = NULL;
	if (s1)
		ft_free_tab(s1);
	return ((char **)str);
}

t_exec	*node_exec(t_config *data, t_lexer *point)
{
	t_exec	*node;
	char	**if_null;
	
	if_null = (char *[]){"-", 0};
	node = (t_exec *)malloc(sizeof(t_exec));
	node->cmd = NULL;
	node->redirect = NULL;
	while(point->i < ft_tab_len(data->tokens))
	{
		if (data->tokens[point->i] && op_redirect(data->tokens[point->i][0]) == 3)
		{
			if (!node->redirect)
				node->redirect = strdup_tab(if_null, 0, ft_tab_len(if_null));
			node->is_builtin = op_builtins(data->tokens[0]);
			node->index = point->index;
			node->next = NULL;
			return (node);
		}
		else if (op_redirect(data->tokens[point->i][0]) == 2 && op_redirect(data->tokens[point->i][0]) != 1)
		{
			node->redirect = strjoin_tab(node->redirect, &data->tokens[point->i++]);
			node->redirect = strjoin_tab(node->redirect, &data->tokens[point->i]);
		}
		else
			node->cmd = strjoin_tab(node->cmd, &data->tokens[point->i]);
		point->i++;;
	}
	if (!node->redirect)
		node->redirect = strdup_tab(if_null, 0, ft_tab_len(if_null));
	node->is_builtin = op_builtins(data->tokens[0]);
	node->index = point->index;
	node->next = NULL;
	return (node);
}

void ft_lexer_tokens(t_exec **exec, t_config *data)
{
	t_lexer	point;

	point.i = 0;
	point.index = 0;
	while(point.i < ft_tab_len(data->tokens))
	{
		exec_link_node_end(exec, node_exec(data, &point));
		point.index++;
		point.i++;
	}
}
