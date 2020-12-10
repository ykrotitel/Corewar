/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:53:44 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/10 21:18:58 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

# define LIVES		1
# define CYCLES		2
# define OPERATIONS 4

# include "../ft_printf/ft_printf.h"
# include "op.h"
# include <libc.h>

typedef struct		s_champ
{
	uint8_t		uid;
	t_header	header;
}					t_champ;

typedef struct		s_carriage
{
	uint32_t			uid;
	uint8_t				carry;
	uint8_t				op_code;
	int32_t				last_live_cycle;
	int32_t				curr_live_num;
	uint16_t			cycles_before;
	int32_t				curr_pos;
	uint32_t			bytes_step;
	int32_t				registers[REG_NUMBER];
	uint8_t				args[3];
	uint8_t				color_code;
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
	uint8_t				code_color[MEM_SIZE];
	uint8_t				arena[MEM_SIZE];
	t_carriage			*carriage_list;
	uint8_t				winner_id;
	int32_t				cycles;
	uint32_t			live_op_counter;
	int32_t				cycles_to_die;
	uint32_t			checks_counter;
	uint32_t			dump_cycles;
	uint8_t				a_flag;
	uint8_t				v_flag;
	uint8_t				h_flag;
}					t_data;

typedef struct	s_op
{
	const char	*op_name;
	uint8_t		args_num;
	t_arg_type	args_type[4];
	uint8_t		op_code;
	uint16_t	cycles;
	const char	*op_description;
	uint8_t		arg_type_code;
	uint8_t		dir_size;
	void		(*func)(t_data *, t_carriage **, int32_t);
}				t_op;

extern t_op op_tab[17];

void 	print_usage();
void	print_arena_state(uint8_t (*arena)[MEM_SIZE]);

int32_t	get_value(size_t size, const uint8_t (*arena)[MEM_SIZE], int32_t pos);
int32_t	get_arg(uint8_t arg_type,  int32_t *pos, const uint8_t (*arena)[MEM_SIZE]);
void	place_value(int32_t arg, int32_t pos, t_carriage *carriage, t_data *data);

int32_t	get_pos(int32_t pos);

void	parse_arguments(int ac, const char **av, t_data *data);
void	parse_champions(t_args (*champs)[MAX_PLAYERS], t_data *data, const char **av);

void	game(t_data *data);
void	ctd_check(t_data *data);

void	init_carriage(t_carriage **clist, uint32_t uid, size_t pos);

void		live(t_data *data, t_carriage **carriage, int32_t pos);
void		ld(t_data *data, t_carriage **carriage, int32_t pos);
void		st(t_data *data, t_carriage **carriage, int32_t pos);
void		add(t_data *data, t_carriage **carriage, int32_t pos);
void		sub(t_data *data, t_carriage **carriage, int32_t pos);
void		and(t_data *data, t_carriage **carriage, int32_t pos);
void		or(t_data *data, t_carriage **carriage, int32_t pos);
void		xor(t_data *data, t_carriage **carriage, int32_t pos);
void		zjmp(t_data *data, t_carriage **carriage, int32_t pos);
void		ldi(t_data *data, t_carriage **carriage, int32_t pos);
void		sti(t_data *data, t_carriage **carriage, int32_t pos);
void		fork_(t_data *data, t_carriage **carriage, int32_t pos);
void		lld(t_data *data, t_carriage **carriage, int32_t pos);
void		lldi(t_data *data, t_carriage **carriage, int32_t pos);
void		lfork(t_data *data, t_carriage **carriage, int32_t pos);
void		aff(t_data *data, t_carriage **carriage, int32_t pos);
void		visual(t_data *data, int *button, int flag);


#endif