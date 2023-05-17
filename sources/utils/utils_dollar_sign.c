/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:31:09 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/17 14:40:31 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	strdup_empty(char *dst, char *exec)
{
	size_t	i;

	i = 0;
	while(i < ft_strlen(exec))
	{
		if (exec[i] == '$' && (exec[i + 1] == SIMPLE_QUOTE || exec[i - 1] == SIMPLE_QUOTE))
		{
			free(dst);
			return ;
		}
		if (exec[i] == DOUBLE_QUOTE)
			dst[i] = exec[i];
		else
			dst[i] = 32;
		i++;		
	}
	dst[i] = '\0';
	free(exec);
	exec = ft_strdup(dst);
	free(dst);
}

int	search_var_quotes(t_node *list, char *exec, char *key)
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
				(ft_strlen(aux->value) + ft_len_dollar(exec)) + 1);
			new_cmd = strdup_quotes(new_cmd, exec, aux->value);
			free(exec);
			exec = ft_strdup(new_cmd);
			free(new_cmd);
			free(cp);
			return (1);
		}
		aux = aux->next;
	}
	new_cmd = (char *)malloc(sizeof(char) * ft_strlen(exec));
	strdup_empty(new_cmd, exec);
	free(cp);
	return (0);
}

void	dollar_quotes(t_node *env, char *str)
{
	int i;

	i = 0;
	if (str[i] == DOUBLE_QUOTE)
	{
		while(str[i])
		{
			if (str[i] == '$' && str[i - 1] == SIMPLE_QUOTE && str[i + 1] == SIMPLE_QUOTE)
				break ;
			else if (str[i] == '$')
				search_var_quotes(env, str, &str[i + 1]);
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
	while(i < ft_len_dollar(exec))
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
	dst[i++] = 34;
	dst[i] = '\0';
	return (dst);
}
