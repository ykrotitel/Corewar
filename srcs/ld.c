/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:06:27 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/09 16:56:02 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ld(t_data *data, t_carriage **carriage, int32_t pos)
{
	int32_t	arg;
	int16_t	r_inx;

	arg = get_arg((*carriage)->args[0], &pos, &data->arena);
	r_inx = data->arena[get_pos(pos)];
	if ((*carriage)->args[0] == T_IND) {
		arg = get_value(DIR_SIZE, &data->arena,
						(*carriage)->curr_pos + arg % IDX_MOD);
	}
	(*carriage)->registers[r_inx - 1] = arg;
	(*carriage)->carry = (arg == 0) ? 1 : 0;

#ifdef TEST
	ft_printf("%d r%d\n", arg, r_inx);

#endif
}

void	ldi(t_data *data, t_carriage **carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int16_t	r_inx3;
	uint8_t type;

	type = (*carriage)->args[0] == T_DIR ? T_IND : (*carriage)->args[0];
	arg1 = get_arg(type, &pos, &data->arena);
	if ((*carriage)->args[0] == T_REG)
		arg1 = (*carriage)->registers[arg1 - 1];
	else if ((*carriage)->args[0] == T_IND)
		arg1 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg1);
	type = (*carriage)->args[1] == T_DIR ? T_IND : (*carriage)->args[1];
	arg2 = get_arg(type, &pos, &data->arena);
	if ((*carriage)->args[1] == T_REG)
		arg2 = (*carriage)->registers[arg2 - 1];
	else if ((*carriage)->args[1] == T_IND)
		arg2 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg2);
	r_inx3 = data->arena[get_pos(pos)];
	(*carriage)->registers[r_inx3 - 1] = get_value(
			DIR_SIZE,
			&data->arena,
			(*carriage)->curr_pos + (arg1 + arg2) % IDX_MOD);

#ifdef TEST
	ft_printf("%d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %d)\n",
		   arg1, arg2, r_inx3, arg1, arg2, arg1 + arg2, (*carriage)->curr_pos + (arg1 + arg2) % IDX_MOD);

#endif
}

void	lld(t_data *data, t_carriage **carriage, int32_t pos)
{
	int32_t	arg;
	int16_t	r_inx;

	arg = get_arg((*carriage)->args[0], &pos, &data->arena);
	r_inx = data->arena[get_pos(pos)];
	if ((*carriage)->args[0] == T_IND)
		arg = get_value(DIR_SIZE, &data->arena,
						(*carriage)->curr_pos + arg);
	(*carriage)->registers[r_inx - 1] = arg;
	(*carriage)->carry = (arg == 0) ? 1 : 0;
}

void	lldi(t_data *data, t_carriage **carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int16_t	r_inx3;
	uint8_t type;

	type = (*carriage)->args[0] == T_DIR ? T_IND : (*carriage)->args[0];
	arg1 = get_arg(type, &pos, &data->arena);
	if ((*carriage)->args[0] == T_REG)
		arg1 = (*carriage)->registers[arg1 - 1];
	else if ((*carriage)->args[0] == T_IND)
		arg1 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg1);
	type = (*carriage)->args[1] == T_DIR ? T_IND : (*carriage)->args[1];
	arg2 = get_arg(type, &pos, &data->arena);
	if ((*carriage)->args[1] == T_REG)
		arg2 = (*carriage)->registers[arg2 - 1];
	else if ((*carriage)->args[1] == T_IND)
		arg2 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg2);
	r_inx3 = data->arena[get_pos(pos)];
	(*carriage)->registers[r_inx3 - 1] = get_value(
			DIR_SIZE,
			&data->arena,
			(*carriage)->curr_pos + (arg1 + arg2));
}
