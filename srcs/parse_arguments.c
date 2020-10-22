/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:12:59 by lmittie           #+#    #+#             */
/*   Updated: 2020/10/22 18:12:59 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	switch_champions(t_args (*champs)[MAX_PLAYERS], int n, int arg_it)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if ((*champs)[i].arg_it == 0)
		{
			(*champs)[i] = (*champs)[n - 1];
			(*champs)[n - 1].arg_it = arg_it;
			(*champs)[n - 1].n_flag = 1;
			break ;
		}
		i++;
	}
	if (i == MAX_PLAYERS)
		exit(1);
}

void	add_arg_it(t_args (*champs)[MAX_PLAYERS], int arg_it)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if ((*champs)[i].arg_it == 0)
		{
			(*champs)[i].arg_it = arg_it;
			break ;
		}
		i++;
	}
	if (i == MAX_PLAYERS)
		exit(1);
}

void	handle_arg_it(t_args (*champs)[MAX_PLAYERS], int players_num)
{
	int		i;

	i = 0;
	while (i < players_num)
	{
		if ((*champs)[i].arg_it == 0)
			break ;
		i++;
	}
	if (i != players_num)
		exit(1);
}

void	parse_arguments(int ac, const char **av, t_data *data)
{
	int		i;
	int		n;
	t_args	arg_it[MAX_PLAYERS];

	i = 1;
	ft_bzero(arg_it, sizeof(t_args) * MAX_PLAYERS);
	while (i < ac)
	{
		if (!(ft_strcmp("-dump", av[i])))
		{
			if (i + 1 != ac)
				data->dump_cycles = ft_atoi(av[++i]);
			else
				exit(1);
			if (data->dump_cycles <= 0)
				exit(1);
		}
		else if (!(ft_strcmp("-n", av[i])))
		{
			if (i + 1 != ac)
				n = ft_atoi(av[++i]);
			else
				exit(1);
			if (n > MAX_PLAYERS || n <= 0 || arg_it[n - 1].n_flag)
				exit(1);
			if (i + 1 == ac)
				exit(1);
			if (arg_it[n - 1].arg_it)
				switch_champions(&arg_it, n, ++i);
			data->players_num++;
		}
		else
		{
			add_arg_it(&arg_it, i);
			data->players_num++;
		}
		i++;
	}
	handle_arg_it(&arg_it, data->players_num);
	parse_champions(&arg_it, data, av);
}
