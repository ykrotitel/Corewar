/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 20:40:24 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 20:44:16 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	parse_dump(uint32_t *dump, const char **av, int *i, int ac)
{
	if (*i + 1 != ac)
		*dump = ft_atoi(av[++(*i)]);
	else
		error_message("Invalid usage of \"-dump\" option\n");
	if (dump <= 0)
		error_message("Invalid usage of \"-dump\" option\n");
}

void	switch_champions(t_args *champs, int n, int arg_it)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (champs[i].arg_it == 0)
		{
			champs[i] = champs[n - 1];
			champs[n - 1].arg_it = arg_it;
			champs[n - 1].n_flag = 1;
			break ;
		}
		i++;
	}
	if (i == MAX_PLAYERS)
		error_message("Invalid usage of \"-n\" option\n");
}

void	parse_n_flag(int *i, int ac, const char **av, t_args *arg_it)
{
	int n;

	n = 0;
	if (*i + 1 != ac)
		n = ft_atoi(av[++(*i)]);
	else
		error_message("Invalid usage of \"-n\" option\n");
	if (n > MAX_PLAYERS || n <= 0 || arg_it[n - 1].n_flag)
		error_message("Invalid usage of \"-n\" option\n");
	if (arg_it[n - 1].arg_it)
		switch_champions(arg_it, n, ++(*i));
}

void	parse_flags(int *i, int ac, t_data *data, const char **av)
{
	if (!(ft_strcmp("-dump", av[*i])))
		parse_dump(&data->dump_cycles, av, i, ac);
	else if (!(ft_strcmp("-a", av[*i])))
		data->a_flag = 1;
	else if (!(ft_strcmp("-v", av[*i])))
		data->v_flag = 1;
	else if (!(ft_strcmp("-h", av[*i])))
	{
		if (*i + 1 != ac)
			data->h_flag = ft_atoi(av[++(*i)]);
		else
			error_message("Invalid usage of \"-h\" option\n");
	}
}
