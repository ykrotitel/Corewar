/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:31:17 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/19 19:34:50 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstat(t_list *begin_list, int nbr)
{
	if (!begin_list)
		return (0);
	while (begin_list && nbr != 0)
	{
		begin_list = begin_list->next;
		nbr--;
	}
	return (begin_list);
}
