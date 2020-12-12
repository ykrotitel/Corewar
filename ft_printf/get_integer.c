/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_integer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:14:42 by fmallist          #+#    #+#             */
/*   Updated: 2019/12/25 16:03:01 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_size_of_int(t_printf *data, long long *n)
{
	if (data->size & H)
		*n = (short)*n;
	else if (data->size & HH)
		*n = (char)*n;
	else if (!(data->size & L) && !(data->size & LL))
		*n = (int)*n;
}

void		get_integer(t_printf *data, long long *n)
{
	*n = va_arg(data->ap, t_ll);
	if (data->type == OCTAL || data->type == HEX
		|| data->type == BIG_HEX)
	{
		if (data->size & H)
			*n = (unsigned short)*n;
		else if (data->size & HH)
			*n = (unsigned char)*n;
		else if (!(data->size & L) && !(data->size & LL))
			*n = (unsigned int)*n;
		if (data->flag & PLUS)
			data->flag ^= PLUS;
		else if (data->flag & SPACE)
			data->flag ^= SPACE;
	}
	else
		get_size_of_int(data, n);
}
