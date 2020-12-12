/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:46:23 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/09 20:34:27 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	long int		result;
	int				neg;

	result = 0;
	neg = 1;
	while (*str == 32 || *str == '\t' || *str == '\n' ||
				*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		str++;
		neg = -1;
	}
	if (*str == '+' && neg == 1)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	if (result > result * 10)
		return (-(neg == 1));
	return (result * neg);
}
