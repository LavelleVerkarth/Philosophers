# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lverkart <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 15:28:04 by lverkart          #+#    #+#              #
#    Updated: 2021/06/07 15:28:06 by lverkart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

CC				=	gcc

FLAGS			=	-Wall -Wextra -Werror -pthread

INC				=	-I includes

SRC				=	philo.c		philo_utils.c	philo_parse.c 	philo_pthread.c

OBJ_NAME		=	$(SRC:.c=.o)

OBJECTS_LIST	=	$(patsubst %.c, %.o, $(SRC))

OBJECTS			=	$(addprefix $(OBJ_DIR), $(OBJECTS_LIST))

HEADERS			=	includes/philo.h

SRC_DIR			=	srcs/

OBJ_DIR			=	objs/

all				:	$(NAME)


$(NAME)			:  $(OBJ_DIR) $(OBJECTS) $(HEADERS)
	@$(CC) $(FLAGS) $(INC) $(OBJECTS) -o $(NAME)

$(OBJ_DIR)		:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -o $@ -c $< $(INC)

clean			:
	@rm -rf $(OBJ_DIR)

fclean			:	clean
	@rm -f $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re

