/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:35:07 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/10 21:30:08 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 	print_usage(void)
{
	ft_printf("Usage:  ./corewar "
			  "[-dump nbr_cycles] [-h mask] [-a] [-v]"
			  "<[-n number] champion1.cor]> <...>\n"
			  "-dump nbr_cycles : Dumps memory after N cycles then exits\n"
			  "-n number        : Sets the number of the next player\n"
			  "-a        		: Prints output from aff (hidden by default)\n"
			  "-v				: Visualization (ncurses)\n"
			  "-h mask		    : Print system info\n"
			  "masks:\n"
			  "1				: Show lives\n"
			  "2			  	: Show cycles\n"
			  "4				: Show operations\n");
}

void	print_arena_state(uint8_t (*arena)[MEM_SIZE])
{
	int i;
	int j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%s%#.4x : ", i ? "\n" : "0x", i);
		j = 0;
		while (j < 64)
			ft_printf("%.2x ", (*arena)[i + j++]);
		i += 64;
	}
}
