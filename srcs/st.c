/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:06:08 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/09 16:56:48 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	st(t_data *data, t_carriage **carriage, int32_t pos)
{
	int16_t	r_inx1;
	int32_t	r_inx2;

	r_inx1 = data->arena[get_pos(pos++)];
	r_inx2 = get_arg((*carriage)->args[1], &pos, &data->arena);
	if ((*carriage)->args[1] == T_REG)
		(*carriage)->registers[r_inx2 - 1] = (*carriage)->registers[r_inx1 - 1];
	else if ((*carriage)->args[1] == T_IND)
		place_value((*carriage)->registers[r_inx1 - 1],
					(*carriage)->curr_pos + r_inx2 % IDX_MOD,
					*carriage,
					data);
	if ((*carriage)->args[1] == T_REG)
		r_inx2 = (*carriage)->registers[r_inx2 - 1];
#ifdef TEST
	ft_printf("r%d %d\n", r_inx1, r_inx2);
#endif
}

void	sti(t_data *data, t_carriage **carriage, int32_t pos)
{
	int32_t	arg1;
	int32_t	arg2;
	int32_t	arg3;
	uint8_t type;

	arg1 = (*carriage)->registers[data->arena[get_pos(pos++)] - 1];
	type = (*carriage)->args[1] == T_DIR ? T_IND : (*carriage)->args[1];
	arg2 = get_arg(type, &pos, &data->arena);
	if ((*carriage)->args[1] == T_REG)
		arg2 = (*carriage)->registers[arg2 - 1];
	else if ((*carriage)->args[1] == T_IND)
		arg2 = get_value(DIR_SIZE, &data->arena,
						 (*carriage)->curr_pos + arg2);
	type = (*carriage)->args[2] == T_DIR ? T_IND : (*carriage)->args[2];
	arg3 = get_arg(type, &pos, &data->arena);
	if ((*carriage)->args[2] == T_REG)
		arg3 = (*carriage)->registers[arg3 - 1];
	place_value(arg1,
				(*carriage)->curr_pos % MEM_SIZE + (arg2 + arg3) % IDX_MOD,
				*carriage,
				data);

#ifdef TEST
	ft_printf("r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n",
			  data->arena[get_pos((*carriage)->curr_pos + 2)],
			  arg2, arg3, arg2, arg3, arg2 + arg3, (*carriage)->curr_pos % MEM_SIZE + (arg2 + arg3) % IDX_MOD);
#endif
}
