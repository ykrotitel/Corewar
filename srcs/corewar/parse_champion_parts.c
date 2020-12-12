/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion_parts.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 20:50:20 by lmittie           #+#    #+#             */
/*   Updated: 2020/12/11 20:51:54 by lmittie          ###   ########.fr       */
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
			error_message("Invalid .cor file\n");
		*magic_header |= byte;
		i++;
	}
	if (*magic_header != COREWAR_EXEC_MAGIC)
		error_message("Invalid magic header\n");
}

void	parse_champion_name(char (*name)[PROG_NAME_LENGTH + 1], int fd)
{
	int		i;
	char	byte;

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		if ((read(fd, &byte, 1)) < 0)
			error_message("Invalid .cor file\n");
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
			error_message("Invalid .cor file\n");
		(*comment)[i] = byte;
		i++;
	}
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
			error_message("Invalid .cor file\n");
		*size |= byte;
		i++;
	}
	if (*size > CHAMP_MAX_SIZE || *size == 0)
		error_message("Invalid code size\n");
}

void	parse_exec_code(t_data *data, int fd, uint8_t uid)
{
	uint8_t byte;
	size_t	i;

	i = (MEM_SIZE / data->players_num) * (uid - 1);
	init_carriage(&data->carriage_list, uid, i);
	while (read(fd, &byte, 1))
		data->arena[i++] = byte;
}
