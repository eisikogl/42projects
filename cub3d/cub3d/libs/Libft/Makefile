# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: akalayci <42istanbul.com.tr>               +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2022/01/04 16:07:08 by akalayci          #+#    #+#             #
#   Updated: 2022/01/09 14:42:56 by akalayci         ###   ########.tr       #
#                                                                            #
# ************************************************************************** #

NAME = libft.a

CC = gcc

CFLAG =  -Wall -Werror -Wextra -c

RM = rm -f

AR = ar rc

MAINSRC = \
	./ft_isalpha.c ./ft_isdigit.c ./ft_isalnum.c \
	./ft_isascii.c ./ft_isprint.c ./ft_strlen.c \
	./ft_memset.c ./ft_bzero.c ./ft_memcpy.c \
	./ft_memmove.c ./ft_strlcpy.c ./ft_strlcat.c \
	./ft_toupper.c ./ft_tolower.c ./ft_strchr.c \
	./ft_strrchr.c ./ft_strncmp.c ./ft_memchr.c \
	./ft_memcmp.c ./ft_strnstr.c ./ft_atoi.c \
	./ft_calloc.c ./ft_strdup.c ./ft_substr.c \
	./ft_strjoin.c ./ft_strtrim.c ./ft_split.c \
	./ft_itoa.c ./ft_strmapi.c ./ft_striteri.c \
	./ft_putchar_fd.c ./ft_putstr_fd.c ./ft_putendl_fd.c \
	./ft_putnbr_fd.c

BONUSSRC = \
	./ft_lstnew.c ./ft_lstadd_front.c ./ft_lstlast.c \
	./ft_lstsize.c ./ft_lstadd_back.c ./ft_lstdelone.c \
	./ft_lstclear.c ./ft_lstiter.c ./ft_lstmap.c

MAINOBJ = $(subst .c,.o,$(MAINSRC))
BONUOBJ = $(subst .c,.o,$(BONUSSRC))

all : $(NAME)

$(NAME) :  $(MAINOBJ)
	$(CC) $(CFLAG) $(MAINSRC)
	$(AR) $(NAME) $(MAINOBJ)

clean : 
	$(RM) $(MAINOBJ) $(BONUOBJ)

fclean : clean
	$(RM) $(NAME)

bonus : $(BONUOBJ)

$(BONUOBJ) : $(BONUSSRC)
	$(CC) $(CFLAG) $(BONUSSRC)
	$(AR) $(NAME) $(BONUOBJ)
	
re : fclean all

rebonus : fclean bonus
