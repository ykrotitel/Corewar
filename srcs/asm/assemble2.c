/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:29:27 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:26:53 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		set_champ_code_size(t_asm *asm_ctx)
{
	int	size;

	if (!asm_ctx->tokens || !asm_ctx->last_token)
		throw_error(asm_ctx, "source code is not present", 0);
	size = get_distance(asm_ctx->tokens, asm_ctx->last_token);
	size += get_token_size((t_token *)(asm_ctx->last_token->content));
	asm_ctx->champ_code_size = size;
	return (1);
}

int		get_big_endian_int(int n)
{
	int	res;

	res = ((n >> 24) & 0xff)
	| ((n >> 16) & 0xff) << 8
	| ((n >> 8) & 0xff) << 16
	| (n & 0xff) << 24;
	return (res);
}

void	set_byte_code(t_asm *asm_ctx, int data, int size, int *i)
{
	unsigned char *data_tmp;

	if (asm_ctx->is_little_endian)
		data = get_big_endian_int(data);
	data_tmp = (unsigned char *)&data;
	data_tmp += sizeof(int) - size;
	while (size-- > 0)
	{
		asm_ctx->champ_code[*i] = *data_tmp;
		data_tmp++;
		(*i)++;
	}
}

int		set_args_byte_code(t_asm *asm_ctx, t_list *arg_l, int dir_size, int *i)
{
	t_arg	*arg;
	int		type_code;
	int		offset;
	int		data;

	offset = 6;
	type_code = 0;
	while (arg_l)
	{
		arg = (t_arg *)arg_l->content;
		type_code |= (arg->type == T_IND ? 3 : arg->type) << offset;
		if (arg->value[0] == 'r')
			data = ft_atoi(arg->value + 1);
		else
			data = ft_atoi(arg->value);
		offset -= 2;
		if (arg->type == T_IND)
			set_byte_code(asm_ctx, data, 2, i);
		else if (arg->type == T_DIR)
			set_byte_code(asm_ctx, data, dir_size, i);
		else if (arg->type == T_REG)
			set_byte_code(asm_ctx, data, 1, i);
		arg_l = arg_l->next;
	}
	return (type_code);
}

int		set_token_byte_code(t_asm *asm_ctx, t_token *token, int *i)
{
	int	arg_type;
	int	arg_type_idx;

	arg_type = 0;
	if (!(token->operation.name))
		return (0);
	asm_ctx->champ_code[*i] = token->operation.id;
	*i += 1;
	if (token->operation.is_arg_type_code)
	{
		arg_type_idx = *i;
		(*i)++;
	}
	arg_type = set_args_byte_code(asm_ctx,
	token->args, get_dir_size(token->operation), i);
	if (token->operation.is_arg_type_code)
		asm_ctx->champ_code[arg_type_idx] = arg_type;
	return (1);
}
