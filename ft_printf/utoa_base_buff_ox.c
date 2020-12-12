/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa_base_buff_ox.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 14:27:08 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/24 18:03:45 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		check_flags(t_printf *data, t_ull value, unsigned base)
{
	handle_overflow_buffer(data, ft_numlen(value, base) + 1);
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

size_t			ft_unumlen(t_ull val, unsigned base)
{
	size_t len;

	len = 0;
	if (val == 0)
		len++;
	if (val != 0)
	{
		val = val / base;
		len++;
	}
	while (val > 0)
	{
		val = val / base;
		len++;
	}
	return (len);
}

char			uvalue(t_ull value, unsigned base, t_printf *data)
{
	char ch;

	if (value % base >= 10)
	{
		if (data->type == BIG_HEX)
			ch = (value % base) % 10 + 'A';
		else
			ch = (value % base) % 10 + 'a';
	}
	else
		ch = (value % base) + '0';
	return (ch);
}

t_ll			new_uvalue(t_ull value, unsigned *base, t_ull *val)
{
	if (*base == BIG_HEX)
		*base = 16;
	*val = value;
	return (value);
}

void			utoa_base_buff_ox(t_ull value, unsigned base, t_printf *data)
{
	size_t		len;
	t_ull		val;

	value = new_uvalue(value, &base, &val);
	len = ft_unumlen(value, base);
	if (check_flags(data, value, base))
		return ;
	while (value > base)
	{
		data->buff[data->length + (len--) - 1] = uvalue(value, base, data);
		value = value / base;
	}
	if (value == base)
	{
		data->buff[data->length + len-- - 1] = '0';
		data->buff[data->length + len-- - 1] = '1';
	}
	else
		data->buff[data->length + len - 1] = uvalue(value, base, data);
	data->length += (ft_unumlen(val, base));
}
