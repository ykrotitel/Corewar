/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:27:03 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	free_label(void *label_v, size_t label_size)
{
	t_label	*label;

	if (label_v)
	{
		label = (t_label *)label_v;
		ft_strdel(&label->name);
		ft_memdel((void **)&label);
		label_size += 1;
	}
}

void	free_arg(void *arg_v, size_t arg_size)
{
	t_arg	*arg;

	if (arg_v)
	{
		arg = (t_arg *)arg_v;
		ft_strdel(&arg->value);
		ft_memdel((void **)&arg);
		arg_size += 1;
	}
}

void	free_token(void *token_v, size_t token_size)
{
	t_token	*token;

	if (token_v)
	{
		token = (t_token *)token_v;
		if (token->args)
			ft_lstdel(&token->args, &free_arg);
		if (token->labels)
			ft_lstdel(&token->labels, &free_label);
		ft_memdel((void **)&token);
		token_size += 1;
	}
}

void	free_asm(t_asm *asm_ctx)
{
	close(asm_ctx->opened_fd);
	ft_strdel(&(asm_ctx->name));
	ft_strdel(&(asm_ctx->comment));
	ft_strdel(&(asm_ctx->out_name));
	if (asm_ctx->tokens)
		ft_lstdel(&asm_ctx->tokens, &free_token);
	ft_memdel((void **)&(asm_ctx->champ_code));
	ft_memdel((void **)&asm_ctx);
}
