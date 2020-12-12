/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:30:54 by acarlett          #+#    #+#             */
/*   Updated: 2020/12/12 16:56:11 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar_visual.h"

void		init_ncurses(t_visual *visual,
												struct winsize *win_size)
{
	initscr();
	noecho();
	curs_set(false);
	start_color();
	ioctl(0, TIOCGWINSZ, win_size);
	visual->wins.arena_win = newwin(win_size->ws_row, 238, 0, 0);
	visual->wins.info_win = newwin(win_size->ws_row, 55, 0, 238);
}

void		init_utils_arena(int *i, int *code_size, int *count_champs)
{
	*i = 0;
	*code_size = 0;
	*count_champs = 0;
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

void		handle_keys(int *button)
{
	if ((*button) == '0')
		*button = getch();
}
