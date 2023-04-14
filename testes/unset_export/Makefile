# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 13:38:17 by rleslie-          #+#    #+#              #
#    Updated: 2023/04/14 14:31:42 by rleslie-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell
SRC= main.c    				\
	../../sources/check/error.c  \
	../../sources/utils/free.c  \
	../../sources/linkedlist/createlist.c \
	../../sources/handle/handle_env.c \
	../../sources/built-ins/ft_unset.c \
	../../sources/built-ins/ft_export.c \
	../../sources/built-ins/ft_pwd.c \
	../../sources/handle/handle_export.c \
	../../sources/built-ins/ft_cd.c \
	
OBJ= $(.c=.o)
CC= cc
RL= -lreadline
FLAG= -Wall -Wextra -Werror -g
LIBFT= ../../libft/libft.a

all: $(NAME) 

$(NAME): $(OBJ)
		@make -C ../../libft
		$(CC) $(SRC) $(LIBFT) $(FLAG) $(RL) -o $(NAME)

clean:
		rm -f $(OBJ)
		@make fclean -C ../../libft

fclean: clean
		rm -rf $(NAME)
		
re: fclean all