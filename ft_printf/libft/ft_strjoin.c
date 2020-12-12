/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:33:43 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/17 20:11:44 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	size_t			size;

	if (s1 && s2)
	{
		size = ft_strlen(s1) + ft_strlen(s2);
		if ((res = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
			return (NULL);
		*res = '\0';
		return (ft_strcat(ft_strcat(res, (char *)s1), (char *)s2));
	}
	return (NULL);
}
