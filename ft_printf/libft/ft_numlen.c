/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:44:48 by fmallist          #+#    #+#             */
/*   Updated: 2019/10/30 20:44:54 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_numlen(long long val, unsigned base)
{
	size_t len;

	len = 0;
	if ((val < 0 && base == 10) || val == 0)
		len++;
	if (val != 0)
	{
		val = val / base;
		len++;
	}
	if (val < 0)
		val *= -1;
	while (val > 0)
	{
		val = val / base;
		len++;
	}
	return (len);
}
