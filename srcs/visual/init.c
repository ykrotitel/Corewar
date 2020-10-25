/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:30:54 by acarlett          #+#    #+#             */
/*   Updated: 2020/10/25 20:52:26 by acarlett         ###   ########.fr       */
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

// char		*convert_x_to_char(t_data *data)
// {
// 	char	a[2];
// 	int		i;

// 	i = 0;
// 	data->arena[i];
// }

char		*int_to_x(uint8_t arena)
{
	char	*tmp;
	int		buff;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * 3);
	while (arena % 16)
	{
		buff = arena % 16;
		switch (buff = arena % 16)
		{
		case 10:
			tmp[i] = 'a';
		case 11:
			tmp[i] = 'a';
		case 12:
			tmp[i] = 'a';
		case 13:
			tmp[i] = 'a';
		case 14:
			tmp[i] = 'a';
		case 15:
			tmp[i] = 'a';
		}
		i++;
		arena = arena / 16;
	}
	tmp[2] = '\0';
	return (tmp);
}

void		visual(t_data *data)
{
	WINDOW	*win;
	char	*ch;
	int		set_x;
	int		set_y;
	int i;
	int j;
	int	key;

	i = 0;
	j = 0;
	ch = malloc(sizeof(char) * 2);
	initscr();
	getmaxyx(stdscr, set_y, set_x);
	curs_set(false);

	
	win = newwin(HEIGHT, WIDTH, set_y, set_x);
	start_color();
	key = 1;
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	i = MEM_SIZE;
	attron(COLOR_PAIR(1));
	while (data->champs->header.prog_size--)
	{
		ch = int_to_x(data->arena[j]);
		addch(48);
		addstr(ch);
		addch(' ');
		j++;
		// ch = convert_x_to_char(data);
		// printf("%02x ", data->arena[j++]);
		i--;
	}
	attroff(COLOR_PAIR(1));

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
	attroff(COLOR_PAIR(1));
	curs_set(true);
    delwin(win);
    getch();
	printw("Hello world!!\n");
}