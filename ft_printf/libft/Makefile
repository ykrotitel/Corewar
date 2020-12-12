# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 20:24:18 by fmallist          #+#    #+#              #
#    Updated: 2020/12/11 20:03:46 by acarlett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

HEADER = libft.h

SRC = 	ft_isspace.c			ft_lstreverse.c			ft_putchar.c			ft_strcapitalize.c		ft_striteri.c			ft_strnew.c \
		ft_itoa.c				ft_lstsize.c			ft_putchar_fd.c			ft_strcat.c				ft_strjoin.c			ft_strnstr.c \
		ft_memalloc.c           ft_putendl.c            ft_strchr.c             ft_strlcat.c            ft_strrchr.c			ft_itoa_base.c ft_numlen.c\
		ft_atoi.c               ft_lstadd.c             ft_memccpy.c            ft_putendl_fd.c         ft_strclr.c             ft_strlen.c             ft_strsplit.c \
		ft_bzero.c              ft_lstat.c              ft_memchr.c             ft_putnbr.c             ft_strcmp.c             ft_strmap.c             ft_strstr.c \
		ft_isalnum.c            ft_lstdel.c             ft_memcmp.c             ft_putnbr_fd.c          ft_strcpy.c             ft_strmapi.c            ft_strsub.c \
		ft_isalpha.c            ft_lstdelone.c          ft_memcpy.c             ft_putstr.c             ft_strdel.c             ft_strncat.c            ft_strtrim.c \
		ft_isascii.c            ft_lstiter.c            ft_memdel.c             ft_putstr_fd.c          ft_strdup.c             ft_strncmp.c            ft_tolower.c \
		ft_isdigit.c            ft_lstmap.c             ft_memmove.c            ft_sort_int_tab.c       ft_strequ.c             ft_strncpy.c            ft_toupper.c \
		ft_isprint.c            ft_lstnew.c             ft_memset.c             ft_str_is_printable.c   ft_striter.c            ft_strnequ.c 			get_next_line.c \

CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SRC:.c=.o)

all:$(NAME)

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@echo !!!LIBRARY IS READY!!!

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	@/bin/rm -f $(OBJECTS)
	@echo !!!OBJECT FILES BEEN DELETED!!!

fclean: clean
	/bin/rm -f $(NAME)
	@echo !!! libft.a BEEN DELETED!!!

re: fclean all
