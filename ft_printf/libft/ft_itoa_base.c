/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:26:07 by exam              #+#    #+#             */
/*   Updated: 2019/10/30 20:48:49 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	result(long value, int base)
{
	char ch;

	if (value < 0)
	{
		if (value % base <= -10)
			ch = (value % base) * -1 % 10 + 'A';
		else
			ch = (value % base) * -1 + '0';
	}
	else
	{
		if (value % base >= 10)
			ch = (value % base) % 10 + 'A';
		else
			ch = (value % base) + '0';
	}
	return (ch);
}

char		*ft_itoa_base(long value, int base)
{
	int		len;
	char	*str;

	len = ft_numlen(value, base);
	if (!(str = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	str[len - 1] = '\0';
	len--;
	while (value > base || value < -base)
	{
		str[len - 1] = result(value, base);
		len--;
		value = value / base;
	}
	if (value == base || value == -base)
	{
		str[len - 1] = '0';
		str[len - 2] = '1';
		len = len - 2;
	}
	else
		str[len - 1] = result(value, base);
	if (value < 0 && base == 10)
		str[--len - 1] = '-';
	return (&str[0]);
}
