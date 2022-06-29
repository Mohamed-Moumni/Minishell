# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 11:20:52 by yait-iaz          #+#    #+#              #
#    Updated: 2022/06/29 13:49:11 by yait-iaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = builtins/builtins_utils.c builtins/builtins.c builtins/export.c \
		lexer/lexer.c lexer/operator.c lexer/quote.c lexer/tokenize.c \
		utils/extra_utils.c utils/ft_split.c utils/tools.c utils/ft_last.c \
		utils/ft_strlcpy.c utils/utils.c main.c execution/execute.c \
		execution/execute_utils.c utils/ft_strtrim.c
		

OBJ = $(SRC:.c=.o)

NAME = minishell

HEADERS = ./headers/minishell.h ./headers/builtins.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline -L$(shell brew --prefix readline)/lib

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all