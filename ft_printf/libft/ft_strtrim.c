/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 20:14:10 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/17 21:32:31 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	char		*res;
	size_t		start;
	size_t		end;
	size_t		i;

	if (!s)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s);
	while ((s[start] == 32 || s[start] == '\t' || s[start] == '\n') && s[start])
		start++;
	while ((s[end - 1] == 32 || s[end - 1] == '\t' || s[end - 1] == '\n')
				&& s[end - 1])
		end--;
	if (!(res = ft_strnew(start < end ? (end - start) : 0)))
		return (NULL);
	while (start < end)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
