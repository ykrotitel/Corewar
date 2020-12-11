/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:27:27 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		is_indirect_valid(char *val)
{
	int i;

	if (val[0] == LABEL_CHAR)
	{
		i = 0;
		while (val[++i])
			if (!ft_strchr(LABEL_CHARS, val[i]))
				return (0);
	}
	else
	{
		i = -1;
		if (val[0] == '-' || val[0] == '+')
			++i;
		while (val[++i])
			if (!(val[i] <= '9' && val[i] >= '0'))
				return (0);
	}
	return (1);
}

int		is_arg_valid(t_arg *arg, int type)
{
	if (!(arg->type & type))
		return (0);
	if (arg->type == T_REG)
		return (is_register_valid(arg->value));
	else if (arg->type == T_DIR)
		return (is_direct_valid(arg->value));
	else if (arg->type == T_IND)
		return (is_indirect_valid(arg->value));
	return (0);
}

void	is_arg_list_valid(t_asm *asm_ctx,
t_list *args, t_op operation, int line)
{
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = args;
	while (tmp)
	{
		++i;
		if (i > operation.arg_count - 1)
			throw_line_error(asm_ctx, "too much args", 0, line);
		if (!is_arg_valid((t_arg *)tmp->content, operation.arg_types[i]))
			throw_line_error(asm_ctx, "args not valid", 0, line);
		tmp = tmp->next;
	}
	if (i != operation.arg_count - 1)
		throw_line_error(asm_ctx, "not enough args", 0, line);
}

void	is_token_valid(t_asm *asm_ctx, t_token *token)
{
	int i;

	i = -1;
	while ((asm_ctx->op_tab[++i]).name)
		if (ft_strequ((token->operation).name, (asm_ctx->op_tab[i]).name))
			break ;
	if (!(asm_ctx->op_tab[i].name))
		throw_line_error(asm_ctx, "wrong operation", 0, token->line_num);
	is_arg_list_valid(asm_ctx,
	token->args, asm_ctx->op_tab[i], token->line_num);
}
