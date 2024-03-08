NAME 	= push_swap

CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror 

RM 		= rm -rf

SRCS = $(wildcard srcs/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		make -C ./libarys/libft
		mv ./libarys/libft/libft.a ./libft.a

		make -C ./libarys/ft_printf
		mv ./libarys/ft_printf/libftprintf.a ./libftprintf.a
	$(CC) $(CFLAGS) $(OBJS) libft.a libftprintf.a -o $(NAME)

clean:
	make -C ./libarys/libft fclean
	rm -rf */*.o libft.a

	make -C ./libarys/ft_printf fclean
	rm -rf */*.o libftprintf.a
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:all clean fclean re