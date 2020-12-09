/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:06:50 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/09 16:55:17 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	and(t_data *data, t_carriage **carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int16_t	r_inx3;

	arg1 = get_arg((*carriage)->args[0], &pos, &data->arena);
	if ((*carriage)->args[0] == T_REG)
		arg1 = (*carriage)->registers[arg1 - 1];
	else if ((*carriage)->args[0] == T_IND)
		arg1 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg1);
	arg2 = get_arg((*carriage)->args[1], &pos, &data->arena);
	if ((*carriage)->args[1] == T_REG)
		arg2 = (*carriage)->registers[arg2 - 1];
	else if ((*carriage)->args[1] == T_IND)
		arg2 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg2);
	r_inx3 = data->arena[get_pos(pos)];
	(*carriage)->registers[r_inx3 - 1] = arg1 & arg2;
	(*carriage)->carry = ((*carriage)->registers[r_inx3 - 1]) ? 0 : 1;

#ifdef TEST
	// ft_printf("%d %d r%d\n", arg1, arg2, r_inx3);

#endif
}

void	or(t_data *data, t_carriage **carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int16_t	r_inx3;

	arg1 = get_arg((*carriage)->args[0], &pos, &data->arena);
	if ((*carriage)->args[0] == T_REG)
		arg1 = (*carriage)->registers[arg1 - 1];
	else if ((*carriage)->args[0] == T_IND)
		arg1 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg1);
	arg2 = get_arg((*carriage)->args[1], &pos, &data->arena);
	if ((*carriage)->args[1] == T_REG)
		arg2 = (*carriage)->registers[arg2 - 1];
	else if ((*carriage)->args[1] == T_IND)
		arg2 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg2);
	r_inx3 = data->arena[get_pos(pos)];
	(*carriage)->registers[r_inx3 - 1] = arg1 | arg2;
	(*carriage)->carry = ((*carriage)->registers[r_inx3 - 1]) ? 0 : 1;

#ifdef TEST
	ft_printf("%d %d r%d\n", arg1, arg2, r_inx3);

#endif
}

void	xor(t_data *data, t_carriage **carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int16_t	r_inx3;

	arg1 = get_arg((*carriage)->args[0], &pos, &data->arena);
	if ((*carriage)->args[0] == T_REG)
		arg1 = (*carriage)->registers[arg1 - 1];
	else if ((*carriage)->args[0] == T_IND)
		arg1 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg1);
	arg2 = get_arg((*carriage)->args[1], &pos, &data->arena);
	if ((*carriage)->args[1] == T_REG)
		arg2 = (*carriage)->registers[arg2 - 1];
	else if ((*carriage)->args[1] == T_IND)
		arg2 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg2);
	r_inx3 = data->arena[get_pos(pos)];
	(*carriage)->registers[r_inx3 - 1] = arg1 ^ arg2;
	(*carriage)->carry = ((*carriage)->registers[r_inx3 - 1]) ? 0 : 1;

#ifdef TEST
	ft_printf("%d %d r%d\n", arg1, arg2, r_inx3);

#endif
}
