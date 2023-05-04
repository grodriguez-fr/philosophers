SRCS	= src/main.c \
	  src/utils.c
INCLUDE_FOLDER	= headers

HEADERS	= headers/philosophers.h

OBJ_FOLDER = obj
OBJS	= $(addprefix $(OBJ_FOLDER)/, $(notdir $(SRCS:.c=.o)))

NAME	= philo

CC	= cc
CFLAGS	= -Wall -Wextra -Werror

$(OBJ_FOLDER)/%.o: src/%.c $(HEADERS)
	${CC} -I$(INCLUDE_FOLDER) -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) Makefile
	${CC} $(CFLAGS) -o $(NAME) $(OBJS)

clean :
	rm -rf $(OBJ_FOLDER)/*.o

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re mlx
