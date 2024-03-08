NAME	= philo

cc		= gcc

SRCS	= main.c

SRCS	+= coloroutput.c

SRCS	+= utils.c

SRCS	+= threads.c 

SRCS	+= initialize.c

SRCS	+= error_maneger.c

SRCS	+= errorhandling.c

OBJS	= $(SRCS:.c=.o)

RM = rm -rf

FLAGS	= -Wall -Wextra -Werror 

TFLAG = -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(TFLAG) $(FLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)
	
fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re