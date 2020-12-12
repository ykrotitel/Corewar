/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:46:55 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/19 16:51:31 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char *str;

	if (size + 1 == 0)
		return (NULL);
	if ((str = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	ft_memset(str, '\0', size + 1);
	return (str);
}
