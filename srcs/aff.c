/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:07:01 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/09 19:41:25 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	aff(t_data *data, t_carriage **carriage, int32_t pos)
{
	int16_t r;

	r = data->arena[get_pos(pos)];
	if (data->a_flag)
		ft_printf("Aff: %c\n",
			(char)((*carriage)->registers[r - 1] % 256));
}
