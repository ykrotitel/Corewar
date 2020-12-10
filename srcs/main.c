/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:52:05 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/10 21:27:05 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->cycles_to_die = CYCLE_TO_DIE;
	data->carriage_list = NULL;
}

int		main(int ac, char **av)
{
	t_data	data;

	if (ac == 1)
		print_usage();
	else
	{
		init(&data);
		parse_arguments(ac, (const char**)av, &data);
		game(&data);
	}
	return (0);
}
