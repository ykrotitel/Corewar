/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:33:49 by acarlett          #+#    #+#             */
/*   Updated: 2020/12/12 16:58:36 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar_visual.h"

void		show_static_members(WINDOW *info_win, t_data *data)
{
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
}

void		show_carriage_members(t_data *data, WINDOW *info_win, int i)
{
	int j;

	j = 0;
	while (data->champs->header.prog_name[j] != '\0')
		wprintw(info_win, "%c", data->champs[i].header.prog_name[j++]);
	wattroff(info_win, COLOR_PAIR(i + 1));
	wprintw(info_win, "\n\n");
	wprintw(info_win, "\n\n");
}

void		make_info_table(t_data *data, WINDOW *info_win)
{
	int i;

	i = -1;
	wmove(info_win, 3, 2);
	show_static_members(info_win, data);
	while (++i != data->players_num)
	{
		wattron(info_win, COLOR_PAIR(6));
		wprintw(info_win, "  PLAYER #%d: ", i + 1);
		wattron(info_win, COLOR_PAIR(i + 1));
		show_carriage_members(data, info_win, i);
	}
	wattroff(info_win, COLOR_PAIR(5));
	wattroff(info_win, COLOR_PAIR(6));
	box(info_win, 0, 0);
}

void		make_color_pair(void)
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
