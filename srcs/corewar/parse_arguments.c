/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:12:59 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/09 18:08:44 by lmittie          ###   ########.fr       */
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

void	parse_dump(uint32_t *dump, const char **av, int *i, int ac)
{
	if (*i + 1 != ac)
		*dump = ft_atoi(av[++(*i)]);
	else
		exit(1);
	if (dump <= 0)
		exit(1);
}

void	parse_n_flag(int *i, int ac, const char **av, t_args (*arg_it)[MAX_PLAYERS])
{
	int n;

	if (*i + 1 != ac)
		n = ft_atoi(av[++(*i)]);
	else
		exit(1);
	if (n > MAX_PLAYERS || n <= 0 || (*arg_it)[n - 1].n_flag)
		exit(1);
	if ((*arg_it)[n - 1].arg_it)
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
			exit(1);
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
			parse_n_flag(&i, ac, av, &arg_it);
			data->players_num++;
		}
		else if (!(ft_strncmp("-", av[i], 1)))
			parse_flags(&i, ac, data, av);
		else
		{
			add_arg_it(&arg_it, i);
			data->players_num++;
		}
	}
	handle_arg_it(&arg_it, data->players_num);
	parse_champions(&arg_it, data, av);
	handle_color_code(data);
}
