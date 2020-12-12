/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:05:57 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 20:07:56 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	zjmp(t_data *data, t_carriage *carriage, int32_t pos)
{
	int32_t arg;

	arg = get_value(IND_SIZE, data->arena, pos);
	if (carriage->carry)
	{
		carriage->curr_pos += arg % IDX_MOD;
		carriage->curr_pos -= carriage->bytes_step;
	}
	if (data->h_flag & OPERATIONS)
	{
		if (carriage->carry)
			ft_printf("%d OK\n", arg);
		else
			ft_printf("%d FAILED\n", arg);
	}
}
