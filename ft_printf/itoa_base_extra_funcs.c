/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base_extra_funcs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:16:05 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/24 14:37:08 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			neg_value(t_ll value, unsigned base, t_printf *data)
{
	char ch;

	if (value % (int)base <= -10)
	{
		if ((data->type & BIG_HEX) == BIG_HEX)
			ch = (value % (int)base) * -1 % 10 + 'A';
		else
			ch = (value % (int)base) * -1 % 10 + 'a';
	}
	else
		ch = (value % (int)base) * -1 + '0';
	return (ch);
}

char			pos_value(t_ll value, unsigned base, t_printf *data)
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

char			result(t_ll value, unsigned base, t_printf *data)
{
	char ch;

	if (value < 0)
		ch = neg_value(value, base, data);
	else
		ch = pos_value(value, base, data);
	return (ch);
}

t_ll			new_value(t_ll value, unsigned *base, t_ll *val)
{
	if (*base == BIG_HEX)
		*base = 16;
	*val = value;
	return (value);
}
