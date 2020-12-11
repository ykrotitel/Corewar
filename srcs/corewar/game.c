/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:45:53 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/10 21:32:17 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	set_op_code(t_carriage **carriage, const uint8_t (*arena)[MEM_SIZE])
{

	(*carriage)->op_code = (*arena)[(*carriage)->curr_pos % MEM_SIZE];
	if ((*carriage)->op_code > 0 && (*carriage)->op_code < 17)
		(*carriage)->cycles_before = op_tab[(*carriage)->op_code - 1].cycles;
}

int		validate_op(t_carriage **carriage, const uint8_t (*arena)[MEM_SIZE])
{
	if ((*carriage)->op_code > 16 || (*carriage)->op_code == 0)
	{
		(*carriage)->curr_pos++;
		return (0);
	}
	return (1);
}

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

int 	invalid_register(uint8_t reg_num)
{
	if (reg_num == 0 || reg_num > REG_NUMBER)
		return (1);
	return (0);
}

int 	invalid_arg(t_carriage **carriage,
					const uint8_t (*arena)[MEM_SIZE], int i)
{
	if (!((*carriage)->args[i] &
				op_tab[(*carriage)->op_code - 1].args_type[i]))
		return (1);
	if ((*carriage)->args[i] == T_REG &&
			invalid_register(
					(*arena)[((*carriage)->curr_pos
					+ (*carriage)->bytes_step) % MEM_SIZE]
					))
		return (1);
	return (0);
}

void	calc_one_arg_step(uint8_t arg_type,
						uint32_t *bytes_step, uint8_t op_code)
{
	if (arg_type == T_REG)
		*bytes_step += T_REG;
	else if (arg_type == T_DIR)
		*bytes_step += op_tab[op_code - 1].dir_size;
	else if (arg_type == T_IND)
		*bytes_step += IND_SIZE;
}

void	validate_with_type_code(t_carriage **carriage,
		uint8_t *wrong_args, const uint8_t (*arena)[MEM_SIZE])
{
	int		i;
	uint8_t	arg_type;

	i = 0;
	(*carriage)->bytes_step++;
	arg_type = (*arena)[((*carriage)->curr_pos + 1) % MEM_SIZE];
	while (i < op_tab[(*carriage)->op_code - 1].args_num)
	{
		(*carriage)->args[i] = one_argument_type(arg_type, 6 - i * 2);
		*wrong_args += invalid_arg(carriage, arena, i);
		calc_one_arg_step(
							(*carriage)->args[i],
							&(*carriage)->bytes_step,
							(*carriage)->op_code);
		i++;
	}
}

void	validate_without_type_code(t_carriage **carriage,
			uint8_t *wrong_args, const uint8_t (*arena)[MEM_SIZE])
{
	int i;

	i = 0;
	while (i < op_tab[(*carriage)->op_code - 1].args_num)
	{
		if (op_tab[(*carriage)->op_code - 1].args_type[i] & T_REG)
			*wrong_args += invalid_register(
					(*arena)[((*carriage)->curr_pos
					+ (*carriage)->bytes_step) % MEM_SIZE]
			);
		calc_one_arg_step(
				op_tab[(*carriage)->op_code - 1].args_type[i],
				&(*carriage)->bytes_step,
				(*carriage)->op_code
		);
		i++;
	}
}

int		validate_args(t_carriage **carriage,
						const uint8_t (*arena)[MEM_SIZE])
{
	uint8_t		wrong_args;

	(*carriage)->bytes_step = 1;
	wrong_args = 0;
	if (op_tab[(*carriage)->op_code - 1].arg_type_code)
		validate_with_type_code(carriage, &wrong_args, arena);
	else
		validate_without_type_code(carriage, &wrong_args, arena);
	if (wrong_args)
	{
		(*carriage)->curr_pos += (*carriage)->bytes_step;
		return (0);
	}
	return (1);
}

void	exec_op(t_data *data, t_carriage **carriage)
{
	int32_t pos;

	pos = (*carriage)->curr_pos;
	pos += (op_tab[(*carriage)->op_code - 1].arg_type_code) ? 2 : 1;
	op_tab[(*carriage)->op_code - 1].func(data, carriage, pos);
	(*carriage)->curr_pos += (*carriage)->bytes_step;
	(*carriage)->curr_pos = get_pos((*carriage)->curr_pos);
}

void	validate_and_exec(t_data *data, t_carriage **carriage)
{
	if (!validate_op(carriage, &data->arena))
		return ;
	if (!validate_args(carriage, &data->arena))
		return ;
	if (data->h_flag & OPERATIONS)
		ft_printf("P %4u | %s ",
			(*carriage)->uid, op_tab[(*carriage)->op_code - 1].op_name,
			data->cycles,
			(*carriage)->curr_pos,
			(*carriage)->curr_pos + (*carriage)->bytes_step);
	exec_op(data, carriage);
}

void	carriage_check(t_data *data)
{
	t_carriage *it;

	it = data->carriage_list;
	while (it)
	{
		if (it->cycles_before == 0)
			set_op_code(&it, &data->arena);
		if (it->cycles_before > 0)
			--it->cycles_before;
		if (it->cycles_before == 0)
			validate_and_exec(data, &it);
		it = it->next;
	}
}

void	greeting_message(uint8_t player_uid, const char *player_name)
{
	ft_printf("Contestant %u, \"%s\", has won !\n",
			player_uid,
			player_name);
}

void	is_cycle_to_die(t_data *data, int32_t *cycles_to_die)
{
	if (++(*cycles_to_die) == data->cycles_to_die ||
								data->cycles_to_die < 0)
	{
		ctd_check(data);
		*cycles_to_die = 0;
		data->live_op_counter = 0;
	}
}

void	game(t_data *data)
{
	int32_t cycles_to_die;
	int32_t button;

	button = '0';
	cycles_to_die = 0;
	data->winner_id = data->champs[data->players_num - 1].uid;
	while (1)
	{
		data->cycles++;
		if (data->h_flag & CYCLES)
			ft_printf("It is now cycle %d\n", data->cycles);
		if (data->cycles == data->dump_cycles)
		{
			print_arena_state(&data->arena);
			return ;
		}
		carriage_check(data);
		is_cycle_to_die(data, &cycles_to_die);
		if (data->carriage_list == NULL)
			break ;
		if (data->v_flag)
			visual(data, &button, 1);
	}
	greeting_message(data->champs[data->winner_id - 1].uid,
					data->champs[data->winner_id - 1].header.prog_name);
}
