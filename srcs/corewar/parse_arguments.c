/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:12:59 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 20:44:16 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add_arg_it(t_args *champs, int arg_it)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (champs[i].arg_it == 0)
		{
			champs[i].arg_it = arg_it;
			break ;
		}
		i++;
	}
	if (i == MAX_PLAYERS)
		error_message("Too much players\n");
}

void	handle_arg_it(t_args *champs, int players_num)
{
	int		i;

	i = 0;
	while (i < players_num)
	{
		if (champs[i].arg_it == 0)
			break ;
		i++;
	}
	if (i != players_num)
		error_message("Invalid usage of \"-n\" option");
}

void	handle_color_code(t_data *data)
{
	t_carriage	*tmp;
	int			i;

	tmp = data->carriage_list;
	i = 0;
	while (tmp != NULL)
	{
		tmp->color_code = data->players_num - i;
		i++;
		tmp = tmp->next;
	}
}

void	parse_arguments(int ac, const char **av, t_data *data)
{
	int		i;
	t_args	arg_it[MAX_PLAYERS];

	i = 0;
	ft_bzero(arg_it, sizeof(t_args) * MAX_PLAYERS);
	while (++i < ac)
	{
		if (!(ft_strcmp("-n", av[i])))
		{
			parse_n_flag(&i, ac, av, arg_it);
			data->players_num++;
		}
		else if (!(ft_strncmp("-", av[i], 1)))
			parse_flags(&i, ac, data, av);
		else
		{
			add_arg_it(arg_it, i);
			data->players_num++;
		}
	}
	handle_arg_it(arg_it, data->players_num);
	parse_champions(arg_it, data, av);
	handle_color_code(data);
}
