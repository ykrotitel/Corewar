/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:09:00 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/18 21:23:46 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *a;

	if ((a = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (!content || !content_size)
	{
		a->content = NULL;
		a->content_size = 0;
	}
	else
	{
		if (!(a->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(a->content, content, content_size);
		a->content_size = content_size;
	}
	a->next = NULL;
	return (a);
}
