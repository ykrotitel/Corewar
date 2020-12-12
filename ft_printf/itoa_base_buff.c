/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base_buff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:26:07 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/24 18:06:39 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			replace_space(int pos, t_printf *data, t_ll val)
{
	int i;

	i = 0;
	if (data->flag & SPACE && (data->precision >
	(t_ll)ft_numlen(val, 10) || data->flag & ZERO))
	{
		data->buff[pos] = '0';
		while (data->buff[pos - i] == '0')
			i++;
		data->buff[pos - --i] = ' ';
	}
}

static int			check_flags(t_printf *data, t_ll value, unsigned base)
{
	handle_overflow_buffer(data, ft_numlen(value, base) + 1);
	if (base == 10 && value < 0 &&
	data->precision > (t_ll)ft_numlen(value, base))
		data->buff[data->length++] = '0';
	if (value >= 0 && (data->flag & PLUS) && base == 10)
		data->buff[data->length++] = '+';
	else if (value >= 0 && (data->flag & SPACE)
	&& base == 10 && data->precision != -1)
	{
		data->buff[data->length++] = ' ';
		replace_space(data->length - 1, data, value);
	}
	if ((data->flag & SHARP && data->type & OCTAL && value == 0 &&
	data->precision != -1 && data->precision != 0) || (((data->flag & SHARP
	&& base != 10) && value != 0) || data->type & POINTER))
		data->buff[data->length++] = '0';
	if (((data->flag & SHARP) && (data->type == HEX || data->type == BIG_HEX)
			&& value) || data->type & POINTER)
		data->buff[data->length++] = 'x' - ((data->type == BIG_HEX) ? 32 : 0);
	if (data->flag & ZERO && data->flag & SHARP)
	{
		data->flag ^= SHARP;
		return (1);
	}
	return (0);
}

static void			replace_zero(int pos, t_printf *data, t_ll val)
{
	int i;

	i = 0;
	if ((data->flag & ZERO || data->precision >
	(t_ll)ft_numlen(val, 10)) && (val < 0 || data->flag & PLUS))
	{
		data->buff[pos] = '0';
		while (data->buff[pos - i] == '0')
			i++;
		if (val < 0)
			data->buff[pos - --i] = '-';
		else
			data->buff[pos - --i] = '+';
	}
}

void				push_ten(t_printf *data, size_t *len, unsigned base)
{
	data->buff[data->length + (*len)-- - 1] = '0';
	data->buff[data->length + (*len)-- - 1] = '1';
	*len = (base == 10) ? *len + 1 : *len;
}

void				itoa_base_buff(t_ll value, unsigned base, t_printf *data)
{
	size_t		len;
	t_ll		val;

	value = new_value(value, &base, &val);
	len = ft_numlen(value, base);
	if (check_flags(data, value, base))
		return ;
	while (value > base || value < -(int)base)
	{
		data->buff[data->length + (len--) - 1] = result(value, base, data);
		value = value / base;
	}
	if (value == base || value == -(int)base)
		push_ten(data, &len, base);
	else
		data->buff[data->length + len - 1] = result(value, base, data);
	if ((data->flag & ZERO || data->precision >
	(t_ll)ft_numlen(val, base)) && (val < 0 || data->flag & PLUS) && base == 10)
		replace_zero(data->length + (int)(len) - 2, data, val);
	else if (val < 0 && base == 10)
		data->buff[data->length + --len - 1] = '-';
	data->length += (ft_numlen(val, base));
}
