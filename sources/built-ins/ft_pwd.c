/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:56:33 by rleslie-          #+#    #+#             */
/*   Updated: 2023/06/12 15:09:55 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		g_data.status_code = 0;
		printf("%s\n", buffer);
	}
	else
		printf("error :");
}
