/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_float_arrays.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 16:04:29 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/23 17:12:56 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_float_dec_array(t_float number, t_printf *data, t_arr *dec)
{
	int				i;
	int				j;

	j = 0;
	i = number.decimal.size_num - 1;
	if (number.sign)
		dec->buff[dec->length++] = '-';
	if (data->flag & PLUS && !number.sign)
		dec->buff[dec->length++] = '+';
	if (data->flag & SPACE && !number.sign)
		dec->buff[dec->length++] = ' ';
	while (i >= 0)
	{
		j = 9 - ft_numlen_u(number.decimal.arr[i]);
		if ((unsigned)i == number.decimal.size_num - 1)
			j = 0;
		while (j-- > 0)
			dec->buff[dec->length++] = '0';
		ftoa_base_buff(number.decimal.arr[i], dec);
		i--;
	}
}

static void	handle_precition(t_float number,
t_printf *data, int *prec, t_arr *frac)
{
	unsigned zeros;

	frac->buff[frac->length++] = '.';
	if (data->precision == 0)
		data->precision = 6;
	if (data->precision == -1)
		data->precision = 0;
	data->precision++;
	*prec = data->precision;
	zeros = count_zeros(&number);
	while (zeros-- && (*prec)--)
		frac->buff[frac->length++] = '0';
}

static void	concat_array(int i, int *prec, t_num num, t_arr *frac)
{
	unsigned int	base;
	int				k;

	base = 1;
	if (i == (int)num.size_num - 1)
	{
		k = ft_numlen_u(num.arr[i]);
		while (--k)
			base = base * 10;
	}
	else
		base = 100000000;
	if (((unsigned)i != num.size_num - 1 && *prec < 9) ||
	(*prec < (int)ft_numlen_u(num.arr[i]) &&
	(unsigned)i == num.size_num - 1))
		while ((*prec)-- > 0)
		{
			if (base != 0 && (num.arr[i] / base) % 10 == 0)
				frac->buff[frac->length++] = '0';
			else if (base != 0)
				frac->buff[frac->length++] = (num.arr[i] / base) % 10 + '0';
			base /= 10;
		}
	else
		ftoa_base_buff(num.arr[i], frac);
}

static void	if_precition_exists(int i, int *prec, t_num num, t_arr *frac)
{
	int j;

	while (i >= 0 && *prec > 0)
	{
		j = 9 - ft_numlen_u(num.arr[i]);
		if ((unsigned)i == num.size_num - 1)
			j = 0;
		while (j-- > 0 && *prec >= 9)
			frac->buff[frac->length++] = '0';
		concat_array(i, prec, num, frac);
		if ((unsigned)i == num.size_num - 1)
			*prec -= ft_numlen_u(num.arr[i]);
		else
			*prec -= 9;
		i--;
	}
	if ((*prec)-- > 0)
		frac->buff[frac->length++] = '0';
}

void		before_print_float(t_float number, t_printf *data)
{
	int				i;
	int				prec;
	t_arr			dec;
	t_arr			frac;

	ft_bzero(&dec, sizeof(t_arr));
	ft_bzero(&frac, sizeof(t_arr));
	fill_float_dec_array(number, data, &dec);
	i = number.fractional.size_num - 1;
	handle_precition(number, data, &prec, &frac);
	if (prec <= 0)
		i = handle_f_prec(&frac, &dec, data);
	if (i >= 0 && prec > 0)
	{
		if_precition_exists(i, &prec, number.fractional, &frac);
		i = handle_f_prec(&frac, &dec, data);
	}
	else
	{
		while (prec-- - 1 > 0)
			frac.buff[frac.length++] = '0';
		i = 0;
	}
	data->precision = --prec;
	print_float(&dec, &frac, data, i);
}
