/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_floats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:45:08 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/25 18:17:27 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_float_dec_bits(t_float *number, __uint128_t bits)
{
	int			i;

	i = 51;
	if (number->exp >= 0 && (bits != 0 || !((bits >> 63) & 1)))
		number->decimal.arr[0] = 1;
	number->decimal.size_num = 1;
	number->sign = bits >> 63;
	if (number->exp > 0)
		while (i > 51 - number->exp)
		{
			multiply_long_short(&number->decimal, 2);
			if (((bits >> (__uint128_t)i) & 1) && i >= 0)
				add_long_short(&number->decimal, 1);
			i--;
		}
}

void	init_float_bitfields(t_float *number, t_printf *data)
{
	int			i;
	__uint128_t	bits;

	bits = *(__uint128_t *)(&number->num);
	number->exp = ((bits >> 52) & 0x7FF) - 1023;
	init_float_dec_bits(number, bits);
	if (number->exp < 0)
	{
		number->fractional.size_num = 1;
		number->fractional = big_power_of_five(-number->exp);
	}
	i = 52 - number->exp;
	if (number->exp < 0)
		i = 52;
	while (--i >= 0)
	{
		multiply_long_short(&number->fractional, 10);
		if ((bits >> i) & 1)
			add_long_long(&number->fractional,
			big_power_of_five(52 - number->exp - i));
	}
	before_print_float(*number, data);
}

void	init_ldbl_dec_bits(t_ldbl *number, __uint128_t bits)
{
	int i;

	i = 62;
	if (number->exp >= 0 && (bits != 0 || !((bits >> 79) & 1)))
		number->decimal.arr[0] = 1;
	number->decimal.size_num = 1;
	number->sign = bits >> 79;
	if (number->exp > 0)
		while (i > 62 - number->exp)
		{
			multiply_long_short(&number->decimal, 2);
			if (((bits >> (__uint128_t)i) & 1) && i >= 0)
				add_long_short(&number->decimal, 1);
			i--;
		}
}

void	init_ldbl_bitfields(t_ldbl *number, t_printf *data)
{
	int			i;
	__uint128_t	bits;

	bits = *(__uint128_t *)(&number->num);
	number->exp = ((bits >> 64) & 0x7FFF) - 16383;
	init_ldbl_dec_bits(number, bits);
	if (number->exp < 0)
	{
		number->fractional.size_num = 1;
		number->fractional = big_power_of_five(-number->exp);
	}
	i = 63 - number->exp;
	if (number->exp < 0)
		i = 63;
	while (--i >= 0)
	{
		multiply_long_short(&number->fractional, 10);
		if ((bits >> i) & 1)
			add_long_long(&number->fractional,
			big_power_of_five(63 - number->exp - i));
	}
	before_print_ldbl(*number, data);
}

void	handle_floats(t_printf *data)
{
	t_float	fl;
	t_ldbl	ldbl;

	ft_bzero(&fl, sizeof(t_float));
	ft_bzero(&ldbl, sizeof(t_ldbl));
	if (data->size == BIGL)
	{
		ldbl.num = (long double)va_arg(data->ap, long double);
		data->type = FL;
		init_ldbl_bitfields(&ldbl, data);
	}
	else
	{
		fl.num = va_arg(data->ap, double);
		data->type = FL;
		init_float_bitfields(&fl, data);
	}
}
