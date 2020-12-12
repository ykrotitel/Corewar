/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:16:48 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/20 18:32:14 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcapitalize(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr != '\0')
	{
		if ((*ptr >= 'a' && *ptr <= 'z') || \
				(*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= '0' && *ptr <= '9'))
		{
			if (*ptr >= 'a' && *ptr <= 'z')
			{
				*ptr -= 32;
			}
			while ((*ptr >= 'a' && *ptr <= 'z') || \
					(*ptr >= 'A' && *ptr <= 'Z') ||
					(*ptr >= '0' && *ptr <= '9'))
			{
				ptr++;
				if (*ptr >= 'A' && *ptr <= 'Z')
					*ptr += 32;
			}
		}
		ptr++;
	}
	return (str);
}
