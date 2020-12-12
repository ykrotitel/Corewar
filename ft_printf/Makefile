# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/26 16:06:00 by fmallist          #+#    #+#              #
#    Updated: 2019/12/26 12:55:12 by fmallist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFTA = libft.a
SRCS = buffer_mgmt.c ft_printf.c fill_options.c itoa_base_buff.c handle_overflow_buffer.c get_integer.c handle_integers.c \
		itoa_base_extra_funcs.c itoa_base_buff_u.c handle_unsigned.c get_unsigned.c ftoa.c ftoa_base_buff.c \
		printing_floats.c long_arithmetics.c handle_octals.c handle_hexdecimals.c handle_bighex.c \
		get_specifiers.c handle_floats.c handle_csp.c fill_ldbl_arrays.c fill_float_arrays.c \
		hanlde_uhex.c handle_ubighex.c handle_uoctal.c utoa_base_buff_ox.c handle_strings.c bonuses.c
OBJ = $(SRCS:.c=.o)
LIBDIR = libft/
LIBNAME = libft/libft.a
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(OBJ): %.o: %.c
	@gcc -c $(CFLAGS) $< -o $@

$(NAME): $(OBJ)
	@make -C $(LIBDIR)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJ)

clean:
	@/bin/rm -f $(OBJ)
	@make -C $(LIBDIR) clean
	@echo OBJECTS FILES HAS BEEN DELETED.

test:
	@gcc *.c -L libft -lft -o test

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBDIR) fclean
	@echo OBJECT FILES AND EXECUTABLE HAS BEEN DELETED.

re: fclean all
