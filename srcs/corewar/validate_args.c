/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 21:15:15 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 21:40:26 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

uint8_t	one_argument_type(uint8_t arg_type, uint8_t shift)
{
	arg_type >>= shift;
	arg_type &= (uint8_t)3;
	if (!(arg_type ^ (uint8_t)1))
		return (T_REG);
	if (!(arg_type ^ (uint8_t)2))
		return (T_DIR);
	if (!(arg_type ^ (uint8_t)3))
		return (T_IND);
	return (0);
}

void	calc_one_arg_step(uint8_t type, uint32_t *bytes_step, uint8_t op_code)
{
	if (type == T_REG)
		*bytes_step += T_REG;
	else if (type == T_DIR)
		*bytes_step += g_op_tab[op_code - 1].dir_size;
	else if (type == T_IND)
		*bytes_step += IND_SIZE;
}

void	validate_with_type_code(
		t_carriage *carriage,
		uint8_t *wrong_args,
		const uint8_t *arena)
{
	int		i;
	uint8_t	arg_type;

	i = 0;
	carriage->bytes_step++;
	arg_type = arena[(carriage->curr_pos + 1) % MEM_SIZE];
	while (i < g_op_tab[carriage->op_code - 1].args_num)
	{
		carriage->args[i] = one_argument_type(arg_type, 6 - i * 2);
		*wrong_args += invalid_arg(carriage, arena, i);
		calc_one_arg_step(carriage->args[i],
						&carriage->bytes_step,
						carriage->op_code);
		i++;
	}
}

void	validate_without_type_code(
		t_carriage *carriage,
		uint8_t *wrong_args,
		const uint8_t *arena)
{
	int i;

	i = 0;
	while (i < g_op_tab[carriage->op_code - 1].args_num)
	{
		if (g_op_tab[carriage->op_code - 1].args_type[i] & T_REG)
			*wrong_args += invalid_register(arena[(carriage->curr_pos
									+ carriage->bytes_step) % MEM_SIZE]);
		calc_one_arg_step(g_op_tab[carriage->op_code - 1].args_type[i],
						&carriage->bytes_step,
						carriage->op_code);
		i++;
	}
}

int		validate_args(t_carriage *carriage, const uint8_t *arena)
{
	uint8_t		wrong_args;

	carriage->bytes_step = 1;
	wrong_args = 0;
	if (g_op_tab[carriage->op_code - 1].arg_type_code)
		validate_with_type_code(carriage, &wrong_args, arena);
	else
		validate_without_type_code(carriage, &wrong_args, arena);
	if (wrong_args)
	{
		carriage->curr_pos += carriage->bytes_step;
		return (0);
	}
	return (1);
}
