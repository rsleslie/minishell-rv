/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:43:34 by coder             #+#    #+#             */
/*   Updated: 2023/05/23 13:03:45 by rleslie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>

int		ft_lurkstr(const char *s, int c);
int		ft_tab_len(char **str);
int		ft_isnum(char *str);
int		ft_counter(char const *s, char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_calloc(size_t nitems, size_t size);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
int		ft_putnbr(int n);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_format(va_list args, char format, int len);
int		ft_putnbr_u(unsigned int n);
int		ft_hex(unsigned int n, int j, int x, int i);
int		ft_ptr(unsigned long n, int j);
int		ft_printf(const char *ptr, ...);
void	ft_putchar_ptr(char *div, int x);
int		ft_key_parser(char *key);
int		ft_strcs(const char *s, int c);
int		ft_strcmp(char c, char key);

#endif
