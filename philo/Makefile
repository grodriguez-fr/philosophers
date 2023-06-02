# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 11:21:47 by gurodrig          #+#    #+#              #
#    Updated: 2023/06/02 15:47:03 by gurodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS	= src/main.c \
	  src/utils.c \
	  src/init.c \
	  src/thread.c \
	  src/routine.c \
	  src/exit.c
INCLUDE_FOLDER	= headers
HEADERS	= headers/philosophers.h
OBJ_FOLDER = obj
OBJS	= $(addprefix $(OBJ_FOLDER)/, $(notdir $(SRCS:.c=.o)))
NAME	= philo

CC	= cc
CFLAGS	= -Wall -Wextra -Werror
LIBS    =  -lpthread

$(OBJ_FOLDER)/%.o: src/%.c $(HEADERS) Makefile
	${CC} -I$(INCLUDE_FOLDER) -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) Makefile
	${CC} $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean :
	rm -rf $(OBJ_FOLDER)/*.o

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
