/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:07:06 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 15:49:31 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add(t_data *data, t_carriage *carriage, int32_t pos)
{
	uint16_t r_inx1;
	uint16_t r_inx2;
	uint16_t r_inx3;

	r_inx1 = data->arena[get_pos(pos++)];
	r_inx2 = data->arena[get_pos(pos++)];
	r_inx3 = data->arena[get_pos(pos)];
	carriage->registers[r_inx3 - 1] = carriage->registers[r_inx1 - 1]
										+ carriage->registers[r_inx2 - 1];
	carriage->carry = (carriage->registers[r_inx3 - 1]) ? 0 : 1;
	if (data->h_flag & OPERATIONS)
		ft_printf("r%d r%d r%d\n", r_inx1, r_inx2, r_inx3);
}

void	sub(t_data *data, t_carriage *carriage, int32_t pos)
{
	uint16_t r_inx1;
	uint16_t r_inx2;
	uint16_t r_inx3;

	r_inx1 = data->arena[get_pos(pos++)];
	r_inx2 = data->arena[get_pos(pos++)];
	r_inx3 = data->arena[get_pos(pos)];
	carriage->registers[r_inx3 - 1] = carriage->registers[r_inx1 - 1]
										- carriage->registers[r_inx2 - 1];
	carriage->carry = (carriage->registers[r_inx3 - 1]) ? 0 : 1;
	if (data->h_flag & OPERATIONS)
		ft_printf("r%d r%d r%d\n", r_inx1, r_inx2, r_inx3);
}
