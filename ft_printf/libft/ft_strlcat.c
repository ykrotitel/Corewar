/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 22:05:04 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/17 16:25:04 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t length_dst;

	if (size == 0)
		return (size + ft_strlen(src));
	length_dst = ft_strlen(dst);
	i = length_dst;
	j = 0;
	while (size - 1 > i && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	if (length_dst > size)
		return (size + ft_strlen(src));
	return (length_dst + ft_strlen(src));
}
