/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:53:44 by lmittie           #+#    #+#             */
/*   Updated: 2020/10/22 16:34:55 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include <libc.h>

typedef struct		s_champ
{
	uint8_t		uid;
	t_header	header;
}					t_champ;

typedef struct		s_carriage
{
	uint16_t			uid;
	uint8_t				carry;
	uint8_t				op_code;
	uint32_t			last_live_cycle;
	uint16_t			cycles_before;
	uint32_t			curr_pos;
	uint32_t			bytes_step;
	uint16_t			registers[REG_NUMBER];
	struct s_carriage	*next;
}					t_carriage;

typedef struct		s_args
{
	int32_t				arg_it;
	int8_t				n_flag;
}					t_args;

typedef struct		s_data
{
	t_champ				champs[MAX_PLAYERS];
	uint16_t			players_num;
	uint8_t				arena[MEM_SIZE];
	t_carriage			*carriage_list;
	uint8_t				winner_id;
	uint32_t			cycles;
	uint32_t			live_op_counter;
	uint32_t			cycles_to_die;
	uint32_t			checks_counter;
	uint32_t			dump_cycles;
}					t_data;

void	parse_arguments(int ac, const char **av, t_data *data);
void	parse_champions(t_args (*champs)[MAX_PLAYERS], t_data *data, const char **av);

#endif