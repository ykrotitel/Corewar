/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base_buff_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:26:07 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/23 15:09:00 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t				ft_numlen_u(t_ull val)
{
	size_t len;

	len = 0;
	if (val == 0)
		len++;
	while (val > 0)
	{
		len++;
		val /= 10;
	}
	return (len);
}

static void			replace_space_u(int pos, t_printf *data, t_ll val)
{
	int i;

	i = 0;
	if (data->flag & SPACE && (data->precision >
	(t_ll)ft_numlen_u(val) || data->flag & ZERO))
	{
		data->buff[pos] = '0';
		while (data->buff[pos - i] == '0')
			i++;
		data->buff[pos - --i] = ' ';
	}
}

static int			check_flags_u(t_printf *data, t_ull value)
{
	handle_overflow_buffer(data, ft_numlen_u(value) + 1);
	if ((data->flag & PLUS))
		data->buff[data->length++] = '+';
	else if ((data->flag & SPACE) && data->precision != -1)
	{
		data->buff[data->length++] = ' ';
		replace_space_u(data->length - 1, data, value);
	}
	return (0);
}

static void			replace_zero_u(int pos, t_printf *data, t_ull val)
{
	int i;

	i = 0;
	if ((data->flag & ZERO || data->precision >
	(t_ll)ft_numlen_u(val)) && (data->flag & PLUS))
	{
		data->buff[pos] = '0';
		while (data->buff[pos - i] == '0')
			i++;
		data->buff[pos - --i] = '+';
	}
}

void				itoa_base_buff_u(t_ull value, t_printf *data)
{
	size_t		len;
	t_ull		val;

	val = value;
	len = ft_numlen_u(value);
	check_flags_u(data, value);
	while (value > 9)
	{
		data->buff[data->length + (len--) - 1] = (value % 10) + '0';
		value = value / 10;
	}
	data->buff[data->length + len - 1] = (value % 10) + '0';
	if ((data->flag & ZERO || data->precision >
	(t_ll)ft_numlen_u(val)) && data->flag & PLUS)
		replace_zero_u(data->length + (int)(len) - 2, data, val);
	data->length += (ft_numlen_u(val));
}
