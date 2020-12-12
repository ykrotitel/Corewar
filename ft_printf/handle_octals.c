/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_octals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 17:12:42 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/24 15:22:08 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		delete_zero_flag(t_printf *data, t_ll n)
{
	t_ll len;

	len = (t_ll)ft_numlen(n, 10);
	if (data->precision != 0 && data->flag & ZERO &&
	(((t_ll)data->precision >= len + (n < 0 ? 1 : 0))
	|| (data->width > len && (t_ll)data->precision < len)))
		data->flag ^= ZERO;
}

static void		if_minus_flag(t_printf *data, t_ll n)
{
	int prcn;

	prcn = data->precision;
	if (data->flag & MINUS && (!n && data->precision == -1)
	&& data->flag & SHARP && handle_overflow_buffer(data, 1))
		data->buff[data->length++] = '0';
	if (data->flag & MINUS && !n && data->precision == -1 && data->flag & PLUS
	&& handle_overflow_buffer(data, 1))
		data->buff[data->length++] = '+';
	if ((data->flag & MINUS || (data->flag & ZERO && data->flag & SHARP)) &&
	!(!n && data->precision == -1))
	{
		while (prcn-- > (t_ll)ft_numlen(n, 8) + (data->flag & SHARP ? 1 : 0)
		&& handle_overflow_buffer(data, 1))
			data->buff[data->length++] = '0';
		itoa_base_buff(n, data->type, data);
	}
}

static void		if_not_minus_flag(t_printf *data, t_ll n)
{
	int prcn;

	prcn = data->precision;
	if (!(data->flag & MINUS) && !(!n && data->precision == -1))
	{
		while (prcn-- > (t_ll)ft_numlen(n, data->type)
		+ (data->flag & SHARP ? 1 : 0) && handle_overflow_buffer(data, 1))
			data->buff[data->length++] = '0';
		itoa_base_buff(n, data->type, data);
	}
	if (!(data->flag & MINUS) && (!n && data->precision == -1)
	&& data->flag & PLUS && handle_overflow_buffer(data, 1))
		data->buff[data->length++] = '+';
	if (!(data->flag & MINUS) && (!n && data->precision == -1)
	&& data->flag & SHARP && handle_overflow_buffer(data, 1))
		data->buff[data->length++] = '0';
}

void			handle_octals(t_printf *data)
{
	t_ll	n;
	int		is_sharp;
	int		prcn;
	t_ll	len;
	t_ll	width;

	get_integer(data, &n);
	len = (t_ll)ft_numlen(n, 8);
	width = data->width;
	is_sharp = (data->flag & SHARP) ? 1 : 0;
	delete_zero_flag(data, n);
	if_minus_flag(data, n);
	prcn = (data->precision < len) ? len : data->precision;
	while (width-- - prcn - (is_sharp && n && (data->precision < len))
	+ ((!n && data->precision == -1) && !(data->type & OCTAL && is_sharp)) > 0
	&& handle_overflow_buffer(data, 1))
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
	if_not_minus_flag(data, n);
}
