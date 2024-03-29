/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:50:51 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/14 18:26:27 by rleslie-         ###   ########.fr       */
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
	return (ft_strdup(" "));
}

void	status_code(t_exec *exec, int i)
{
	if (exec->cmd[i][0] == '$' && exec->cmd[i][1] == '?' && exec->cmd[i][2])
	{
		exec->cmd[i] = dollar_refesh(exec->cmd[i]);
		return ;
	}
	exec->cmd[i] = ft_strdup(ft_itoa(g_data.status_code));
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
			if (g_data.status_code == 0)
				ptr[j] = '0';
			if (g_data.status_code == 1)
				ptr[j] = '1';
			j++;
			i += 2;
			continue ;
		}
		ptr[j] = cmd[i];
		i++;
		j++;
	}
	free(cmd);
	return (ptr);
}

void	aux_dollar(t_exec *aux, t_node *env)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	(void)env;
	while (aux->cmd && aux->cmd[++i])
	{
		if (aux->cmd[i][0] == DOUBLE_QUOTE && aux->cmd[i][1] == '$'
			&& aux->cmd[i][2] == DOUBLE_QUOTE)
			continue ;
		if (aux->cmd[i][0] == SIMPLE_QUOTE && aux->cmd[i][1] == '$'
			&& aux->cmd[i][2] == SIMPLE_QUOTE)
			continue ;
		if (aux->cmd[i][0] == '$' && aux->cmd[i][1] == '?' && !aux->cmd[i][2])
		{
			free(aux->cmd[i]);
			aux->cmd[i] = ft_itoa(g_data.status_code);
		}
		else if (aux->cmd[i][0] == '$'
			&& aux->cmd[i][1] == '?' && aux->cmd[i][2])
			aux->cmd[i] = dollar_refesh(aux->cmd[i]);
		else if (aux->cmd[i][0] == '$' && aux->cmd[i][1])
			aux->cmd[i] = search_var(env, aux->cmd[i], &aux->cmd[i][1]);
	}
}

void	dollar_sign(t_exec *exec, t_node *env)
{
	t_exec	*aux;
	int		i;

	aux = exec;
	while (aux)
	{
		aux_dollar(aux, env);
		i = -1;
		while (aux->redirect[++i] && aux->redirect)
		{
			if (aux->redirect[i][0] == '$' && aux->redirect[i][1] == '?')
			{
				free(aux->cmd[i]);
				aux->cmd[i] = ft_itoa(g_data.status_code);
			}
			else if (aux->redirect[i][0] == '$' && aux->redirect[i][1])
				aux->redirect[i] = search_var(env, aux->redirect[i],
						&aux->redirect[i][1]);
		}
		aux = aux->next;
	}
}
