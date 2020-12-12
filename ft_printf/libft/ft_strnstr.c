/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:52:34 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/09 20:53:05 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t length;

	i = 0;
	if (needle[0] == '\0' && (haystack[0] == '\0' || len == 0))
		return ((char *)haystack);
	if (*haystack == '\0' || !haystack)
		return (NULL);
	while (haystack[i] && len > 0)
	{
		j = 0;
		length = len;
		while (needle[j] && haystack[i + j] == needle[j] && (length - j) > 0)
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
		len--;
	}
	return (NULL);
}
