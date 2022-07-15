# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 11:20:52 by yait-iaz          #+#    #+#              #
#    Updated: 2022/07/15 18:27:31 by mmoumni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = builtins/builtins_utils.c builtins/builtins.c builtins/env.c  builtins/env_tools.c\
	builtins/export.c builtins/ft_unset.c execution/execute_command.c execution/execute_utils_2.c \
	execution/execute_utils.c execution/execute.c expande/expander.c lexer/lexer.c lexer/operator.c \
	lexer/quote.c lexer/tokenize.c utils/error.c utils/extra_utils.c utils/ft_itoa.c \
	utils/ft_last.c utils/ft_split.c utils/ft_strdup.c utils/ft_strlcpy.c utils/ft_strstr.c \
	utils/ft_strtrim.c utils/tools.c utils/utils.c main.c
	

OBJ = $(SRC:.c=.o)

NAME = minishell

HEADERS = ./headers/minishell.h ./headers/builtins.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all