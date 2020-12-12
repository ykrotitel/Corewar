/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 17:31:43 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/19 21:44:04 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	size_t			i;
	char			*res;

	i = 0;
	if (!s || !(*s) || !f)
		return (NULL);
	if ((res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
		return (NULL);
	while (s[i])
	{
		res[i] = (*f)(s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
