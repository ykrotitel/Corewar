/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:54:18 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/11 20:05:46 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/assembler.h"

int		is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int		skip_whitespaces(char *str, int *i)
{
	int	i1;

	i1 = *i;
	while (is_space(str[i1]))
		i1++;
	*i = i1;
	return (0);
}

int		create_token(t_asm *asm_ctx, int position)
{
	t_token	token;
	t_list	*list_item;

	token.position = position;
	token.is_full = 0;
	token.operation = (t_op){0, 0, {0}, 0, 0, 0, 0, 0};
	token.labels = 0;
	token.args = 0;
	token.line_num = asm_ctx->line_count;
	if (!(list_item = ft_lstnew(&token, sizeof(token))))
		return (0);
	asm_ctx->last_token = list_item;
	ft_lstadd_end(&(asm_ctx->tokens), list_item);
	return (1);
}

void	ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (!alst)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int		clean_trim(char **str_res, char *to_trim)
{
	char	*tmp;

	tmp = to_trim;
	if (!to_trim || !(*str_res = ft_strtrim(to_trim)))
		return (0);
	ft_strdel(&tmp);
	return (1);
}
