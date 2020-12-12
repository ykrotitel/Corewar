/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:43:54 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/06 21:06:44 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char			*result;
	size_t			len;

	len = ft_strlen(s1);
	if ((result = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	result[len] = '\0';
	while (len != 0)
	{
		result[len - 1] = s1[len - 1];
		len--;
	}
	return (result);
}
