/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_integers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 21:03:31 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/23 15:04:04 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		delete_zero_flag(t_printf *data, t_ll n)
{
	t_ll len;

	len = (t_ll)ft_numlen(n, 10);
	if (data->precision != 0 && data->flag & ZERO &&
	((data->precision >= len + (n < 0 ? 1 : 0))
	|| (data->width > len && data->precision < len)))
		data->flag ^= ZERO;
}

static void		if_minus_flag(t_printf *data, t_ll n)
{
	int prcn;

	prcn = data->precision;
	if (data->flag & MINUS && !n && data->precision == -1 && data->flag & PLUS
	&& handle_overflow_buffer(data, 1))
		data->buff[data->length++] = '+';
	if ((data->flag & MINUS || (data->flag & ZERO && data->flag & SHARP)) &&
	!(!n && data->precision == -1))
	{
		while (prcn-- > (t_ll)ft_numlen(n, 10)
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
		while (prcn-- > (t_ll)ft_numlen(n, 10)
		&& handle_overflow_buffer(data, 1))
			data->buff[data->length++] = '0';
		itoa_base_buff(n, data->type, data);
	}
	if (!(data->flag & MINUS) && (!n && data->precision == -1)
	&& data->flag & PLUS && handle_overflow_buffer(data, 1))
		data->buff[data->length++] = '+';
}

void			handle_integers(t_printf *data)
{
	t_ll	n;
	int		excpn;
	int		prcn;
	t_ll	width;
	t_ll	len;

	get_integer(data, &n);
	len = (t_ll)ft_numlen(n, 10);
	width = data->width;
	excpn = (!n && data->precision == -1) ? 1 : 0;
	delete_zero_flag(data, n);
	if_minus_flag(data, n);
	prcn = (data->precision < len) ? len : data->precision;
	if (prcn == data->precision && n < 0 && data->precision > len)
		prcn++;
	while (width-- - prcn + excpn
	- (((data->flag & PLUS || data->flag & SPACE) && n >= 0) ? 1 : 0) > 0
	&& handle_overflow_buffer(data, 1))
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
	if_not_minus_flag(data, n);
}
