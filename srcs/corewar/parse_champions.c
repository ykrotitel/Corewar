/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:06:12 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 21:55:34 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_null_bytes(int fd)
{
	uint32_t bytes;

	if ((read(fd, &bytes, 4)) < 0 || bytes != 0)
		error_message("No null bytes at bytecode\n");
}

int		parse_file_name(const char *file_name)
{
	int		fd;
	char	*it;

	if (!(it = ft_strchr(file_name, '.')))
		error_message("Invalid expansion\n");
	if (ft_strcmp(".cor", it))
		error_message("Invalid expansion\n");
	if ((fd = open(file_name, O_RDONLY)) < 0)
		error_message("Cannot open file for reading\n");
	return (fd);
}

void	parse_champion(t_data *data, const char *file_name, uint8_t uid)
{
	int		fd;

	fd = parse_file_name(file_name);
	data->champs[uid - 1].uid = uid;
	parse_magic_header(&data->champs[uid - 1].header.magic, fd);
	parse_champion_name(&data->champs[uid - 1].header.prog_name, fd);
	check_null_bytes(fd);
	parse_exec_code_size(&data->champs[uid - 1].header.prog_size, fd);
	parse_champion_comment(&data->champs[uid - 1].header.comment, fd);
	check_null_bytes(fd);
	parse_exec_code(data, fd, uid);
}

void	parse_champions(t_args *champs, t_data *data, const char **av)
{
	int i;

	i = 0;
	while (i < data->players_num)
	{
		parse_champion(data, av[champs[i].arg_it], i + 1);
		i++;
	}
	introduce_champions(data->champs, data->players_num);
}
