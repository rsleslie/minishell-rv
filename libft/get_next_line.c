/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:21:09 by rleslie-          #+#    #+#             */
/*   Updated: 2023/01/29 14:11:34 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read(int fd, char *rd_static)
{
	char	*buf;
	int		rd_byte;

	buf = (char *)malloc(sizeof(char *) + 1);
	rd_byte = 1;
	while (!ft_strchr(rd_static, '\n') && rd_byte != 0)
	{
		rd_byte = read(fd, buf, 1);
		if (rd_byte == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_byte] = '\0';
		rd_static = ft_strjoin(rd_static, buf);
	}
	free(buf);
	return (rd_static);
}

static char	*ft_new_static(char *rd_static)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (rd_static[i] && rd_static[i] != '\n')
		i++;
	if (!rd_static[i])
	{
		free(rd_static);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(rd_static) - i + 1));
	if (!s)
		return (NULL);
	i++;
	c = 0;
	while (rd_static[i])
		s[c++] = rd_static[i++];
	s[c] = '\0';
	free(rd_static);
	return (s);
}

static char	*ft_get_line(char *rd_static)
{
	int		i;
	char	*line;

	i = 0;
	if (!rd_static[i])
		return (NULL);
	while (rd_static[i] && rd_static[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (rd_static[i] && rd_static[i] != '\n')
	{
		line[i] = rd_static[i];
		i++;
	}
	if (rd_static[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rd_static;
	char		*line;

	if (fd < 0)
		return (NULL);
	rd_static = ft_read(fd, rd_static);
	if (!rd_static)
	{
		free(rd_static);
		return (NULL);
	}
	line = ft_get_line(rd_static);
	rd_static = ft_new_static(rd_static);
	if (!line)
	{
		free(rd_static);
		free(line);
		return (NULL);
	}
	return (line);
}
