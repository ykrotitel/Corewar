/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:40:44 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/19 17:01:15 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *ptr1;
	unsigned char *ptr2;

	ptr1 = (unsigned char*)s1;
	ptr2 = (unsigned char*)s2;
	if (n == 0)
		return (0);
	if (s1 == NULL && s2 == NULL)
		return (0);
	while (n != 1 && *ptr1 == *ptr2)
	{
		n--;
		ptr1++;
		ptr2++;
	}
	return (*ptr1 - *ptr2);
}
