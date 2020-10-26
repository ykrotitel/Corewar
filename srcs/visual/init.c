/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:30:54 by acarlett          #+#    #+#             */
/*   Updated: 2020/10/26 21:58:30 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar_visual.h"
#include <panel.h>
#include <sys/ioctl.h>
#include <stdio.h>

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

void		test(t_data *data)
{
	WINDOW *win;
	int i;
	int x;
	int y;

	i = 0;

    struct winsize win_size;
    ioctl(0, TIOCGWINSZ, &win_size);

    printf ("lines %d\n", win_size.ws_row);
    printf ("columns %d\n", win_size.ws_col);
	initscr();
	start_color();
	// init_pair(1, COLOR_RED, COLOR_CYAN);
	win = newwin(win_size.ws_row, win_size.ws_col, 0, 0);
	// attron(1);
	box(win, 0, 0);
	touchwin(win);
	refresh();
	// attroff(1);
	wrefresh(win);
	delwin(win);
	getch();
}

void		visual(t_data *data)
{
	WINDOW	*win;
	int		set_x;
	int		set_y;
	int i;
	int j;
	int	key;

	i = 0;
	j = 0;
	initscr();
	
	getmaxyx(stdscr, set_y, set_x);
	win = newwin(HEIGHT, WIDTH, set_y, set_x);
	
	curs_set(false);
	
	init_pair(3, COLOR_GREEN, COLOR_MAGENTA);

	attron(COLOR_PAIR(3));
	box(win, '*', '*');
	attroff(COLOR_PAIR(3));
	wrefresh(win);

	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	// attron(COLOR_PAIR(1));
	// i = 0;
	// while (i != data->champs->header.prog_size)
	// {
	// 	printw("%02x ", data->arena[i]);
	// 	i++;
	// }
	// attroff(COLOR_PAIR(1));
	// attron(COLOR_PAIR(2));
	// while (i != MEM_SIZE)
	// {
	// 	printw("00 ");
	// 	i++;
	// }
	// attroff(COLOR_PAIR(1));
	curs_set(true);
    delwin(win);
    getch();
}
















	// while (1 || key != 27)
	// {
	// 	// key = getch();
	// 	mvaddstr((set_y / 2 + 0), (set_x / 2 + 0), "Just a String\n");
	// 	if (j < 10 && !j_f)
	// 		j++;
	// 	if (j == 10)
	// 		j_f = 1;
	// 	if (j <= 10 && j_f)
	// 		j--;
	// 	if (j == 0)
	// 		j_f = 0;
		
		
	// 	if (i < 10 && !i_f)
	// 		i++;
	// 	if (i == 10)
	// 		i_f = 1;
	// 	if (i <= 10 && i_f)
	// 		i--;
	// 	if (i == 0)
	// 		i_f = 0;
	// 	if (k == 1)
	// 		k = 2;
	// 	else if (k == 2)
	// 		k = 1;
	// 	refresh();
	// 	delay_output(100);
	// 	clear();
	// }