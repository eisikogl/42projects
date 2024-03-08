NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -c

RM = rm -f

AR = ar rcs

SRCS = \
	ft_printf.c \
	ft_printf_utils.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) :  $(OBJS)
	$(CC) $(CFLAGS) $(SRCS)
	$(AR) $(NAME) $(OBJS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re