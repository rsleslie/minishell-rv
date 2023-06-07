/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:35:40 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/07 18:49:34 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	aux_quotes(char *ptr, t_config *data, t_lexer *counter)
// {
// 	char	c;

// 	if ((data->str[counter->i] == DOUBLE_QUOTE
// 			|| data->str[counter->i] == SIMPLE_QUOTE))
// 	{
// 		c = data->str[counter->i];
// 		ptr[counter->j++] = 27;
// 		ptr[counter->j] = c;
// 		counter->j++;
// 		counter->i++;
// 		if (!data->str[counter->i])
// 			return (1);
// 		while (data->str[counter->i] && data->str[counter->i] != c)
// 			ptr[counter->j++] = data->str[counter->i++];
// 	}
// 	return (0);
// }

// void	aux_redirect(char *ptr, t_config *data, t_lexer *counter)
// {
// 	char	c;

// 	if ((op_redirect(data->str[counter->i]) != 0
// 			&& op_redirect(data->str[counter->i]) != 4))
// 	{
// 		c = data->str[counter->i];
// 		counter->i++;
// 		ptr[counter->j] = 27;
// 		counter->j++;
// 		ptr[counter->j] = c;
// 		counter->j++;
// 		if (data->str[counter->i] == c)
// 		{
// 			ptr[counter->j] = data->str[counter->i];
// 			counter->j++;
// 			counter->i++;
// 		}
// 		ptr[counter->j] = 27;
// 		counter->j++;
// 	}
// }

// int	norminette_aux_lexer(char *ptr, t_config *data, t_lexer *counter)
// {
// 	if (!data->str[counter->i])
// 		return (1);
// 	ptr[counter->j] = data->str[counter->i];
// 	counter->j++;
// 	counter->i++;
// 	if (!data->str[counter->i])
// 		return (1);
// 	return (0);
// }

// void	aux_lexer(char *ptr, t_config *data, t_lexer *counter, int size)
// {
// 	while (data->str[counter->i] || counter->j <= size)
// 	{
// 		if (aux_quotes(ptr, data, counter) == 1)
// 			break ;
// 		aux_redirect(ptr, data, counter);
// 		if (data->str[counter->i] == 32
// 			|| (data->str[counter->i] >= 9 && data->str[counter->i] <= 13))
// 		{
// 			ptr[counter->j] = 27;
// 			counter->j++;
// 			counter->i++;
// 			if (!data->str[counter->i])
// 				break ;
// 		}
// 		else
// 		{
// 			if (norminette_aux_lexer(ptr, data, counter) == 1)
// 				break ;
// 		}
// 	}
// 	is_null(data->tokens);
// 	data->tokens = ft_split(ptr, 27);
// 	free(ptr);
// }

// void	ft_lexer(t_config *data)
// {
// 	t_lexer	counter;
// 	char	*ptr;
// 	int		size;

// 	size = ft_strlen(data->str) + ((counter_redirect(data->str) + 2) * 2);
// 	counter.i = 0;
// 	counter.j = 0;
// 	ptr = calloc(sizeof(char), size + 1);
// 	ptr[size] = '\0';
// 	aux_lexer(ptr, data, &counter, size);
// }


//----------------------------------------------------------------------------------------------------------


// int	aux_quotes(char *ptr, t_config *data, t_lexer *counter)
// {
// 	char	c;

// 	if ((data->str[counter->i] == DOUBLE_QUOTE
// 			|| data->str[counter->i] == SIMPLE_QUOTE))
// 	{
// 		c = data->str[counter->i];
// 		ptr[counter->j++] = 27;
// 		ptr[counter->j] = c;
// 		counter->j++;
// 		counter->i++;
// 		if (!data->str[counter->i])
// 			return (1);
// 		while (data->str[counter->i] && data->str[counter->i] != c)
// 			ptr[counter->j++] = data->str[counter->i++];
// 	}
// 	return (0);
// }

// void	aux_redirect(char *ptr, t_config *data, t_lexer *counter)
// {
// 	char	c;

// 	if ((op_redirect(data->str[counter->i]) != 0
// 			&& op_redirect(data->str[counter->i]) != 4))
// 	{
// 		c = data->str[counter->i];
// 		counter->i++;
// 		ptr[counter->j] = 27;
// 		counter->j++;
// 		ptr[counter->j] = c;
// 		counter->j++;
// 		if (data->str[counter->i] == c)
// 		{
// 			ptr[counter->j] = data->str[counter->i];
// 			counter->j++;
// 			counter->i++;
// 		}
// 		ptr[counter->j] = 27;
// 		counter->j++;
// 	}
// }

