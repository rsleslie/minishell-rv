/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:30:07 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/06 13:49:46 by rleslie-         ###   ########.fr       */
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
	while (i < size)
	{
		str[i] = ft_strdup(tab[start++]);
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	norm_node_exec(t_config *data, t_lexer *point, t_exec *node)
{
	if (op_redirect(data->tokens[point->i][0]) == 2
		|| op_redirect(data->tokens[point->i][0]) == 1)
	{
		node->redirect = strjoin_tab(node->redirect,
				&data->tokens[point->i++]);
		node->redirect = strjoin_tab(node->redirect,
				&data->tokens[point->i]);
	}
	else
		node->cmd = strjoin_tab(node->cmd, &data->tokens[point->i]);
	point->i++;
}

void	norm_node_two(t_exec *node, t_config *data,
	char **if_null, t_lexer *point)
{
	if (!node->redirect)
		node->redirect = strdup_tab(if_null, 0, ft_tab_len(if_null));
	node->is_builtin = op_builtins(data->tokens[0]);
	node->index = point->index;
	node->next = NULL;
}

t_exec	*node_exec(t_config *data, t_lexer *point)
{
	t_exec	*node;
	char	**if_null;

	if_null = (char *[]){"-", 0};
	node = (t_exec *)malloc(sizeof(t_exec));
	node->cmd = NULL;
	node->redirect = NULL;
	while (point->i < ft_tab_len(data->tokens))
	{
		if (data->tokens[point->i]
			&& op_redirect(data->tokens[point->i][0]) == 3)
		{
			if (!node->redirect)
				node->redirect = strdup_tab(if_null, 0, ft_tab_len(if_null));
			node->is_builtin = op_builtins(data->tokens[0]);
			node->index = point->index;
			node->next = NULL;
			return (node);
		}
		else
			norm_node_exec(data, point, node);
	}
	norm_node_two(node, data, if_null, point);
	return (node);
}

void	ft_lexer_tokens(t_exec **exec, t_config *data)
{
	t_lexer	point;

	point.i = 0;
	point.index = 0;
	while (point.i < ft_tab_len(data->tokens))
	{
		exec_link_node_end(exec, node_exec(data, &point));
		point.index++;
		point.i++;
	}
}
