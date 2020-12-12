/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:14:34 by fmallist          #+#    #+#             */
/*   Updated: 2019/12/23 17:15:09 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned	g_arr[10] = {5, 25, 125, 625, 3125, 15625,
	78125, 390625, 1953125, 9765625};

void		add_long_short(t_num *a, unsigned b)
{
	unsigned	temp;
	unsigned	tmp;
	int			i;

	tmp = 0;
	i = 0;
	while (a->arr[i] != 0)
	{
		temp = a->arr[i];
		a->arr[i] = (tmp + a->arr[i] + b) % BASE;
		tmp = (tmp + temp + b) / BASE;
		i++;
		b = 0;
	}
	if (b != 0)
		tmp = b;
	if (tmp > 0 && a->arr[i] == 0)
		a->size_num++;
	a->arr[i] += tmp;
}

void		multiply_long_short(t_num *a, unsigned b)
{
	unsigned		i;
	unsigned long	tmp;
	unsigned		temp;
	unsigned long	res;

	i = 0;
	tmp = 0;
	while (i < a->size_num)
	{
		temp = a->arr[i];
		res = ((unsigned long)a->arr[i] * (unsigned long)b + tmp) % BASE;
		a->arr[i] = (unsigned)res;
		tmp = ((unsigned long)temp * (long)b + tmp) / BASE;
		i++;
	}
	a->arr[a->size_num] = (unsigned)tmp;
	a->size_num = (tmp != 0) ? a->size_num + 1 : a->size_num;
}

void		add_long_long(t_num *a, t_num b)
{
	int				size;
	int				i;
	unsigned int	tmp;
	unsigned int	temp;

	if (a->size_num > b.size_num)
		size = a->size_num;
	else
		size = b.size_num;
	i = 0;
	tmp = 0;
	while (i < size)
	{
		temp = a->arr[i];
		a->arr[i] = (tmp + a->arr[i] + b.arr[i]) % BASE;
		tmp = (tmp + temp + b.arr[i]) / BASE;
		i++;
	}
	a->arr[i + 1] = tmp;
	a->size_num = (tmp == 0) ? size : size + 1;
}

static void	big_power_of_five_extra(unsigned *power, t_num *n)
{
	if (*power >= 10)
	{
		multiply_long_short(n, g_arr[9]);
		*power -= 10;
	}
	else
	{
		multiply_long_short(n, g_arr[*power - 1]);
		*power -= *power;
	}
}

t_num		big_power_of_five(unsigned power)
{
	t_num		n;

	ft_bzero(&n, sizeof(t_num));
	n.arr[0] = 1;
	n.size_num = 1;
	if (power == 0)
		return (n);
	if (power == 1)
	{
		n.arr[0] = g_arr[0];
		return (n);
	}
	else if (power <= 10)
	{
		n.arr[0] = g_arr[power - 1];
		return (n);
	}
	while (power > 0)
		big_power_of_five_extra(&power, &n);
	return (n);
}
