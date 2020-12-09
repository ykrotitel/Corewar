# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 23:17:20 by acarlett          #+#    #+#              #
#    Updated: 2020/12/05 14:55:24 by acarlett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_SRCS =	srcs

DIR_VIS =	srcs/visual

DIR_INC =	includes

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
			$(DIR_SRCS)/operations.c \
			$(DIR_SRCS)/parse_arguments.c \
			$(DIR_SRCS)/parse_champions.c \
			$(DIR_SRCS)/st.c \
			$(DIR_SRCS)/zjmp.c

SRCS_VISUAL = $(DIR_VIS)/init.c

INCL =	$(DIR_INC)/corewar.h \
		$(DIR_INC)/corewar_visual.h

all:
	@gcc $(SRCS_CORE) $(SRCS_VISUAL) -I includes/ -L ft_printf ft_printf/libftprintf.a -lpanel -lncurses