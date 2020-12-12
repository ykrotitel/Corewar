/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:52:13 by fmallist          #+#    #+#             */
/*   Updated: 2019/10/30 20:47:15 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	int			count;
	char		*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = ft_numlen(n, 10);
	if ((res = (char *)malloc(sizeof(char) * (count + 1))) == NULL)
		return (NULL);
	res[count--] = '\0';
	if (n == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (n < 0)
	{
		n = n * (-1);
		res[0] = '-';
	}
	while (n > 0)
	{
		res[count--] = '0' + (n % 10);
		n = n / 10;
	}
	return (res);
}
