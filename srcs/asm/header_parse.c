/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:27:10 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		read_cmd(t_asm *asm_ctx, char *line)
{
	int		i;
	char	*sep;

	if (!line[0])
	{
		concat_cmd(asm_ctx, "\n", 0, 1);
		return (1);
	}
	i = 0;
	if ((sep = ft_strchr(line, '"')))
	{
		i = sep - line + 1;
		if (!concat_cmd(asm_ctx, line, 0, sep - line))
			return (-1);
		skip_whitespaces(line, &i);
		if (line[i] && line[i] != COMMENT_CHAR)
			return (-1);
		return (0);
	}
	if (!concat_cmd(asm_ctx, line, 0, ft_strlen(line))
	|| !concat_cmd(asm_ctx, "\n", 0, 1))
		return (-1);
	return (1);
}

void	set_cmd_mode(t_asm *asm_ctx, char *line)
{
	if (!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		asm_ctx->cmd_mode = 0;
		if (asm_ctx->was_name)
			throw_error(asm_ctx, "expected only one definition of name", 0);
		asm_ctx->was_name = 1;
	}
	else if (!ft_strncmp(line,
			COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
	{
		asm_ctx->cmd_mode = 1;
		if (asm_ctx->was_comment)
			throw_error(asm_ctx, "expected only one definition of comment", 0);
		asm_ctx->was_comment = 1;
	}
	else
		asm_ctx->cmd_mode = -1;
}

int		skip_header_void(t_asm *asm_ctx, char **line, int *i)
{
	int ret;

	while ((ret = get_next_line(asm_ctx->opened_fd, line)) > 0)
	{
		asm_ctx->line_count++;
		*i = 0;
		skip_whitespaces(*line, i);
		if ((*line)[*i] && (*line)[*i] != COMMENT_CHAR)
			return (1);
		else
			ft_strdel(line);
	}
	return (ret);
}

int		get_cmd(t_asm *asm_ctx)
{
	int		i;
	int		ret;
	char	*line;

	i = 0;
	if ((ret = skip_header_void(asm_ctx, &line, &i)) <= 0)
		return (ret != 0 ? ret : -1);
	set_cmd_mode(asm_ctx, &line[i]);
	if (asm_ctx->cmd_mode == -1)
		return (-1);
	i += ft_strlen(asm_ctx->cmd_mode ? COMMENT_CMD_STRING : NAME_CMD_STRING);
	skip_whitespaces(line, &i);
	if (line[i++] != '"')
		return (-1);
	ret = read_cmd(asm_ctx, &line[i]);
	ft_strdel(&line);
	if (ret <= 0)
		return (ret);
	while (++(asm_ctx->line_count) > 0
	&& get_next_line(asm_ctx->opened_fd, &line)
	&& (ret = read_cmd(asm_ctx, line)) == 1)
		ft_strdel(&line);
	ft_strdel(&line);
	return (ret);
}

int		set_header_command(t_asm *asm_ctx)
{
	int		ret;
	int		len;
	int		required_len;
	char	*res;

	ret = get_cmd(asm_ctx);
	if (ret != 0)
		return (0);
	required_len = asm_ctx->cmd_mode ? COMMENT_LENGTH : PROG_NAME_LENGTH;
	len = asm_ctx->cmd_mode
			? ft_strlen(asm_ctx->comment) : ft_strlen(asm_ctx->name);
	if (ret != 0 || len > required_len)
		return (0);
	res = (char *)ft_memalloc(required_len);
	ft_memmove(res, asm_ctx->cmd_mode ? asm_ctx->comment : asm_ctx->name, len);
	free(asm_ctx->cmd_mode ? asm_ctx->comment : asm_ctx->name);
	if (asm_ctx->cmd_mode)
		asm_ctx->comment = res;
	else
		asm_ctx->name = res;
	return (1);
}
