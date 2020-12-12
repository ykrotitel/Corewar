/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_base_buff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:44:50 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/16 19:51:47 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ftoa_base_buff(unsigned int value, t_arr *arr)
{
	size_t		len;
	t_ull		val;

	val = value;
	len = ft_numlen_u(value);
	while (value > 9)
	{
		arr->buff[arr->length + (len--) - 1] = (value % 10) + '0';
		value = value / 10;
	}
	arr->buff[arr->length + len - 1] = (value % 10) + '0';
	arr->length += (ft_numlen_u(val));
}
