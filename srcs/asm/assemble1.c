/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:29:27 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:26:48 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		get_dir_size(t_op operation)
{
	if (ft_strequ(operation.name, "lfork") ||
		ft_strequ(operation.name, "lldi") ||
		ft_strequ(operation.name, "fork") ||
		ft_strequ(operation.name, "sti") ||
		ft_strequ(operation.name, "ldi") ||
		ft_strequ(operation.name, "zjmp"))
		return (2);
	else
		return (4);
}

int		get_token_size(t_token *token)
{
	int		size;
	t_list	*temp;

	if (!(token->operation.name))
		return (0);
	size = 1;
	if (token->operation.is_arg_type_code)
		size++;
	if (!token->args)
		return (size);
	temp = token->args;
	while (temp)
	{
		if (((t_arg *)temp->content)->type == T_IND)
			size += IND_SIZE;
		else if (((t_arg *)temp->content)->type == T_DIR)
			size += get_dir_size(token->operation);
		else if (((t_arg *)temp->content)->type == T_REG)
			size += 1;
		temp = temp->next;
	}
	return (size);
}

int		get_distance(t_list *node1, t_list *node2)
{
	t_list	*start;
	t_list	*end;
	int		result;
	int		sign;

	result = 0;
	if (((t_token *)(node1->content))->position
		> ((t_token *)(node2->content))->position && (sign = -1) < 0)
	{
		start = node2;
		end = node1;
	}
	else
	{
		start = node1;
		end = node2;
		sign = 1;
	}
	while (start && ((t_token *)(start->content))->position
					!= ((t_token *)(end->content))->position)
	{
		result += get_token_size(((t_token *)(start->content)));
		start = start->next;
	}
	return (result * sign);
}

void	convert_label(t_asm *asm_ctx, t_arg *arg, t_list *token)
{
	t_list	*start_token;
	t_list	*s_lab;
	t_list	*end_token;
	char	*dist;

	start_token = asm_ctx->tokens;
	end_token = 0;
	while (start_token)
	{
		s_lab = ((t_token *)(start_token->content))->labels;
		while (s_lab)
		{
			if (ft_strequ(((t_label *)(s_lab->content))->name, arg->value + 1))
				end_token = start_token;
			s_lab = s_lab->next;
		}
		start_token = start_token->next;
	}
	if (!end_token)
		throw_line_error(asm_ctx, "wrong label",
	arg->value + 1, ((t_token *)(token->content))->line_num);
	if (!(dist = ft_itoa(get_distance(token, end_token))))
		throw_error(asm_ctx, "malloc error", 0);
	ft_strdel(&arg->value);
	arg->value = dist;
}

int		resolve_labels(t_asm *asm_ctx)
{
	t_list	*start_token;
	t_list	*start_arg;

	start_token = asm_ctx->tokens;
	while (start_token)
	{
		start_arg = ((t_token *)(start_token->content))->args;
		while (start_arg)
		{
			if (((t_arg *)(start_arg->content))->value
				&& ((t_arg *)(start_arg->content))->value[0] == LABEL_CHAR)
				convert_label(asm_ctx,
				(t_arg *)(start_arg->content), start_token);
			start_arg = start_arg->next;
		}
		start_token = start_token->next;
	}
	return (1);
}
