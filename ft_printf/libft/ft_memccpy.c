/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:50:28 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/05 20:02:48 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *s1;
	unsigned char *s2;

	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	while (n != 0)
	{
		*s1 = *s2;
		if (*s2 == (unsigned char)c)
			return (s1 + 1);
		s1++;
		s2++;
		n--;
	}
	return (NULL);
}
