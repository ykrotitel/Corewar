/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:45:53 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 21:42:14 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exec_op(t_data *data, t_carriage *carriage)
{
	int32_t pos;

	pos = carriage->curr_pos;
	pos += (g_op_tab[carriage->op_code - 1].arg_type_code) ? 2 : 1;
	g_op_tab[carriage->op_code - 1].func(data, carriage, pos);
	carriage->curr_pos += carriage->bytes_step;
	carriage->curr_pos = get_pos(carriage->curr_pos);
}

void	validate_and_exec(t_data *data, t_carriage *carriage)
{
	if (!validate_op(carriage))
		return ;
	if (!validate_args(carriage, data->arena))
		return ;
	if (data->h_flag & OPERATIONS)
		ft_printf("P %4u | %s ",
				carriage->uid, g_op_tab[carriage->op_code - 1].op_name,
				data->cycles,
				carriage->curr_pos,
				carriage->curr_pos + carriage->bytes_step);
	exec_op(data, carriage);
}

void	carriage_check(t_data *data)
{
	t_carriage *it;

	it = data->carriage_list;
	while (it)
	{
		if (it->cycles_before == 0)
			set_op_code(it, data->arena);
		if (it->cycles_before > 0)
			--it->cycles_before;
		if (it->cycles_before == 0)
			validate_and_exec(data, it);
		it = it->next;
	}
}

void	is_cycle_to_die(t_data *data, int32_t *cycles_to_die)
{
	if (++(*cycles_to_die) == data->cycles_to_die || data->cycles_to_die < 0)
	{
		ctd_check(data);
		*cycles_to_die = 0;
		data->live_op_counter = 0;
	}
}

void	game(t_data *data)
{
	int32_t cycles_to_die;
	int32_t button;

	button = '0';
	cycles_to_die = 0;
	data->winner_id = data->champs[data->players_num - 1].uid;
	while (1)
	{
		data->cycles++;
		if (data->h_flag & CYCLES)
			ft_printf("It is now cycle %d\n", data->cycles);
		if ((uint32_t)data->cycles == data->dump_cycles)
		{
			print_arena_state(data->arena);
			return ;
		}
		carriage_check(data);
		is_cycle_to_die(data, &cycles_to_die);
		if (data->carriage_list == NULL)
			break ;
		if (data->v_flag)
			visual(data, &button, 1);
	}
	greeting_message(data->champs[data->winner_id - 1].uid,
			data->champs[data->winner_id - 1].header.prog_name);
}
