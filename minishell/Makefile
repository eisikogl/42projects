SRCS			= $(shell find src -type f -name "*.c")
OBJS			= $(SRCS:src/%.c=src/bin/%.o)
ROOT			= $(shell echo $(HOME))


NAME			= minishell
CC				= gcc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -I./libs/readline/include
LDFLAGS			= -L./libs/readline/lib -lreadline
LIBFT			= ./libs/libft/libft.a
INC_FT			= ./libs/libft
INC				= ./inc/
BIN				= ./src/bin/
LIB				= ./libs/.minishell


all : $(LIB) $(LIBFT) $(NAME)

$(LIBFT):
	@make -C ./libs/libft

$(LIB):
	@make -C ./libs

$(BIN):
	@mkdir $(BIN)

$(BIN)%.o: src/%.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_FT) -I$(INC)

$(NAME): $(BIN) $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME) $(LIBFT)

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)
	@$(RM) $(BIN)

ffclean: fclean
	@make fclean -C ./libs/libft

fffclean: ffclean
	@make fclean -C ./libs

re : ffclean all

.PHONY: all clean fclean re