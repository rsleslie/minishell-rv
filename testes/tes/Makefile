# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 13:38:17 by rleslie-          #+#    #+#              #
#    Updated: 2023/05/10 14:21:32 by rleslie-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell
SRC= main.c    				\
	../../sources/check/error.c  \
	../../sources/utils/free.c  \
	../../sources/utils/builtins_utils.c  \
	../../sources/utils/lexer_utils.c  \
	../../sources/utils/op_builtins.c  \
	../../sources/utils/op_redirect.c  \
	../../sources/linkedlist/createlist.c \
	../../sources/lexer/ft_lexer.c \
	../../sources/parser/ft_parser.c \
	../../sources/built-ins/ft_unset.c \
	../../sources/built-ins/ft_export.c \
	../../sources/built-ins/ft_cd.c \
	../../sources/built-ins/ft_echo.c \
	../../sources/built-ins/ft_env.c \
	../../sources/built-ins/ft_pwd.c \
	../../sources/handle/handle_path.c \
	../../sources/signals/signals.c \
	
OBJ= $(.c=.o)
CC= cc
RL= -lreadline
FLAG= -Wall -Wextra -Werror -g -lcurses
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