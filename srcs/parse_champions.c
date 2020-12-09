/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:06:12 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/09 16:56:38 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	parse_magic_header(unsigned int *magic_header, int fd)
{
	uint32_t	i;
	uint8_t		byte;

	i = 0;
	while (i < 4)
	{
		*magic_header <<= (uint32_t)8;
		if ((read(fd, &byte, 1)) < 0)
			exit(18);
		*magic_header |= byte;
		i++;
	}
	if (*magic_header != COREWAR_EXEC_MAGIC)
		exit(17);
}

void	parse_champion_name(char (*name)[PROG_NAME_LENGTH + 1], int fd)
{
	int		i;
	char	byte;

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		if ((read(fd, &byte, 1)) < 0)
			exit(16);
		(*name)[i] = byte;
		i++;
	}
}

void	parse_champion_comment(char (*comment)[COMMENT_LENGTH + 1], int fd)
{
	int		i;
	char	byte;

	i = 0;
	while (i < COMMENT_LENGTH)
	{
		if ((read(fd, &byte, 1)) < 0)
			exit(15);
		(*comment)[i] = byte;
		i++;
	}
}

void	check_null_bytes(int fd)
{
	uint32_t bytes;

	if ((read(fd, &bytes, 4)) < 0 || bytes != 0)
		exit(14);
}

int		parse_file_name(const char *file_name)
{
	int		fd;
	char	*it;

	if (!(it = ft_strchr(file_name, '.')))
		exit(13);
	if (ft_strcmp(".cor", it))
		exit(11);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		exit(12);
	return (fd);
}

void	parse_exec_code_size(unsigned int *size, int fd)
{
	uint32_t	i;
	uint8_t		byte;

	i = 0;
	while (i < 4)
	{
		*size <<= (uint32_t)8;
		if ((read(fd, &byte, 1)) < 0)
			exit(19);
		*size |= byte;
		i++;
	}
	if (*size > CHAMP_MAX_SIZE || *size == 0)
		exit(20);
}

void	init_carriage(t_carriage **clist, uint32_t uid, size_t pos)
{
	t_carriage *carriage;

	if (!(carriage = malloc(sizeof(t_carriage))))
		exit(30);
	ft_bzero(carriage, sizeof(t_carriage));

	carriage->uid = uid;
	carriage->registers[0] = (int16_t)uid * -1;
	carriage->curr_pos = pos;
	carriage->next = NULL;
	if (*clist == NULL)
		*clist = carriage;
	else
	{
		carriage->next = *clist;
		*clist = carriage;
	}
}

void	parse_exec_code(t_data *data, int fd, uint8_t uid)
{
	uint8_t byte;
	size_t	i;

	i = (MEM_SIZE / data->players_num) * (uid - 1);
	init_carriage(&data->carriage_list, uid, i);
	// data->carriage_list->color = hui;
	while (read(fd, &byte, 1))
		data->arena[i++] = byte;
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

void	introduce_champions(t_champ champs[MAX_PLAYERS], int players_num)
{
	int i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < players_num)
	{
		ft_printf("* Player %u, weighing %u bytes, \"%s\" (\"%s\") !\n",
			champs[i].uid,
			champs[i].header.prog_size,
			champs[i].header.prog_name,
			champs[i].header.comment);
		i++;
	}
}

void	parse_champions(t_args (*champs)[MAX_PLAYERS], t_data *data, const char **av)
{
	int i;

	i = 0;
	while (i < data->players_num)
	{
		parse_champion(data, av[(*champs)[i].arg_it], i + 1);
		i++;
	}
	introduce_champions(data->champs, data->players_num);
}
