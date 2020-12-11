# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 23:17:20 by acarlett          #+#    #+#              #
#    Updated: 2020/12/11 20:25:43 by acarlett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = 
# FLAGS = -Wall -Werror -Wextra

DIR_SRCS =	srcs/corewar

DIR_VIS =	srcs/visual

DIR_INC =	includes

DIR_LIB =	ft_printf/libft

SRCS_CORE =	$(DIR_SRCS)/add_sub.c \
			$(DIR_SRCS)/aff.c \
			$(DIR_SRCS)/and_or_xor.c \
			$(DIR_SRCS)/cycles_to_die_check.c \
			$(DIR_SRCS)/fork.c \
			$(DIR_SRCS)/game.c \
			$(DIR_SRCS)/handle_value.c \
			$(DIR_SRCS)/ld.c \
			$(DIR_SRCS)/live.c \
			$(DIR_SRCS)/main.c \
			$(DIR_SRCS)/op.c \
			$(DIR_SRCS)/parse_arguments.c \
			$(DIR_SRCS)/parse_champions.c \
			$(DIR_SRCS)/st.c \
			$(DIR_SRCS)/print.c \
			$(DIR_SRCS)/zjmp.c

SRCS_VISUAL =	$(DIR_VIS)/init.c \
				$(DIR_VIS)/visual.c \
				$(DIR_VIS)/arena.c \
				$(DIR_VIS)/info_table.c \

INCLUDES =	$(DIR_INC)/corewar.h \
			$(DIR_INC)/corewar_visual.h

OBJECTS = 	$(patsubst %.c.%.o,$(SRCS_CORE), $(SRCS_VISUAL))

NAME = huevina



all: $(NAME)

$(NAME): $(OBJECTS)
	make -C ft_printf/libft
	make -C ft_printf/
	make -C srcs/asm
	gcc $(FLAGS) -o $(NAME) $(SRCS_CORE) $(SRCS_VISUAL) -I $(DIR_INC) -L ft_printf ft_printf/libftprintf.a -lpanel -lncurses

%.o: %.c $(INCLUDES)
	gcc $(FLAGS) -I $(DIR_INC) -I $(DIR_LIB) $< -c -o $@

clean:
	rm -rf srcs/corewar/*.o
	rm -rf srcs/visual/*.o

fclean: clean
	rm -rf $(NAME)