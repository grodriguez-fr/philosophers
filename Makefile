SRCS	= src/main.c \
	  src/utils.c \
	  src/utils_2.c \
	  src/matrix_functions.c \
	  src/camera_basic.c \
	  src/camera_matrix.c \
	  src/matrix_operations.c \
	  src/matrix_base.c \
	  src/draw.c \
	  src/draw_line.c \
	  src/key.c \
	  src/main_functions.c \
	  src/parsing.c
MLX_PATH	= minilibx-linux
INCLUDE_FOLDER	= includes
MLX_INC		= -I$(MLX_PATH) -O3
LIBS_MLX	= -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

HEADERS	= includes/fdf.h includes/get_next_line.h includes/libft.h

OBJ_FOLDER = obj
OBJS	= $(addprefix $(OBJ_FOLDER)/, $(notdir $(SRCS:.c=.o)))

NAME	= fdf 

CC	= cc
CFLAGS	= -Wall -Wextra -Werror

LIBFT	= libft/libft.a

$(OBJ_FOLDER)/%.o: src/%.c $(HEADERS)
	${CC} -I$(INCLUDE_FOLDER) $(MLX_INC) -c $< -o $@ $(CFLAGS)


all: $(NAME)


$(NAME): $(OBJS) $(HEADERS) $(LIBFT) libft/* minilibx-linux/libmlx_Linux.a Makefile
	${CC} $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBS_MLX) $(MLX_INC)

minilibx-linux/libmlx_Linux.a:
	make -sC $(MLX_PATH)

$(LIBFT): libft/*.c libft/*.h
	make -C libft

clean :
	rm -rf $(OBJ_FOLDER)/*.o
	make clean -C libft
	make clean -C $(MLX_PATH)

fclean : clean
	rm -f $(LIBFT)	
	rm -f $(NAME)
	rm -f $(MLX_LIB)

re : fclean all

.PHONY: all clean fclean re mlx
