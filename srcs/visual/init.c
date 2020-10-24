/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:30:54 by acarlett          #+#    #+#             */
/*   Updated: 2020/10/24 22:47:20 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar_visual.h"

void		clear_window(WINDOW *win)
{
	int y;
	int x;
	int tmp_x;

	getmaxyx(win, y, x);
	tmp_x = x;
	while (y != 0)
	{
		while (x != 0)
		{
			mvaddch(y, x, ' ');
			x--;
		}
		x = tmp_x;
		y--;
	}

}

void		visual(t_data *data)
{
	WINDOW	*win;
	int		set_x;
	int		set_y;
	int i;
	int i_f;
	int j;
	int j_f;

	i = 0;
	i_f = 0;
	j = 0;
	j_f = 0;
	initscr();
	getmaxyx(stdscr, set_y, set_x);
	curs_set(false);

	
	// set_x = (COLS - WIDTH) / 2;
	// set_y = (LINES - HEIGHT) / 2;
	
	win = newwin(HEIGHT, WIDTH, set_y, set_x);
	while (j != 65)
	{
		mvaddstr((set_y / 2 + j), (set_x / 2 + i), "Just a String");
		if (j < 10 && !j_f)
			j++;
		if (j == 10)
			j_f = 1;
		if (j <= 10 && j_f)
			j--;
		if (j == 0)
			j_f = 0;
		
		
		if (i < 10 && !i_f)
			i++;
		if (i == 10)
			i_f = 1;
		if (i <= 10 && i_f)
			i--;
		if (i == 0)
			i_f = 0;

		refresh();
		delay_output(100);
		clear();

	}
    delwin(win);
    getch();
	printw("Hello world!!\n");
}