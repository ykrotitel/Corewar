/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:26:58 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	throw_line_error(t_asm *asm_ctx,
const char *msg1, const char *msg2, int line_num)
{
	if (msg1)
		ft_putstr(msg1);
	if (msg2)
	{
		ft_putstr(" ");
		ft_putstr(msg2);
	}
	ft_putstr(" at line: ");
	ft_putnbr(line_num);
	ft_putstr("\n");
	if (asm_ctx)
		free_asm(asm_ctx);
	exit(-1);
}

void	throw_error(t_asm *asm_ctx, const char *msg1, const char *msg2)
{
	if (msg1)
		ft_putstr(msg1);
	if (msg2)
	{
		ft_putstr(" ");
		ft_putstr(msg2);
	}
	ft_putstr("\n");
	if (asm_ctx)
		free_asm(asm_ctx);
	exit(-1);
}

t_asm	*init(void)
{
	t_asm			*asm_ctx;
	unsigned int	i;
	unsigned char	*c;

	i = 1;
	c = (unsigned char*)&i;
	if (!(asm_ctx = ft_memalloc(sizeof(t_asm))))
		return (0);
	init_op_tab(asm_ctx);
	asm_ctx->name = ft_strdup("");
	asm_ctx->comment = ft_strdup("");
	asm_ctx->cmd_mode = -1;
	asm_ctx->champ_code_size = 0;
	asm_ctx->line_count = 1;
	asm_ctx->was_comment = 0;
	asm_ctx->was_name = 0;
	if (*c)
		asm_ctx->is_little_endian = 1;
	else
		asm_ctx->is_little_endian = 0;
	asm_ctx->is_little_endian = 1;
	return (asm_ctx);
}

int		main(int argc, char **argv)
{
	t_asm	*asm_ctx;

	if (argc != 2)
		throw_error(0, "count of files is not valid", 0);
	if (!(asm_ctx = init()))
		throw_error(0, "error while creating main context", 0);
	if (!(open_file(asm_ctx, argv[1])))
		throw_error(asm_ctx, "cant open file", 0);
	if (!set_header_command(asm_ctx))
		throw_error(asm_ctx, "some error while reading header", 0);
	if (!set_header_command(asm_ctx))
		throw_error(asm_ctx, "some error while reading header", 0);
	if (!parse(asm_ctx, 0))
		throw_error(asm_ctx, "some error while parsing\n", 0);
	if (!resolve_labels(asm_ctx))
		throw_error(asm_ctx, "error when resolving labels\n", 0);
	if (!assemble(asm_ctx))
		throw_error(asm_ctx, "some error while parsing\n", 0);
	ft_putstr("Writing output program to ");
	ft_putstr(asm_ctx->out_name);
	ft_putchar('\n');
	free_asm(asm_ctx);
}
