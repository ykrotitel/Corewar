/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parse1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:27:14 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int	concat_cmd(t_asm *asm_ctx, char *line, int start, int len)
{
	char	*tmp;
	char	*tmp1;
	char	*result;

	if (!(tmp = ft_strsub(line, start, len)))
		return (0);
	tmp1 = asm_ctx->cmd_mode ? asm_ctx->comment : asm_ctx->name;
	if (!(result = ft_strjoin(tmp1, tmp)))
	{
		ft_strdel(&tmp);
		return (0);
	}
	if (asm_ctx->cmd_mode == 1)
		asm_ctx->comment = result;
	else if (asm_ctx->cmd_mode == 0)
		asm_ctx->name = result;
	ft_strdel(&tmp1);
	ft_strdel(&tmp);
	return (1);
}
