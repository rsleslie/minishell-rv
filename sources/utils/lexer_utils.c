/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:02:35 by rleslie-          #+#    #+#             */
/*   Updated: 2023/05/03 18:34:57 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	counter_redirect(char *s)
{
	int i;
	int len;
	int c;
	
	i = 0;
	len = 0;
	while(s[i])
	{
		if (op_redirect(s[i]) != 0 && op_redirect(s[i]) != 4)
		{
			c = s[i];
			len++;
			if (c == s[i + 1])
				i++;
		}
		i++;
	}
	return (len);
}
