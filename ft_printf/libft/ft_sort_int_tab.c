/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:38:49 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/19 19:50:36 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_sort_int_tab(int *tab, int size)
{
	int i;
	int tmp;
	int j;

	i = -1;
	j = -1;
	tmp = 0;
	while (++j < size)
	{
		i = -1;
		while (++i < size)
		{
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
}
