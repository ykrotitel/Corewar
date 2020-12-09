/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:30:54 by acarlett          #+#    #+#             */
/*   Updated: 2020/12/09 17:04:34 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar_visual.h"
#include <panel.h>
#include <sys/ioctl.h>
#include <stdio.h>

int buff;

void		init_ncurses(t_data *data, t_visual *visual, struct winsize *win_size)
{
	initscr();
	noecho();
	curs_set(false);
	start_color();
    ioctl(0, TIOCGWINSZ, win_size);
	visual->wins.arena_win = newwin(win_size->ws_row, 238, 0, 0);
	visual->wins.info_win = newwin(win_size->ws_row, 55, 0, 238);

}

void		make_arena(t_data *data, WINDOW *arena_win, t_visual *visual)
{
	int i;
	int code_size;
	int	count_champs;

	i = 0;
	code_size = 0;
	count_champs = 0;
	wprintw(arena_win, "\n");
	while (i != MEM_SIZE - 1)
	{
		if (i % 79 == 0)
			wprintw(arena_win, " ");
		if (i == (MEM_SIZE / data->players_num) * count_champs || code_size)
		{
			code_size++;
			wattron(arena_win, COLOR_PAIR(count_champs + 1));
		}

		if (data->code_color[i])
		{
			wattron(arena_win, COLOR_PAIR(data->code_color[i]));
		}

		
		if (visual->carriage[i] != 0)
		{
				wattron(arena_win, COLOR_PAIR((visual->carriage[i] * 10)));
		}
		wprintw(arena_win, "%02x", data->arena[i]);


		if (data->code_color[i])
		{
			wattroff(arena_win, COLOR_PAIR(data->code_color[i]));
		}

		if (visual->carriage[i] != 0)
		{
				wattroff(arena_win, COLOR_PAIR((visual->carriage[i] * 10)));
		}
		
		else if(i == (MEM_SIZE / data->players_num) * count_champs || code_size)
			wattroff(arena_win, COLOR_PAIR(count_champs + 1));
				
		wprintw(arena_win, " ");
		
		if (code_size == data->champs[count_champs].header.prog_size)
		{
			wattroff(arena_win, COLOR_PAIR(count_champs + 1));
			code_size = 0;
			count_champs++;

			if (count_champs >= data->players_num){
				count_champs = data->players_num - 1;
			}
		}
		i++;
	}
	box(arena_win, 0, 0);
}


void		make_color_pair()
{
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(10, COLOR_WHITE, COLOR_BLUE);

	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(20, COLOR_WHITE, COLOR_GREEN);
	
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(30, COLOR_WHITE, COLOR_MAGENTA);
	
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(40, COLOR_WHITE, COLOR_CYAN);
	
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);

	init_pair(7, COLOR_BLACK, COLOR_WHITE);
}

int			carriage_length(t_carriage *tmp)
{
	int i;

	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);

}

void		make_info_table(t_data *data, WINDOW *info_win)
{
	int i;
	int j;

	i = -1;
	wmove(info_win, 3, 2);

	wattron(info_win, COLOR_PAIR(6));
	wprintw(info_win, "CYCLE: ");
	wattron(info_win, COLOR_PAIR(5));
	wprintw(info_win, "%d\n\n", data->cycles);

	wattron(info_win, COLOR_PAIR(6));
	wprintw(info_win, "  CYCLES TO DIE: ");
	wattron(info_win, COLOR_PAIR(5));
	wprintw(info_win, "%d\n\n", data->cycles_to_die);
		
	wattron(info_win, COLOR_PAIR(6));
	wprintw(info_win, "  LIVE COUNTER:");
	wattron(info_win, COLOR_PAIR(5));
	wprintw(info_win, "  %d\n\n", data->live_op_counter);	
		
	wattron(info_win, COLOR_PAIR(6));
	wprintw(info_win, "  PROCESSES:");
	wattron(info_win, COLOR_PAIR(5));
	wprintw(info_win, "  %d\n\n\n", carriage_length(data->carriage_list));	

	while (++i != data->players_num)
	{
		wattron(info_win, COLOR_PAIR(6));
		wprintw(info_win, "  PLAYER #%d: ", i + 1);
		wattron(info_win, COLOR_PAIR(i + 1));

		j = 0;
		while(data->champs->header.prog_name[j] != '\0')
			wprintw(info_win, "%c", data->champs[i].header.prog_name[j++]);
		wattroff(info_win, COLOR_PAIR(i + 1));

		wprintw(info_win, "\n\n");
		wattron(info_win, COLOR_PAIR(6));
		wprintw(info_win, "\tLives in current period:      ");
		wattron(info_win, COLOR_PAIR(5));
		wprintw(info_win, "133");

		wprintw(info_win, "\n\n");
		wattron(info_win, COLOR_PAIR(6));
		wprintw(info_win, "\tLast live:                    ");
		wattron(info_win, COLOR_PAIR(5));
		wprintw(info_win, "1333");
		
		wprintw(info_win, "\n\n\n");
	}

	wattroff(info_win, COLOR_PAIR(5));
	wattroff(info_win, COLOR_PAIR(6));
	box(info_win, 0, 0);

}

void		first_init(t_data *data, t_visual *visual)
{
	t_carriage *tmp;

	tmp = data->carriage_list;
	ft_bzero(visual->carriage, MEM_SIZE);

	while (tmp != NULL)
	{
		visual->carriage[get_pos(tmp->curr_pos)] = tmp->color_code;
		tmp = tmp->next;
	}
}

void		visual(t_data *data, int *button)
{
	t_visual visual;

	first_init(data, &visual);

	init_ncurses(data, &visual, &(visual.win_size));

       if ((*button) == '0') {
            *button = wgetch(visual.wins.arena_win);
       }
	if (*button != '0')
	{
		make_color_pair();
		make_arena(data, visual.wins.arena_win, &visual);
		make_info_table(data, visual.wins.info_win);



		refresh();
		delay_output(5);
		wrefresh(visual.wins.arena_win);
		wrefresh(visual.wins.info_win);
	}
	delwin(visual.wins.arena_win);
	delwin(visual.wins.info_win);
	curs_set(true);
}
