/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:15:28 by fmallist          #+#    #+#             */
/*   Updated: 2019/12/23 16:09:54 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				count_zeros(t_float *n)
{
	unsigned last;

	if (n->fractional.size_num == 0)
		return (0);
	last = ft_numlen_u(n->fractional.arr[n->fractional.size_num - 1]);
	return (52 - n->exp - 9 * (n->fractional.size_num - 1) - last);
}

int				count_zeros_ldbl(t_ldbl *n)
{
	unsigned last;

	if (n->fractional.size_num == 0)
		return (0);
	last = ft_numlen_u(n->fractional.arr[n->fractional.size_num - 1]);
	return (63 - n->exp - 9 * (n->fractional.size_num - 1) - last);
}

static void		add_one(t_arr *arr, char *flag, size_t len)
{
	*flag = 0;
	if (arr->buff[len - 1] == '9')
	{
		arr->buff[len - 1] = '0';
		*flag = 1;
	}
	else
		arr->buff[len - 1] += 1;
}

int				handle_f_dec(t_arr *arr, char num, char flag)
{
	int len;

	len = arr->length;
	if (num - 48 > 5)
		add_one(arr, &flag, len);
	else if (num - 48 == 5)
		if ((arr->buff[len - 1] - 48) % 2 != 0)
			add_one(arr, &flag, len);
	while (len-- > 0 && flag)
		add_one(arr, &flag, len + 1);
	if (flag)
		return (1);
	return (0);
}

int				handle_f_prec(t_arr *arr, t_arr *dec, t_printf *data)
{
	size_t	len;
	char	flag;
	char	num;

	len = arr->length - 1;
	flag = 0;
	if (arr->buff[len] - '0' >= 5 && arr->buff[len - 1] != '.')
		add_one(arr, &flag, len);
	len--;
	while (arr->buff[len-- - 1] != '.' && flag)
		add_one(arr, &flag, len + 1);
	num = arr->buff[1];
	arr->buff[arr->length-- - 1] = '\0';
	if (flag || data->precision == 1)
		flag = handle_f_dec(dec, num, flag);
	return (flag);
}