// int	norminette_aux_lexer(char *ptr, t_config *data, t_lexer *counter)
// {
// 	if (!data->str[counter->i])
// 		return (1);
// 	ptr[counter->j] = data->str[counter->i];
// 	counter->j++;
// 	counter->i++;
// 	if (!data->str[counter->i])
// 		return (1);
// 	return (0);
// }

// void	aux_lexer(char *ptr, t_config *data, t_lexer *counter, int size)
// {
// 	while (data->str[counter->i] || counter->j <= size)
// 	{
// 		if (aux_quotes(ptr, data, counter) == 1)
// 			break ;
// 		aux_redirect(ptr, data, counter);
// 		if (data->str[counter->i] == 32
// 			|| (data->str[counter->i] >= 9 && data->str[counter->i] <= 13))
// 		{
// 			ptr[counter->j] = 27;
// 			counter->j++;
// 			counter->i++;
// 			if (!data->str[counter->i])
// 				break ;
// 		}
// 		else
// 		{
// 			if (norminette_aux_lexer(ptr, data, counter) == 1)
// 				break ;
// 		}
// 	}
// 	is_null(data->tokens);
// 	data->tokens = ft_split(ptr, 27);
// 	free(ptr);
// }

// int	op_redirect(char c)
// {
// 	if (ft_strcmp(c, '<') == 0)
// 		return (1);
// 	else if (ft_strcmp(c, '>') == 0)
// 		return (2);
// 	else if (ft_strcmp(c, '|') == 0)
// 		return (3);
// 	else if (ft_strcmp(c, '$') == 0)
// 		return (4);
// 	return (0);
// }

// int	counter_redirect(char *s)
// {
// 	int	i;
// 	int	len;
// 	int	c;

// 	i = 0;
// 	len = 0;
// 	while (s[i])
// 	{
// 		if (op_redirect(s[i]) != 0 && op_redirect(s[i]) != 4)
// 		{
// 			c = s[i];
// 			len++;
// 			if (c == s[i + 1])
// 				i++;
// 		}
// 		i++;
// 	}
// 	return (len);
// }

// void	ft_lexer(t_config *data)
// {
// 	t_lexer	counter;
// 	char	*ptr;
// 	int		size;

// 	size = ft_strlen(data->str) + ((counter_redirect(data->str) + 2) * 2);
// 	counter.i = 0;
// 	counter.j = 0;
// 	ptr = calloc(sizeof(char), size + 1);
// 	ptr[size] = '\0';
// 	aux_lexer(ptr, data, &counter, size);
// }

int aux_quotes(char *ptr, t_config *data, t_lexer *counter) {
    char c;

    if ((data->str[counter->i] == DOUBLE_QUOTE || data->str[counter->i] == SIMPLE_QUOTE))
	{
        c = data->str[counter->i];
        ptr[counter->j++] = c;
        counter->i++;
        if (!data->str[counter->i])
            return 1;
        while (data->str[counter->i] && data->str[counter->i] != c)
            ptr[counter->j++] = data->str[counter->i++];
        ptr[counter->j++] = c;
		counter->i++;
    }
    return 0;
}

void aux_redirect(char *ptr, t_config *data, t_lexer *counter)
{
    char c;

    if ((op_redirect(data->str[counter->i]) != 0 && op_redirect(data->str[counter->i]) != 4))
	{
        c = data->str[counter->i];
        counter->i++;
        ptr[counter->j++] = c;
        if (data->str[counter->i] == c)
            ptr[counter->j++] = data->str[counter->i++];
        ptr[counter->j++] = 27;
    }
}

int norminette_aux_lexer(char *ptr, t_config *data, t_lexer *counter)
{
    if (!data->str[counter->i])
        return 1;
    ptr[counter->j++] = data->str[counter->i++];
    if (!data->str[counter->i])
        return 1;
    return 0;
}

void aux_lexer(char *ptr, t_config *data, t_lexer *counter, int size)
{
    while (data->str[counter->i] || counter->j <= size)
	{
        aux_redirect(ptr, data, counter);
        if (aux_quotes(ptr, data, counter) == 1)
            break;
        else if (data->str[counter->i] == 32 || (data->str[counter->i] >= 9 && data->str[counter->i] <= 13))
		{
            ptr[counter->j++] = 27;
            counter->i++;
            if (!data->str[counter->i])
                break;
        }
		else
		{
            if (norminette_aux_lexer(ptr, data, counter) == 1)
                break;
        }
    }
    is_null(data->tokens);
    data->tokens = ft_split(ptr, 27);
    free(ptr);
}

void	ft_lexer(t_config *data)
{
	t_lexer	counter;
	char	*ptr;
	int		size;

	size = ft_strlen(data->str) + ((counter_redirect(data->str) + 2) * 2);
	counter.i = 0;
	counter.j = 0;
	ptr = calloc(sizeof(char), size + 1);
	ptr[size] = '\0';
	aux_lexer(ptr, data, &counter, size);
}
