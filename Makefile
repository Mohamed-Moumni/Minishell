# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yait-iaz <yait-iaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 11:20:52 by yait-iaz          #+#    #+#              #
#    Updated: 2022/05/29 11:21:26 by yait-iaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 
OBJ = $(SRC:.c=.o)
NAME = minishell
HEADER = minishell.h

CC = gcc

FLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all