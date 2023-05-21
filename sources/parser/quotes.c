/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverona- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:20:52 by rverona-          #+#    #+#             */
/*   Updated: 2023/05/20 21:21:02 by rverona-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	quotes_parser(t_config *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		if ((data->tokens[i][0] == SIMPLE_QUOTE || data->tokens[i][0]
			== DOUBLE_QUOTE)
			&& ft_char_counter(data->tokens[i], data->tokens[i][0]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	strip_quotes(t_exec *exec, int i)
{
	char	*ptr;
	int		j;
	int		size;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(exec->cmd[i]) - 2));
	size = 1;
	j = 0;
	while (exec->cmd[i][size + 1])
	{
		ptr[j] = exec->cmd[i][size];
		size++;
		j++;
	}
	ptr[j] = '\0';
	free(exec->cmd[i]);
	exec->cmd[i] = ft_strdup(ptr);
	free(ptr);
}

void	unquotes(t_exec *exec)
{
	t_exec	*aux;
	int		i;

	aux = exec;
	while (aux != NULL)
	{
		i = -1;
		while (aux->cmd[++i])
		{
			if (aux->cmd[i][0] == DOUBLE_QUOTE
				|| aux->cmd[i][0] == SIMPLE_QUOTE)
				strip_quotes(exec, i);
		}
		aux = aux->next;
	}
}

char	*remove_quotes(char *str)
{
	size_t	i;
	char	*cp;

	i = 0;
	cp = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (i < (ft_strlen(str) - 1))
	{
		cp[i] = str[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
