/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:29:27 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:26:42 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		set_champ_byte_code(t_asm *asm_ctx)
{
	int		i;
	t_list	*token_l;

	i = 0;
	set_champ_code_size(asm_ctx);
	if (!(asm_ctx->champ_code =
	(unsigned char *)ft_memalloc(asm_ctx->champ_code_size)))
		return (0);
	token_l = asm_ctx->tokens;
	while (token_l)
	{
		set_token_byte_code(asm_ctx, (t_token *)(token_l->content), &i);
		token_l = token_l->next;
	}
	return (1);
}

int		create_champ(t_asm *asm_ctx)
{
	int	fd;
	int	magic;

	fd = open(asm_ctx->out_name, O_WRONLY | O_TRUNC | O_CREAT);
	if (fd < 0)
		return (0);
	magic = COREWAR_EXEC_MAGIC;
	if (asm_ctx->is_little_endian)
		magic = get_big_endian_int(magic);
	write(fd, &magic, 4);
	write(fd, asm_ctx->name, PROG_NAME_LENGTH);
	magic = 0;
	write(fd, &magic, 4);
	if (asm_ctx->is_little_endian)
		magic = get_big_endian_int(asm_ctx->champ_code_size);
	write(fd, &(magic), 4);
	magic = 0;
	write(fd, asm_ctx->comment, COMMENT_LENGTH);
	write(fd, &magic, 4);
	write(fd, asm_ctx->champ_code, asm_ctx->champ_code_size);
	close(fd);
	return (1);
}

int		assemble(t_asm *asm_ctx)
{
	set_champ_byte_code(asm_ctx);
	if (!create_champ(asm_ctx))
		return (0);
	return (1);
}
