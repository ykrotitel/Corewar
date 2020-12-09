/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_visual.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:13:25 by acarlett          #+#    #+#             */
/*   Updated: 2020/12/09 14:52:48 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VISUAL_H
# define COREWAR_VISUAL_H

# include <ncurses.h>
# include <time.h>
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
void		visual(t_data *data, int *button);

# endif