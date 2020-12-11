/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:27:32 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		set_operation(t_asm *asm_ctx, char *str)
{
	int	i;

	i = -1;
	while (++i < 17)
	{
		if (ft_strequ(str, asm_ctx->op_tab[i].name))
		{
			((t_token *)
			(asm_ctx->last_token->content))->operation = asm_ctx->op_tab[i];
			return (1);
		}
	}
	return (0);
}

int		get_next_arg1(t_asm *asm_ctx, char *line, int *i, int i1)
{
	t_arg	arg;

	if (line[*i] == DIRECT_CHAR)
	{
		arg.type = T_DIR;
		(*i)++;
	}
	else if (line[*i] == 'r')
		arg.type = T_REG;
	else
		arg.type = T_IND;
	while (line[i1] && line[i1] != COMMENT_CHAR && line[i1] != SEPARATOR_CHAR)
		++(i1);
	clean_trim(&(arg.value), ft_strsub(line, *i, i1 - *i));
	ft_lstadd_end(&((t_token *)
	(asm_ctx->last_token->content))->args, ft_lstnew(&arg, sizeof(t_arg)));
	if (line[i1] == SEPARATOR_CHAR)
		i1++;
	else
	{
		*i = i1;
		return (0);
	}
	*i = i1;
	return (1);
}

int		get_next_arg(t_asm *asm_ctx, char *line, int *i)
{
	int		i1;
	t_arg	arg;

	if (!line[*i] || line[*i] == COMMENT_CHAR)
	{
		arg.type = T_DIR;
		arg.value = ft_strdup("");
		ft_lstadd_end(&((t_token *)
		(asm_ctx->last_token->content))->args, ft_lstnew(&arg, sizeof(t_arg)));
		return (0);
	}
	skip_whitespaces(line, i);
	i1 = *i;
	return (get_next_arg1(asm_ctx, line, i, i1));
}

int		is_register_valid(char *val)
{
	int i;
	int reg_num;

	i = 0;
	if (!val[1])
		return (0);
	while (val[++i])
	{
		if (!(val[i] <= '9' && val[i] >= '0'))
			return (0);
	}
	reg_num = ft_atoi(&val[1]);
	if (reg_num > REG_NUMBER)
		return (0);
	return (1);
}

int		is_direct_valid(char *val)
{
	int	i;

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
