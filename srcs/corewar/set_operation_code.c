/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_operation_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 21:17:29 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 21:17:29 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		validate_op(t_carriage *carriage)
{
	if (carriage->op_code > 16 || carriage->op_code == 0)
	{
		carriage->curr_pos++;
		return (0);
	}
	return (1);
}

void	set_op_code(t_carriage *carriage, const uint8_t *arena)
{
	carriage->op_code = arena[carriage->curr_pos % MEM_SIZE];
	if (carriage->op_code > 0 && carriage->op_code < 17)
		carriage->cycles_before = g_op_tab[carriage->op_code - 1].cycles;
}
