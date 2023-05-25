/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:19:01 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/24 21:11:13 by rleslie-         ###   ########.fr       */
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
			i++;
		}
		aux = aux->next;
	}
}

char	*teste_code()
{
	if (g_status_code == 0)
		return(ft_strdup("0"));
	if (g_status_code == 1)
		return(ft_strdup("1"));
	if (g_status_code == 127)
		return(ft_strdup("127"));
	return (ft_strdup("0"));
}

char	*search_expansion(char *data, t_node *list, char *key, int j)
{
	t_node	*aux;

	aux = list;
	while (aux != NULL)
	{
		if (search_env(key, aux->variable) == 0)
			return (ft_strdup(aux->value));
		aux = aux->next;
	}
	if (data[j] == '$' && data[j + 1] == '?')
		return (teste_code());

	return (ft_strdup("-1"));
}

char	*get_key(char *ptr, int j)
{
	int		i;
	char	*key;
	
	i = 0;
	while(ptr[j + 1] && ptr[j] != 32)
	{
		i++;
		j++;
	}
	key = calloc(sizeof(char *), i + 1);
	j -= i;
	i = -1;
	while(ptr[j + 1] && ptr[j] != 32)
		key[++i] = ptr[j++];
	key[++i] = '\0';
	return (key); 
}

char	*refresh_value(char *s1, char *s2, int j, int size)
{
	int 	i;
	int		x;
	char	*dst;

	i = -1;
	x = 0;
	dst = calloc(sizeof(char *), (ft_strlen(s1)+ ft_strlen(s2) + 1) - size );
	while (++i < j)
		dst[i] = s1[i];
	while (s2[x])
		dst[i++] = s2[x++];
	j += (size + 1);
	while(s1[j])
		dst[i++] = s1[j++];
	dst[i] = '\0';
	if (s2)
		free(s2);
	return (dst);
}

void	expantion(t_config *data, t_node *env)
{
	int 	i;
	int 	j;
	char	*key;
	char	*value;
	
	i = -1;
	while (data->tokens[++i])
	{
		if (data->tokens[i][0] == DOUBLE_QUOTE || data->tokens[i][0] == SIMPLE_QUOTE)
		{
			j = -1;
			while (data->tokens[i][++j])
			{
				if (data->tokens[i][j] == '$')
				{
					key = get_key(data->tokens[i], j + 1);
					value = search_expansion(data->tokens[i], env, key, j);
					value = refresh_value(data->tokens[i], value, j, ft_strlen(key));
					free(data->tokens[i]);
					data->tokens[i] = ft_strdup(value);
					free(value);
					free(key);
				}
			}
		}
	}
}
