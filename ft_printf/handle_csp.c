/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_csp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:28:53 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/24 19:38:38 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			push_pointer(t_printf *data, t_ll n)
{
	t_ll len;

	len = (t_ll)ft_numlen(n, 16);
	if (data->precision > len || (!n && data->precision == -1))
	{
		ft_strcpy(&data->buff[data->length], "0x");
		data->length += 2;
		if (!n && data->precision == -1)
			return ;
		while (data->precision-- - len > 0 && handle_overflow_buffer(data, 1))
			data->buff[data->length++] = '0';
		data->type = HEX;
		data->flag = 0;
		itoa_base_buff(n, 16, data);
	}
	else
		itoa_base_buff(n, 16, data);
}

void			handle_pointers(t_printf *data)
{
	t_ll n;

	n = (long)va_arg(data->ap, void *);
	handle_overflow_buffer(data, ft_numlen(n, 16) + data->width);
	if (data->flag & MINUS)
		push_pointer(data, n);
	while (data->width-- - (long long)ft_numlen(n, 16) - 2 > 0)
		data->buff[data->length++] = 32;
	if (!(data->flag & MINUS))
		push_pointer(data, n);
}

void			handle_chars(t_printf *data)
{
	handle_overflow_buffer(data, 1);
	if (data->flag & MINUS)
		data->buff[data->length++] = (char)va_arg(data->ap, int);
	while (--data->width > 0 && handle_overflow_buffer(data, 1))
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
	if (!(data->flag & MINUS))
		data->buff[data->length++] = (char)va_arg(data->ap, int);
}
