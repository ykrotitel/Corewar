/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:06:16 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 20:08:23 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		live(t_data *data, t_carriage *carriage, int32_t pos)
{
	int32_t	r;

	r = get_value(DIR_SIZE, data->arena, pos);
	if (data->h_flag & OPERATIONS)
		ft_printf("%d\n", r);
	if (r >= -data->players_num && r < 0)
	{
		data->winner_id = r * -1;
		if (data->h_flag & LIVES)
			printf("A process shows that %d (%s) is alive\n",
				r * -1,
				data->champs[-r - 1].header.prog_name);
	}
	carriage->last_live_cycle = data->cycles;
	data->live_op_counter++;
}
