# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumni <mmoumni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 11:20:52 by yait-iaz          #+#    #+#              #
#    Updated: 2022/06/25 16:12:20 by mmoumni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = builtins/builtins_utils.c builtins/builtins.c builtins/export.c \
		lexer/lexer.c lexer/operator.c lexer/quote.c lexer/tokenize.c \
		utils/extra_utils.c utils/ft_split.c utils/tools.c utils/ft_last.c \
		utils/ft_strlcpy.c utils/utils.c main.c

OBJ = builtins/builtins_utils.o builtins/builtins.o builtins/export.o \
		lexer/lexer.o lexer/operator.o lexer/quote.o lexer/tokenize.o \
		utils/extra_utils.o utils/ft_split.o utils/tools.o utils/ft_last.o \
		utils/ft_strlcpy.o utils/utils.o main.o
	
OBJ_COM =  builtins.o builtins_utils.o export.o extra_utils.o ft_last.o ft_split.o \
		ft_strlcpy.o lexer.o main.o operator.o quote.o tokenize.o tools.o utils.o

NAME = minishell

HEADERS = ./headers/minishell.h ./headers/builtins.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ_COM) -lreadline -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(OBJ_COM)

fclean: clean
	rm -f $(NAME)

re: fclean all