/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:54:13 by acarlett          #+#    #+#             */
/*   Updated: 2020/12/11 20:10:49 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int		ft_c_b(char *buff, char c)
{
	int i;

	i = 0;
	if (c == '\n')
		while (buff[i])
		{
			if (buff[i] == c)
				return (i);
			i++;
		}
	else
		while (1)
		{
			if (buff[i] == c)
				return (i);
			i++;
		}
	return (-1);
}

static	int		ft_error(char **a)
{
	if (a && *a)
		free(*a);
	return (-1);
}

static int		g_n_l_two(t_params *p, char *a[10240], int fd, char **line)
{
	if (p->i == -1)
		return (-1);
	if (p->i == 0 && (!a[fd] || !a[fd][0]))
		return (0);
	if (p->i == 0)
		p->c = '\0';
	if (!(*line = (char *)malloc(sizeof(char) * (ft_c_b(a[fd], p->c) + 1))))
		return (-1);
	if (!ft_strncpy(*line, a[fd], (size_t)(ft_c_b(a[fd], p->c))))
		return (ft_error(&a[fd]));
	(*line)[ft_c_b(a[fd], p->c)] = '\0';
	if (p->c == '\n' && !(p->tmp = ft_strdup(ft_strchr(a[fd], p->c) + 1)))
		return (ft_error(&a[fd]));
	if (p->c == '\0' && !(p->tmp = ft_strdup(ft_strchr(a[fd], p->c))))
		return (ft_error(&a[fd]));
	free(a[fd]);
	a[fd] = p->tmp;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	t_params		p;
	char			buff[BUFF_SIZE + 1];
	static char		*a[10240];

	p.c = '\n';
	if (fd > 10240 || fd < 0)
		return (-1);
	p.i = -2;
	if (!a[fd] && !(a[fd] = ft_strnew(1)))
		return (-1);
	if (ft_c_b(a[fd], p.c) == -1)
		while ((p.i = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[p.i] = '\0';
			if (!(p.tmp = ft_strjoin(a[fd], buff)))
				return (ft_error(&a[fd]));
			free(a[fd]);
			a[fd] = p.tmp;
			if (ft_c_b(buff, p.c) >= 0)
				break ;
		}
	return (g_n_l_two(&p, a, fd, &*line));
}
