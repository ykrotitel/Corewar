/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_specifiers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 20:21:38 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/25 17:14:47 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			get_flags(t_printf *data, const char **f)
{
	if ((**f == '#' || **f == '-' || **f == '+'
							|| **f == ' ' || **f == '0'))
	{
		while ((**f == '#' || **f == '-' || **f == '+'
								|| **f == ' ' || **f == '0'))
		{
			if (!(data->flag & SHARP) && **f == '#')
				data->flag |= SHARP;
			if (!(data->flag & ZERO) && **f == '0')
				data->flag |= ZERO;
			else if (data->flag & ZERO && **f == '0' && *(*f - 1) == '0')
				data->flag ^= ZERO;
			if (!(data->flag & PLUS) && **f == '+')
				data->flag |= PLUS;
			if (!(data->flag & MINUS) && **f == '-')
				data->flag |= MINUS;
			if (!(data->flag & SPACE) && **f == ' ')
				data->flag |= SPACE;
			*f += 1;
		}
		if (data->flag & ZERO && (data->flag & MINUS))
			data->flag ^= ZERO;
		if (data->flag & SPACE && data->flag & PLUS)
			data->flag ^= SPACE;
	}
}

void			get_width(t_printf *data, const char **format)
{
	if (**format == '*')
	{
		data->width = va_arg(data->ap, int);
		*format += 1;
	}
	if (**format && ft_isdigit(**format))
	{
		data->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			*format += 1;
		if (**format == '*')
		{
			data->width = va_arg(data->ap, int);
			*format += 1;
		}
	}
	if (data->width < 0)
	{
		data->flag |= MINUS;
		data->width *= -1;
	}
}

void			get_precision(t_printf *data, const char **format)
{
	while (**format == '.')
	{
		*format += 1;
		data->precision = ft_atoi(*format);
		if (**format == '0' && data->precision == 0)
			data->precision = -1;
		if (ft_isalpha(**format) && data->precision == 0)
			data->precision = -1;
		while (ft_isdigit(**format))
			*format += 1;
		if (**format == '*')
		{
			data->precision = va_arg(data->ap, int);
			*format += 1;
			if (data->precision < 0)
				data->precision = 0;
			else if (data->precision == 0)
				data->precision = -1;
		}
	}
}

void			handle_undefined_behavior(t_printf *data, const char **format)
{
	get_flags(data, format);
	while (**format && (**format == 'h' || **format == 'l' || **format == 'z'
	|| **format == 'j' || **format == 'L'))
	{
		if (**format == 'h' && *(*format + 1) == 'h' &&
		!(data->size & L || data->size & LL))
			data->size = HH;
		else if (**format == 'l' && *(*format + 1) == 'l')
			data->size = LL;
		else if (**format == 'h' && !(data->size & L || data->size & LL))
			data->size = H;
		else if (**format == 'l' || **format == 'z' || **format == 'j')
			data->size = L;
		else if (**format == 'L')
			data->size = BIGL;
		*format += 1;
	}
}

int				get_size(t_printf *data, const char **format)
{
	if (**format == 'h' && *(*format + 1) == 'h')
		data->size = HH;
	else if (**format == 'l' && *(*format + 1) == 'l')
		data->size = LL;
	else if (**format == 'h')
		data->size = H;
	else if (**format == 'l' || **format == 'z' || **format == 'j')
		data->size = L;
	else if (**format == 'L')
		data->size = BIGL;
	if (data->size & H || data->size & BIGL || data->size & L)
		*format += 1;
	else if ((data->size & HH) || (data->size & LL))
		*format += 2;
	if (**format != 'c' && **format != 's' && **format != 'p'
	&& **format != 'd' && **format != 'i' && **format != 'o' &&
	**format != 'u' && **format != 'x' && **format != 'X')
		handle_undefined_behavior(data, format);
	return (1);
}
