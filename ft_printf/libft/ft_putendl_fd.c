/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:43:32 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/19 21:38:24 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putendl_fd(char const *s, int fd)
{
	if (fd < 0)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
