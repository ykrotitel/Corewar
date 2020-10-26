# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 23:17:20 by acarlett          #+#    #+#              #
#    Updated: 2020/10/26 19:10:32 by acarlett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_SRCS =	srcs

DIR_VIS =	srcs/visual

DIR_INC =	includes

SRCS_CORE =	$(DIR_SRCS)/main.c \
			$(DIR_SRCS)/op.c \
			$(DIR_SRCS)/parse_arguments.c \
			$(DIR_SRCS)/parse_champions.c

SRCS_VISUAL = $(DIR_VIS)/init.c

INCL =	$(DIR_INC)/corewar.h \
		$(DIR_INC)/corewar_visual.h

all:
	@gcc $(SRCS_CORE) $(SRCS_VISUAL) -I includes/ -L ft_printf ft_printf/libftprintf.a -lpanel -lncurses