# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleslie- <rleslie-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 13:38:17 by rleslie-          #+#    #+#              #
#    Updated: 2023/06/12 11:32:12 by rleslie-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell
SRC= main.c    											\
	../../sources/check/error.c  						\
	../../sources/check/error_utils.c  					\
	../../sources/utils/free.c  						\
	../../sources/utils/builtins_utils.c  				\
	../../sources/utils/lexer_utils.c  					\
	../../sources/utils/op_builtins.c  					\
	../../sources/utils/op_redirect.c 				 	\
	../../sources/utils/utils_dollar_sign.c  			\
	../../sources/utils/export_utils.c  				\
	../../sources/linkedlist/createlist.c 				\
	../../sources/linkedlist/create_list_exec.c 		\
	../../sources/lexer/ft_lexer.c 						\
	../../sources/lexer/error_handling.c 				\
	../../sources/lexer/error_norm.c 					\
	../../sources/lexer/tokens.c 						\
	../../sources/parser/ft_parser.c 					\
	../../sources/parser/unquote.c 						\
	../../sources/parser/dollar_sign.c 					\
	../../sources/parser/dollar_utils.c 				\
	../../sources/parser/utils_parser.c 				\
	../../sources/built-ins/ft_unset.c 					\
	../../sources/built-ins/builtins.c 					\
	../../sources/built-ins/ft_export.c 				\
	../../sources/built-ins/ft_cd.c 					\
	../../sources/built-ins/ft_echo.c 					\
	../../sources/built-ins/ft_env.c 					\
	../../sources/built-ins/ft_pwd.c 					\
	../../sources/handle/handle_path.c 					\
	../../sources/signals/signals.c 					\
	../../sources/exec/executor.c  						\
	../../sources/exec/init_exec.c  					\
	../../sources/exec/pipex.c  						\
	../../sources/exec/pipeless.c  						\
	../../sources/exec/utils_executor.c  				\
	../../sources/exec/utils_exec.c  					\
	../../sources/exec/redirect.c 		  				\
	../../sources/exec/executor_pipe.c  				\
	../../sources/exec/validation.c  					\
	../../sources/heredoc/heredoc.c  					\
	
	
OBJ= $(.c=.o)
CC= cc
RL= -lreadline
FLAG= -Wall -Wextra -Werror -g3 -g -lcurses
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
