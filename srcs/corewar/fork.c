/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:06:41 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/10 21:22:52 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	copy_fields(t_carriage *lhs, t_carriage *rhs)
{
	ft_memcpy((void*)lhs->registers,
			(void*)rhs->registers, sizeof(int32_t) * REG_NUMBER);
	lhs->carry = rhs->carry;
	lhs->last_live_cycle = rhs->last_live_cycle;
	lhs->color_code = rhs->color_code;
}

void		fork_(t_data *data, t_carriage **carriage, int32_t pos)
{
	int32_t		arg;
	t_carriage	*carriage_copy;

	arg = get_value(IND_SIZE, &data->arena, pos);
	carriage_copy = *carriage;
	init_carriage(
			&data->carriage_list,
			data->carriage_list->uid + 1,
			(*carriage)->curr_pos + arg % IDX_MOD);
	copy_fields(data->carriage_list, carriage_copy);
	if (data->h_flag & OPERATIONS)
		ft_printf("%d (%d)\n", arg, data->carriage_list->curr_pos);
}

void		lfork(t_data *data, t_carriage **carriage, int32_t pos)
{
	int32_t		arg;
	t_carriage	*carriage_copy;

	arg = get_value(IND_SIZE, &data->arena, pos);
	carriage_copy = *carriage;
	init_carriage(
			&data->carriage_list,
			data->carriage_list->uid + 1,
			(*carriage)->curr_pos + arg);
	copy_fields(data->carriage_list, carriage_copy);
	if (data->h_flag & OPERATIONS)
		ft_printf("%d (%d)\n", arg, data->carriage_list->curr_pos);
}
