/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:06:08 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 20:08:15 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			st(t_data *data, t_carriage *carriage, int32_t pos)
{
	int16_t	r_inx1;
	int32_t	r_inx2;

	r_inx1 = data->arena[get_pos(pos++)];
	r_inx2 = get_arg(carriage->args[1], &pos, data->arena);
	if (carriage->args[1] == T_REG)
		carriage->registers[r_inx2 - 1] = carriage->registers[r_inx1 - 1];
	else if (carriage->args[1] == T_IND)
		place_value(carriage->registers[r_inx1 - 1],
					carriage->curr_pos + r_inx2 % IDX_MOD,
					carriage,
					data);
	if (carriage->args[1] == T_REG)
		r_inx2 = carriage->registers[r_inx2 - 1];
	if (data->h_flag & OPERATIONS)
		ft_printf("r%d %d\n", r_inx1, r_inx2);
}

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

void			sti(t_data *data, t_carriage *carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int32_t	arg3;
	uint8_t tmp_reg;

	tmp_reg = data->arena[get_pos(pos++)];
	arg1 = carriage->registers[tmp_reg - 1];
	arg2 = change_value(carriage, data, &pos, 1);
	arg3 = change_value(carriage, data, &pos, 2);
	place_value(arg1,
				carriage->curr_pos % MEM_SIZE + (arg2 + arg3) % IDX_MOD,
				carriage,
				data);
	if (data->h_flag & OPERATIONS)
		ft_printf("r%d %d %d\n       "
			"| -> store to %d + %d = %d (with pc and mod %d)\n",
			tmp_reg,
			arg2, arg3, arg2, arg3, arg2 + arg3,
			carriage->curr_pos % MEM_SIZE + (arg2 + arg3) % IDX_MOD);
}
