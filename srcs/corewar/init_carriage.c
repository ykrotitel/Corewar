/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_carriages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 20:47:31 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 20:49:07 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_carriage(t_carriage **clist, uint32_t uid, size_t pos)
{
	t_carriage *carriage;

	if (!(carriage = malloc(sizeof(t_carriage))))
		error_message("Malloc error\n");
	ft_bzero(carriage, sizeof(t_carriage));
	carriage->uid = uid;
	carriage->registers[0] = (int16_t)uid * -1;
	carriage->curr_pos = pos;
	carriage->next = NULL;
	if (*clist == NULL)
		*clist = carriage;
	else
	{
		carriage->next = *clist;
		*clist = carriage;
	}
}
