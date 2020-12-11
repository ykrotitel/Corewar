/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:27:07 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		open_file(t_asm *asm_ctx, char *fname)
{
	int		fd;
	int		len;
	char	buf[1];

	if ((fd = open(fname, O_RDONLY)) < 0)
		return (0);
	len = ft_strlen(fname);
	if (!(fname[len - 1] == 's' && fname[len - 2] == '.'))
		throw_error(asm_ctx, "wrong input file", 0);
	asm_ctx->opened_fd = fd;
	if (!(asm_ctx->out_name = ft_strnew(len + 2)))
		throw_error(asm_ctx, "malloc error", 0);
	ft_memmove((void *)asm_ctx->out_name, (void *)fname, len - 1);
	ft_memmove((void *)(asm_ctx->out_name + len - 1), (void *)"cor", 3);
	if (lseek(fd, -1, SEEK_END) == -1L)
		throw_error(asm_ctx, "seek error", 0);
	if (!read(fd, buf, 1))
		throw_error(asm_ctx, "read error", 0);
	if (buf[0] != '\n')
		throw_error(asm_ctx, "missing newline at the end", 0);
	if (lseek(fd, 0, SEEK_SET) == -1L)
		throw_error(asm_ctx, "seek error", 0);
	return (1);
}
