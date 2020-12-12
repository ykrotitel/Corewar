/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:08:42 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/24 18:13:26 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			read_fd(t_printf *data, const char **f)
{
	if (ft_strnstr(*f, "{fd}", 4) && handle_overflow_buffer(data, 4))
	{
		data->fd = va_arg(data->ap, int);
		*f = *f + 4;
	}
	else if (ft_strnstr(*f, "{/fd}", 5) && handle_overflow_buffer(data, 5))
	{
		handle_overflow_buffer(data, 5000);
		data->fd = 1;
		*f = *f + 5;
	}
	else
		return (0);
	return (1);
}

int			reset_color(t_printf *data, const char **f)
{
	if (ft_strnstr(*f, "{cyan}", 6) && handle_overflow_buffer(data, 7))
	{
		ft_strcpy(&data->buff[data->length], "\x1b[36m");
		data->length += 5;
		*f = *f + 6;
	}
	else if (ft_strnstr(*f, "{yellow}", 8) && handle_overflow_buffer(data, 9))
	{
		ft_strcpy(&data->buff[data->length], "\x1b[33m");
		data->length += 5;
		*f = *f + 8;
	}
	else if (ft_strnstr(*f, "{eoc}", 5) && handle_overflow_buffer(data, 5))
	{
		ft_strcpy(&data->buff[data->length], "\x1b[0m");
		data->length += 4;
		*f = *f + 5;
	}
	else if (!read_fd(data, f))
		return (0);
	return (1);
}

int			read_color(t_printf *data, const char **f)
{
	if (ft_strnstr(*f, "{red}", 5) && handle_overflow_buffer(data, 5))
	{
		ft_strcpy(&data->buff[data->length], "\x1b[31m");
		data->length += 5;
		*f = *f + 5;
	}
	else if (ft_strnstr(*f, "{green}", 7) && handle_overflow_buffer(data, 7))
	{
		ft_strcpy(&data->buff[data->length], "\x1b[32m");
		data->length += 5;
		*f = *f + 7;
	}
	else if (ft_strnstr(*f, "{blue}", 6) && handle_overflow_buffer(data, 6))
	{
		ft_strcpy(&data->buff[data->length], "\x1b[34m");
		data->length += 5;
		*f = *f + 6;
	}
	else if (!reset_color(data, f))
		return (0);
	return (1);
}
