/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_visual.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:13:25 by acarlett          #+#    #+#             */
/*   Updated: 2020/12/09 19:43:13 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VISUAL_H
# define COREWAR_VISUAL_H

# include <ncurses.h>
# include <time.h>
#include <panel.h>
#include <sys/ioctl.h>
#include <stdio.h>
# include "corewar.h"

# define WIDTH 200
# define HEIGHT 100

# define LINES 30
# define COLUMNS 200

typedef struct	s_wins
{
	WINDOW		*arena_win;
	WINDOW		*info_win;
}				t_wins;

typedef struct		s_visual
{
	t_wins			wins;
	struct winsize	win_size;
	uint8_t			carriage[MEM_SIZE];
	
}					t_visual;


/*
** init.c
*/
void		init_ncurses(t_data *data, t_visual *visual, struct winsize *win_size);
void		first_init(t_data *data, t_visual *visual);
void		init_utils_arena(int *i, int *code_size, int *count_champs);
void		handle_keys(int *button);
int			carriage_length(t_carriage *tmp);


/*
** visual.c
*/
void		visual(t_data *data, int *button, int flag);


/*
** info_table.c
*/
void		make_info_table(t_data *data, WINDOW *info_win);
void		make_color_pair();


/*
** arena.c
*/
void		show_arena(t_data *data, t_visual visual, int *button);
void		make_arena(t_data *data, WINDOW *arena_win, t_visual *visual);

# endif