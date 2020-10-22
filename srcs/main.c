/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:52:05 by lmittie           #+#    #+#             */
/*   Updated: 2020/10/22 18:04:41 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 	print_usage()
{
	ft_printf("Usage:  ./corewar "
		   "[-dump nbr_cycles] [[-n number] champion1.cor] ...\n"
	 		"-dump nbr_cycles : Dumps memory after N cycles then exits\n"
			"-n number        : sets the number of the next player\n");
}

void 	init(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
}

int 	main(int ac, char **av)
{
	t_data	data;

	if (ac == 1)
		print_usage();
	else
	{
		init(&data);
		parse_arguments(ac, (const char**)av, &data);
	}
	return (0);
}