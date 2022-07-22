# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 11:20:52 by yait-iaz          #+#    #+#              #
#    Updated: 2022/07/21 17:37:56 by Ma3ert           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = builtins/builtins_utils.c builtins/builtins.c builtins/env.c  builtins/env_tools.c\
	builtins/export.c builtins/ft_unset.c execution/execute_command.c execution/execute_utils_2.c \
	execution/execute_utils.c execution/execute.c expande/expander.c lexer/lexer.c lexer/operator.c \
	lexer/quote.c utils/error.c utils/extra_utils.c utils/ft_itoa.c \
	utils/ft_last.c utils/ft_split.c utils/ft_strdup.c utils/ft_strlcpy.c \
	utils/ft_strtrim.c utils/tools.c utils/utils.c builtins/exit.c utils/ft_atoi.c execution/handle_signals.c main.c \
	rigor_gnl/get_next_line.c rigor_gnl/get_next_line_utils.c execution/execute_command_utils.c utils/free_funcs.c \
	execution/execute_utils_3.c execution/char_list.c execution/cmd.c lexer/heredoc.c lexer/print.c builtins/export_utils.c \
	utils/ft_strjoin_ad.c

OBJ = $(SRC:.c=.o)

NAME = minishell

HEADERS = ./headers/minishell.h ./headers/builtins.h ./headers/struct.h

INCLUDES= -I/goinfre/$(USER)/homebrew/opt/readline/include

READLINE= -lreadline -L/goinfre/$(USER)/homebrew/opt/readline/lib

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(READLINE)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean allsdf
