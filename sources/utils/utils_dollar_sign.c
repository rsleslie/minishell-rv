/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:31:09 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/24 18:27:03 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strdup_empty(char *dst, char *exec)
{
	size_t	i;

	i = 0;
	while(i < ft_strlen(exec))
	{
		if (exec[i] == '$' && (exec[i + 1] == SIMPLE_QUOTE || exec[i - 1] == SIMPLE_QUOTE))
		{
			free(dst);
			return (exec);
		}
		if (exec[i] == DOUBLE_QUOTE)
			dst[i] = exec[i];
		else
			dst[i] = 32;
		i++;		
	}
	dst[i] = '\0';
	// free(exec);
	// exec = ft_strdup(dst);
	return (dst);
}

char	*search_var_quotes(t_node *list, char *exec, char *key)
{
	char	*cp;
	t_node	*aux;
	char	*new_cmd;
	
	cp = remove_quotes(key);
	aux = list;
	while (aux != NULL)
	{
		if (search_env(cp, aux->variable) == 0)
		{
			new_cmd = (char *)malloc(sizeof(char) *
				(ft_strlen(aux->value) + ft_strlen(exec)) - (ft_strlen(cp)));
			new_cmd = strdup_quotes(new_cmd, exec, aux->value);
			free(cp);
			return (new_cmd);
		}
		aux = aux->next;
	}
	new_cmd = (char *)malloc(sizeof(char) * ft_strlen(exec));
	strdup_empty(new_cmd, exec);
	free(cp);
	return (new_cmd);
}

// char	*search_expansion(t_node *list, char *key)
// {
// 	t_node	*aux;

// 	aux = list;
// 	while (aux != NULL)
// 	{
// 		if (search_env(key, aux->variable) == 0)
// 			return (ft_strdup(aux->value));
// 		aux = aux->next;
// 	}
// 	return (ft_strdup("-1"));
// }

// char	*update_value(char *value, char *ptr, int size, int j)
// {
// 	int		i;
// 	int		x;
// 	char	*update_ptr;
	
// 	i = -1;
// 	x = 0;
// 	update_ptr = calloc(sizeof(char *), size - ft_strlen(value) + ft_strlen(ptr) + 1);
// 	while (++i < j)
// 	{
// 		update_ptr[i] = ptr[x];
// 		x++;
// 	}
// 	j = -1;
// 	x += size;
// 	while (value[++j])
// 		update_ptr[i++] = value[j];
// 	while(ptr[x])
// 	{
// 		update_ptr[i] = ptr[x];
// 		x++;
// 		i++;
// 	}
// 	update_ptr[i] = '\0';
// 	return (update_ptr);
// }

void	dollar_quotes(t_node *env, t_exec *exec, int size)
{
	int i;
	char	*new;
	
	i = 0;
	if (exec->cmd[size][i] == DOUBLE_QUOTE)
	{
		while(exec->cmd[size][i])
		{
			if ((exec->cmd[size][i] == '$' && exec->cmd[size][i - 1] == SIMPLE_QUOTE && exec->cmd[size][i + 1] == SIMPLE_QUOTE)
				|| (exec->cmd[size][i] == '$' && exec->cmd[size][i - 1] == DOUBLE_QUOTE && exec->cmd[size][i + 1] == DOUBLE_QUOTE))
				break ;
			else if (exec->cmd[size][i] == '$' && exec->cmd[size][i + 1] != '?' && exec->cmd[size][i + 1] != 32)
			{
				new = search_var_quotes(env, exec->cmd[size], &exec->cmd[size][i + 1]);
				printf("->%s\n", new);
				free(exec->cmd);
				exec->cmd[size] = ft_strdup(new);
				free(new);
			}
			i++;
		}
	}
}

char *remove_quotes(char *str)
{
	size_t 	i;
	char	*cp;
	
	i = 0;
	cp = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (i < (ft_strlen(str) - 1))
	{
		cp[i] = str[i];
		i++;
	}
	cp[i] = '\0';
	return(cp);
}

int	ft_len_dollar(char *str)
{
	int i;

	i = 0;
	while (str[i] != '$')
		i++;
	return (i);		
}

char	*strdup_quotes(char *dst, char *exec, char *value)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(i < (ft_len_dollar(exec)))
	{
		dst[i] = exec[i];
		i++;		
	}
	while (value[j])
	{
		dst[i] = value[j];
		i++;
		j++;
	}
	dst[i++] = exec[0];
	dst[i] = '\0';
	return (dst);
}
