# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 13:38:17 by rleslie-          #+#    #+#              #
#    Updated: 2023/04/25 15:59:18 by rleslie-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell
SRC= minishell.c    				\
	./sources/check/error.c  \
	./sources/linkedlist/createlist.c \
	./sources/built-ins/ft_env.c \
	./sources/built-ins/ft_unset.c \
	./sources/built-ins/ft_export.c \
	./sources/built-ins/ft_pwd.c \
	./sources/built-ins/ft_cd.c \
	./sources/built-ins/ft_echo.c \
	./sources/lexer/ft_lexer.c \
	./sources/parser/ft_parser.c \
	./sources/utils/builtins_utils.c \
	./sources/utils/free.c  \
		
OBJ= $(.c=.o)
CC= cc
RL= -lreadline
FLAG= -Wall -Wextra -Werror
LIBFT= ./libft/libft.a

all: $(NAME) 

$(NAME): $(OBJ)
		@make -C libft
		$(CC) $(SRC) $(LIBFT) $(FLAG) $(RL) -o $(NAME)

clean:
		rm -f $(OBJ)
		@make fclean -C libft

fclean: clean
		rm -rf $(NAME)
		
re: fclean all