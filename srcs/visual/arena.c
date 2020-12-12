/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:13:47 by acarlett          #+#    #+#             */
/*   Updated: 2020/12/12 17:03:52 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar_visual.h"

void		show_arena(t_data *data, t_visual visual)
{
	make_color_pair();
	make_arena(data, visual.wins.arena_win, &visual);
	make_info_table(data, visual.wins.info_win);
	refresh();
	wrefresh(visual.wins.arena_win);
	wrefresh(visual.wins.info_win);
	delay_output(25);
}

void		set_color_on(t_data *data, int i,
							t_visual *visual, WINDOW *arena_win)
{
	if (data->code_color[i])
		wattron(arena_win, COLOR_PAIR(data->code_color[i]));
	if (visual->carriage[i] != 0)
		wattron(arena_win, COLOR_PAIR((visual->carriage[i] * 10)));
}

void		set_color_off(t_data *data, int i,
							t_visual *visual, WINDOW *arena_win)
{
	if (data->code_color[i])
		wattroff(arena_win, COLOR_PAIR(data->code_color[i]));
	if (visual->carriage[i] != 0)
		wattroff(arena_win, COLOR_PAIR((visual->carriage[i] * 10)));
}

void		handle_count_champs(t_data *data, int *code_size,
							int *count_champs, WINDOW *arena_win)
{
	if ((unsigned int)*code_size ==
	data->champs[*count_champs].header.prog_size)
	{
		wattroff(arena_win, COLOR_PAIR(*count_champs + 1));
		*code_size = 0;
		(*count_champs)++;
		if (*count_champs >= data->players_num)
			*count_champs = data->players_num - 1;
	}
}

void		make_arena(t_data *data, WINDOW *arena_win, t_visual *visual)
{
	int i;
	int code_size;
	int	count_champs;

	init_utils_arena(&i, &code_size, &count_champs);
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
		set_color_on(data, i, visual, arena_win);
		wprintw(arena_win, "%02x", data->arena[i]);
		set_color_off(data, i, visual, arena_win);
		if (i == (MEM_SIZE / data->players_num) * count_champs || code_size)
			wattroff(arena_win, COLOR_PAIR(count_champs + 1));
		wprintw(arena_win, " ");
		handle_count_champs(data, &code_size, &count_champs, arena_win);
		i++;
	}
	box(arena_win, 0, 0);
}
