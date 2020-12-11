/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:27:22 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	parse_args(t_asm *asm_ctx, char *line, int *i)
{
	int		i1;

	if (!line[*i] || line[*i] == COMMENT_CHAR)
		return ;
	i1 = *i;
	while (line[i1]
	&& line[i1] != COMMENT_CHAR && (line[i1] != ' ' || line[i1] != '\n'))
		++i1;
	while (get_next_arg(asm_ctx, line, i))
	{
	}
	skip_whitespaces(line, i);
	((t_token *)(asm_ctx->last_token->content))->line_num = asm_ctx->line_count;
	if (line[*i] && line[*i] != COMMENT_CHAR)
		throw_line_error(asm_ctx, "wrong character",
		0, ((t_token *)(asm_ctx->last_token->content))->line_num);
	is_token_valid(asm_ctx, asm_ctx->last_token->content);
	((t_token *)(asm_ctx->last_token->content))->is_full = 1;
}

void	parse_operation(t_asm *asm_ctx, char *line, int *i)
{
	int		i1;
	char	*op;

	if (!line[*i] || line[*i] == COMMENT_CHAR)
		return ;
	i1 = *i;
	((t_token *)(asm_ctx->last_token->content))->line_num = asm_ctx->line_count;
	while (line[i1] && line[i1] != COMMENT_CHAR
	&& !is_space(line[i1]) && line[i1] != DIRECT_CHAR)
		++i1;
	op = ft_strsub(line, *i, i1 - *i);
	if (!set_operation(asm_ctx, op))
	{
		throw_line_error(asm_ctx, "wrong operation",
		op, ((t_token *)(asm_ctx->last_token->content))->line_num);
		ft_strdel(&op);
	}
	*i = i1;
	ft_strdel(&op);
}

void	parse_label(t_asm *asm_ctx, char *line, int *i)
{
	t_label	label;
	int		i1;

	if (!line[*i] || line[*i] == COMMENT_CHAR)
		return ;
	i1 = *i;
	((t_token *)(asm_ctx->last_token->content))->line_num = asm_ctx->line_count;
	while (line[i1]
	&& line[i1] != COMMENT_CHAR && ft_strchr(LABEL_CHARS, line[i1]))
		++(i1);
	if (line[i1] == LABEL_CHAR)
	{
		label.name = ft_strsub(line, *i, i1 - *i);
		ft_lstadd(&((t_token *)(asm_ctx->last_token->content))->labels,
		ft_lstnew(&label, sizeof(label)));
		i1++;
		*i = i1;
	}
}

int		parse(t_asm *asm_ctx, int cur_position)
{
	char	*line;
	int		i;

	while ((i = 0) == 0 && get_next_line(asm_ctx->opened_fd, &line) > 0)
	{
		skip_whitespaces(line, &i);
		if (line[i] && line[i] != COMMENT_CHAR && (!(asm_ctx->last_token)
		|| ((t_token *)(asm_ctx->last_token->content))->is_full))
		{
			if (!create_token(asm_ctx, cur_position))
				throw_error(asm_ctx, "malloc error", 0);
			((t_token *)(asm_ctx->last_token->content))->is_full = 0;
			cur_position++;
		}
		parse_label(asm_ctx, line, &i);
		skip_whitespaces(line, &i);
		parse_operation(asm_ctx, line, &i);
		skip_whitespaces(line, &i);
		parse_args(asm_ctx, line, &i);
		ft_strdel(&line);
		asm_ctx->line_count++;
	}
	return (1);
}
