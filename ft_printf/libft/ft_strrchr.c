/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:29:46 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/19 22:02:42 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	size_t len;

	len = ft_strlen(s);
	while (len--)
	{
		if (s[len] == (char)c)
			return ((char *)(s + len));
	}
	if (c == '\0')
		return ((char*)(s + ft_strlen(s)));
	return (NULL);
}
