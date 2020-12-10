/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:59:23 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/10 21:29:55 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int32_t		get_pos(int32_t pos)
{
	if (pos < 0)
		return (pos % MEM_SIZE + MEM_SIZE);
	return (pos % MEM_SIZE);
}

int32_t		get_value(size_t size, const uint8_t (*arena)[MEM_SIZE], int32_t pos)
{
	size_t	i;
	int32_t	arg;

	i = 0;
	arg = 0;
	while (i < size)
	{
		arg <<= (int32_t)8;
		arg |= (*arena)[get_pos(pos + i)];
		i++;
	}
	if (size == 2 && arg & 0x8000)
		arg |= 0xFFFF0000;
	return ((int)arg);
}

int32_t		get_arg(uint8_t arg_type,  int32_t *pos, const uint8_t (*arena)[MEM_SIZE])
{
	int32_t arg;

	arg = 0;
	if (arg_type == T_DIR)
	{
		arg = get_value(DIR_SIZE, arena, *pos);
		*pos += DIR_SIZE;
	}
	else if (arg_type == T_IND)
	{
		arg = get_value(IND_SIZE, arena, *pos);
		*pos += IND_SIZE;
	}
	else if (arg_type == T_REG)
	{
		arg = (*arena)[get_pos(*pos)];
		++(*pos);
	}
	return (arg);
}

void		place_value(int32_t arg, int32_t pos, t_carriage *carriage, t_data *data)
{
	size_t size;

	size = REG_SIZE;
	while (size--)
	{
		data->arena[get_pos(pos + size)] = arg & 0xFF;
		arg >>= (uint32_t)8;
	}
}
