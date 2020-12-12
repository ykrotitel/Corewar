/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:30:35 by fmallist          #+#    #+#             */
/*   Updated: 2019/12/25 16:26:29 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			handle_percent(t_printf *data)
{
	if (data->flag & MINUS)
		data->buff[data->length++] = '%';
	while (--data->width > 0 && handle_overflow_buffer(data, 1))
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
	if (!(data->flag & MINUS))
		data->buff[data->length++] = '%';
}

void			push_buffer_extra(t_printf *data)
{
	if (data->type == BIG_HEX && !(data->size & L) && !(data->size & LL))
		handle_bighex(data);
	else if (data->type == OCTAL)
		handle_uoctal(data);
	else if (data->type == HEX)
		handle_uhex(data);
	else if (data->type == BIG_HEX)
		handle_ubighex(data);
	else if (data->type == UNSIGNED)
		handle_unsigned(data);
	else if (data->type == FL)
		handle_floats(data);
}

void			push_buffer(t_printf *data)
{
	if (data->type & CHAR)
		handle_chars(data);
	else if (data->type & STRING || data->type & UNDEF)
		handle_strings(data);
	else if (data->type & POINTER)
		handle_pointers(data);
	else if (data->type & PERCENT &&
			handle_overflow_buffer(data, data->width + 1))
		handle_percent(data);
	else if (data->type == DECIMAL)
		handle_integers(data);
	else if (data->type == OCTAL && !(data->size & L) && !(data->size & LL))
		handle_octals(data);
	else if (data->type == HEX && !(data->size & L) && !(data->size & LL))
		handle_hexdecimals(data);
	else
		push_buffer_extra(data);
}
