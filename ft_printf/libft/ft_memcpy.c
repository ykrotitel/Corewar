/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:35:00 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/05 19:26:00 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *p1;
	unsigned char *p2;

	if (dst == NULL && src == NULL)
		return (NULL);
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	while (n != 0)
	{
		*p1 = *p2;
		p1++;
		p2++;
		n--;
	}
	return (dst);
}
