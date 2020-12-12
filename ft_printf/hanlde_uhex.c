/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hanlde_uhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 14:59:43 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/24 15:22:55 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		if_minus_flag(t_printf *data, t_ull n, t_ll *width, int *sharp)
{
	int prcn;

	prcn = data->precision;
	handle_overflow_buffer(data, ft_unumlen(n, 16) +
	(data->flag & PLUS ? 1 : 0));
	if (data->flag & MINUS && !n && data->precision == -1 && data->flag & PLUS)
		data->buff[data->length++] = '+';
	if ((data->flag & MINUS || (data->flag & ZERO && data->flag & SHARP)) &&
	!(!n && data->precision == -1))
	{
		if (data->flag & SHARP && data->precision != 0 && n)
		{
			handle_overflow_buffer(data, 2);
			data->buff[data->length++] = '0';
			data->buff[data->length++] = 'x';
			data->flag ^= SHARP;
			*width -= 2;
			*sharp = 0;
		}
		while (prcn-- > (t_ll)ft_unumlen(n, data->type)
		+ (data->type & OCTAL && data->flag & SHARP)
		&& handle_overflow_buffer(data, 1))
			data->buff[data->length++] = '0';
		utoa_base_buff_ox(n, data->type, data);
	}
}

static void		if_not_minus_flag(t_printf *data, t_ull n, int *sharp)
{
	int prcn;

	prcn = data->precision;
	if (!(data->flag & MINUS) && !(!n && data->precision == -1))
	{
		if (data->flag & SHARP && data->precision != 0 && n)
		{
			handle_overflow_buffer(data, 2);
			data->buff[data->length++] = '0';
			data->buff[data->length++] = 'x';
			data->flag ^= SHARP;
			*sharp = 0;
		}
		while (prcn-- > (t_ll)ft_unumlen(n, data->type)
		&& handle_overflow_buffer(data, 1))
			data->buff[data->length++] = '0';
		utoa_base_buff_ox(n, data->type, data);
	}
	if (!(data->flag & MINUS) && (!n && data->precision == -1)
	&& data->flag & PLUS && handle_overflow_buffer(data, 1))
		data->buff[data->length++] = '+';
}

void			handle_uhex(t_printf *data)
{
	t_ull	n;
	t_ll	width;
	int		prcn;
	int		is_sharp;
	t_ll	len;

	get_unsigned(data, &n);
	width = data->width;
	len = (t_ll)ft_unumlen(n, 16);
	is_sharp = (data->flag & SHARP) ? 1 : 0;
	if (data->precision != 0 && data->flag & ZERO)
		data->flag ^= ZERO;
	if_minus_flag(data, n, &width, &is_sharp);
	prcn = (data->precision < len) ? len : data->precision;
	if (!(data->flag & MINUS) && data->flag & SHARP
	&& n && data->precision > len)
		width -= 2;
	while (width-- - prcn - ((is_sharp && n && data->precision < len) ? 2 : 0)
	+ ((!n && data->precision == -1) && !(data->type & OCTAL && is_sharp)) > 0
	&& handle_overflow_buffer(data, 1))
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
	if_not_minus_flag(data, n, &is_sharp);
}
