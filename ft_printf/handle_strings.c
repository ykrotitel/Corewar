/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 17:20:53 by lmittie           #+#    #+#             */
/*   Updated: 2019/12/26 15:26:46 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		sb(t_printf *data, char *str)
{
	handle_overflow_buffer(data, ft_strlen(str));
	if (ft_strlen(str) > 4096)
	{
		if (!data->precision || (t_ll)ft_strlen(str) < (t_ll)data->precision)
			write(data->fd, str, ft_strlen(str)) == -1 ?
			0 : (data->printed += ft_strlen(str));
		else
			write(data->fd, str, data->precision) == -1 ?
			0 : (data->printed += data->precision);
		return (0);
	}
	return (1);
}

static void		string_spaces(t_printf *data, char *str)
{
	t_ll	what_bigger;
	int		pr_or_wid;

	what_bigger = ((t_ll)data->precision < (t_ll)ft_strlen(str)
	&& data->precision != 0 && data->precision != -1)
	? data->precision : (t_ll)ft_strlen(str);
	if (data->precision > (t_ll)ft_strlen(str))
		data->precision = 0;
	pr_or_wid = (data->precision > data->width) ? data->precision : 0;
	while ((data->width-- - ((*str == '\0' && (data->precision != 0
	|| data->precision != -1)) ? 0 : what_bigger + pr_or_wid)) > 0
	&& handle_overflow_buffer(data, 1))
		data->buff[data->length++] = 32 + ((data->flag & ZERO) ? 16 : 0);
}

void			handle_strings(t_printf *data)
{
	char	*str;

	if (data->type & UNDEF)
		str = data->undef;
	else if ((str = (char *)va_arg(data->ap, char*)) == NULL)
		str = "(null)";
	if (data->precision == -1)
		str = "";
	if (data->flag & MINUS && *str && data->precision != -1 && sb(data, str))
	{
		if (!data->precision || (t_ll)ft_strlen(str) < (t_ll)data->precision)
			ft_strcpy(&data->buff[data->length], str);
		else
			str = ft_strncpy(&data->buff[data->length], str, data->precision);
		data->length += ft_strlen(str);
	}
	string_spaces(data, str);
	if (!(data->flag & MINUS) && *str && data->precision != -1 && sb(data, str))
	{
		if (!data->precision || (t_ll)ft_strlen(str) < (t_ll)data->precision)
			ft_strcpy(&data->buff[data->length], str);
		else
			str = ft_strncpy(&data->buff[data->length], str, data->precision);
		data->length += ft_strlen(str);
	}
}
