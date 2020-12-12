/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:06:27 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 20:08:40 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int32_t	change_value(
		t_carriage *carriage,
		t_data *data,
		int32_t *pos,
		size_t inx)
{
	uint8_t type;
	int32_t arg;

	type = carriage->args[inx] == T_DIR ? T_IND : carriage->args[inx];
	arg = get_arg(type, pos, data->arena);
	if (carriage->args[inx] == T_REG)
		arg = carriage->registers[arg - 1];
	else if (carriage->args[inx] == T_IND)
		arg = get_value(DIR_SIZE, data->arena,
						carriage->curr_pos + arg);
	return (arg);
}

void			ld(t_data *data, t_carriage *carriage, int32_t pos)
{
	int32_t	arg;
	int16_t	r_inx;

	arg = get_arg(carriage->args[0], &pos, data->arena);
	r_inx = data->arena[get_pos(pos)];
	if (carriage->args[0] == T_IND)
	{
		arg = get_value(DIR_SIZE, data->arena,
						carriage->curr_pos + arg % IDX_MOD);
	}
	carriage->registers[r_inx - 1] = arg;
	carriage->carry = (arg == 0) ? 1 : 0;
	if (data->h_flag & OPERATIONS)
		ft_printf("%d r%d\n", arg, r_inx);
}

void			ldi(t_data *data, t_carriage *carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int16_t	r_inx3;

	arg1 = change_value(carriage, data, &pos, 0);
	arg2 = change_value(carriage, data, &pos, 1);
	r_inx3 = data->arena[get_pos(pos)];
	carriage->registers[r_inx3 - 1] = get_value(
			DIR_SIZE,
			data->arena,
			carriage->curr_pos + (arg1 + arg2) % IDX_MOD);
	if (data->h_flag & OPERATIONS)
		ft_printf("%d %d r%d\n       "
			"| -> load from %d + %d = %d (with pc and mod %d)\n",
			arg1, arg2, r_inx3, arg1, arg2, arg1 + arg2,
			carriage->curr_pos + (arg1 + arg2) % IDX_MOD);
}

void			lld(t_data *data, t_carriage *carriage, int32_t pos)
{
	int32_t	arg;
	int16_t	r_inx;

	arg = get_arg(carriage->args[0], &pos, data->arena);
	r_inx = data->arena[get_pos(pos)];
	if (carriage->args[0] == T_IND)
		arg = get_value(DIR_SIZE, data->arena,
						carriage->curr_pos + arg);
	carriage->registers[r_inx - 1] = arg;
	carriage->carry = (arg == 0) ? 1 : 0;
	if (data->h_flag & OPERATIONS)
		ft_printf("%d r%d\n", arg, r_inx);
}

void			lldi(t_data *data, t_carriage *carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int16_t	r_inx3;

	arg1 = change_value(carriage, data, &pos, 0);
	arg2 = change_value(carriage, data, &pos, 1);
	r_inx3 = data->arena[get_pos(pos)];
	carriage->registers[r_inx3 - 1] = get_value(
			DIR_SIZE,
			data->arena,
			carriage->curr_pos + (arg1 + arg2));
	if (data->h_flag & OPERATIONS)
		ft_printf("%d %d r%d\n       "
				"| -> load from %d + %d = %d (with pc and mod %d)\n",
				arg1, arg2, r_inx3, arg1, arg2, arg1 + arg2,
				carriage->curr_pos + (arg1 + arg2));
}
