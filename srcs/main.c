/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:52:05 by lmittie           #+#    #+#             */
/*   Updated: 2020/10/25 20:25:12 by acarlett         ###   ########.fr       */
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
	int		i;

	i = 0;
	if (ac == 1)
		print_usage();
	else
	{
		init(&data);
		parse_arguments(ac, (const char**)av, &data);
	}
	// while (data.champs->header.prog_size--)
	// {
	// 	printf("%02x ", data.arena[i++]);
	// }
	visual(&data);
	return (0);
}