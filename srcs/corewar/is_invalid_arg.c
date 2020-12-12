/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_invalid_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 21:19:01 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 21:19:01 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		invalid_register(uint8_t reg_num)
{
	if (reg_num == 0 || reg_num > REG_NUMBER)
		return (1);
	return (0);
}

int		invalid_arg(t_carriage *carriage, const uint8_t *arena, int i)
{
	if (!(carriage->args[i] & g_op_tab[carriage->op_code - 1].args_type[i]))
		return (1);
	if (carriage->args[i] == T_REG &&
		invalid_register(arena[(carriage->curr_pos
								+ carriage->bytes_step) % MEM_SIZE]))
		return (1);
	return (0);
}
