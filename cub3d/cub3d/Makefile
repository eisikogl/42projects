NAME	= cube3d

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra

SRCS	=	./srcs/exit_func.c \
			./srcs/init_func.c \
			./srcs/input_control_funcs.c \
			./srcs/input_control.c \
			./srcs/line_drawing.c \
			./srcs/main.c \
			./srcs/map_drawing.c \
			./srcs/map_utils.c \
			./srcs/parse_map.c \
			./srcs/parse.c \
			./srcs/pixel_drawing.c \
			./srcs/raycaster_functions.c \
			./srcs/raycaster.c \
			./srcs/rendering_functions.c \
			./srcs/utils.c \
			./srcs/utils2.c \
			./srcs/get_next_line_utils.c \
			./srcs/get_next_line.c \
			

OBJS	= $(SRCS:%.c=%.o)

$(NAME):$(OBJS)
		make -C ./libs/mlx
		mv ./libs/mlx/libmlx.a ./libmlx.a

		make -C ./libs/Libft
		mv ./libs/Libft/libft.a ./libft.a

		$(CC) $(CFLAGS) $(SRCS) -framework OpenGL -framework AppKit libmlx.a libft.a -o $(NAME)

all: 	$(NAME)

clean:
		make -C ./libs/mlx clean
		rm -rf */*.o libmlx.a cube3d.o

		make -C ./libs/Libft fclean
		rm -rf */*.o libft.a

		
fclean: clean
		rm -rf cube3d

re: 	fclean all

.PHONY: all clean fclean re
