/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:50:26 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/06 19:58:26 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *s1;
	unsigned char *s2;

	if (dst == NULL && src == NULL)
		return (NULL);
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	if (s1 < s2)
		return (ft_memcpy(dst, src, len));
	else
		while (len != 0)
		{
			s1[len - 1] = s2[len - 1];
			len--;
		}
	return (dst);
}
