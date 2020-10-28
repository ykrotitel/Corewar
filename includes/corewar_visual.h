/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_visual.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:13:25 by acarlett          #+#    #+#             */
/*   Updated: 2020/10/27 18:42:28 by acarlett         ###   ########.fr       */
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
	
}					t_visual;


/*
** init.c
*/
void		visual(t_data *data);

# endif