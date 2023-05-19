/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:19:01 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/19 17:16:53 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*search_var(t_node *list, char *exec, char *key)
{
	t_node	*aux;

	aux = list;
	while (aux != NULL)
	{
		if (search_env(key, aux->variable) == 0)
		{
			free(exec);
			return (ft_strdup(aux->value));
		}
		aux = aux->next;
	}
	free(exec);
	return (ft_strdup("-1"));
}

char	*dollar_refesh(char *cmd)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(cmd) - 1));
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			if (g_status_code == 0)
				ptr[j] = '0';
			if (g_status_code == 1)
				ptr[j] = '1';
			j++;
			i += 2;
			continue;
		}
		ptr[j] = cmd[i];
		i++;
		j++;	
	}
	free(cmd);
	return (ptr);
}

void	status_code(t_exec *exec, int i)
{
	if (exec->cmd[i][0] == '$' && exec->cmd[i][1] == '?' && exec->cmd[i][2])
	{
		exec->cmd[i] = dollar_refesh(exec->cmd[i]);
		return ;
	}
	if (g_status_code == 0)
	{
		free(exec->cmd[i]);
		exec->cmd[i] = ft_strdup("0");
		return;
	}
	if (g_status_code == 1)
	{
		free(exec->cmd[i]);
		exec->cmd[i] = ft_strdup("1");
		return ;
	}
	if (g_status_code == 127)
	{
		free(exec->cmd[i]);
		exec->cmd[i] = ft_strdup("127");
		return ;
	}
}

void dollar_sign(t_exec *exec, t_node *env)
{
	t_exec	*aux;
	int		i;
	int		j;

	j = 0;
	aux = exec;
	while (aux)
	{
		i = 0;
		while(aux->cmd[i])
		{
			if (aux->cmd[i][0] == '$' && aux->cmd[i][1] == '?')
				status_code(exec, i);
			if (aux->cmd[i][0] == '$' && aux->cmd[i][2])
				aux->cmd[i] = search_var(env, exec->cmd[i], &exec->cmd[i][1]);
			if (aux->cmd[i][0] == DOUBLE_QUOTE)
				dollar_quotes(env, aux->cmd[i]);
			i++;
		}
		aux = aux->next;
	}
}	
