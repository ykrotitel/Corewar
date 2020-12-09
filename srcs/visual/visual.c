/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:05:10 by acarlett          #+#    #+#             */
/*   Updated: 2020/12/09 19:45:38 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar_visual.h"

void		visual(t_data *data, int *button, int flag)
{
	t_visual visual;

	first_init(data, &visual);
	init_ncurses(data, &visual, &(visual.win_size));
	if (*button == ' ' || flag)
	{
		show_arena(data, visual, button);
		handle_keys(button);
	}
	delwin(visual.wins.arena_win);
	delwin(visual.wins.info_win);
	curs_set(true);
}
