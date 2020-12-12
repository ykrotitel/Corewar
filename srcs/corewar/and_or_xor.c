/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:06:50 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 20:38:14 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int32_t	change_value(
		t_carriage *carriage,
		t_data *data,
		int32_t *pos,
		size_t inx)
{
	int32_t arg;

	arg = get_arg(carriage->args[inx], pos, data->arena);
	if (carriage->args[inx] == T_REG)
		arg = carriage->registers[arg - 1];
	else if (carriage->args[inx] == T_IND)
		arg = get_value(DIR_SIZE, data->arena,
						carriage->curr_pos + arg);
	return (arg);
}

void			and(t_data *data, t_carriage *carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int16_t	r_inx3;

	arg1 = change_value(carriage, data, &pos, 0);
	arg2 = change_value(carriage, data, &pos, 1);
	r_inx3 = data->arena[get_pos(pos)];
	carriage->registers[r_inx3 - 1] = arg1 & arg2;
	carriage->carry = (carriage->registers[r_inx3 - 1]) ? 0 : 1;
	if (data->h_flag & OPERATIONS)
		ft_printf("%d %d r%d\n", arg1, arg2, r_inx3);
}

void			or(t_data *data, t_carriage *carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int16_t	r_inx3;

	arg1 = change_value(carriage, data, &pos, 0);
	arg2 = change_value(carriage, data, &pos, 1);
	r_inx3 = data->arena[get_pos(pos)];
	carriage->registers[r_inx3 - 1] = arg1 | arg2;
	carriage->carry = (carriage->registers[r_inx3 - 1]) ? 0 : 1;
	if (data->h_flag & OPERATIONS)
		ft_printf("%d %d r%d\n", arg1, arg2, r_inx3);
}

void			xor(t_data *data, t_carriage *carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int16_t	r_inx3;

	arg1 = change_value(carriage, data, &pos, 0);
	arg2 = change_value(carriage, data, &pos, 1);
	r_inx3 = data->arena[get_pos(pos)];
	carriage->registers[r_inx3 - 1] = arg1 ^ arg2;
	carriage->carry = (carriage->registers[r_inx3 - 1]) ? 0 : 1;
	if (data->h_flag & OPERATIONS)
		ft_printf("%d %d r%d\n", arg1, arg2, r_inx3);
}
