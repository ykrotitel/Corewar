/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:00:04 by fmallist          #+#    #+#             */
/*   Updated: 2019/12/26 15:38:57 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>

# define MINUS				(1 << 0)
# define PLUS				(1 << 1)
# define ZERO				(1 << 2)
# define SPACE				(1 << 3)
# define SHARP				(1 << 4)

# define H					(1 << 1)
# define HH					(1 << 2)
# define L					(1 << 3)
# define LL					(1 << 4)
# define D					(1 << 5)
# define BIGL				(1 << 6)

# define CHAR				(1 << 9)
# define STRING				(1 << 2)
# define POINTER			(1 << 5)
# define PERCENT			(1 << 6)
# define DECIMAL			10
# define OCTAL				8
# define UNSIGNED			(1 << 7)
# define HEX				16
# define BIG_HEX			17
# define FL					(1 << 8)
# define UNDEF				(1 << 10)

# define ANSI_RED			"\x1b[31m"
# define ANSI_GREEN			"\x1b[32m"
# define ANSI_YELLOW		"\x1b[33m"
# define ANSI_BLUE			"\x1b[34m"
# define ANSI_CYAN			"\x1b[36m"
# define ANSI_RESET			"\x1b[0m"

# define MAX_LENGTH			4096

# define BASE				1000000000

# define VAR(x, y)			x y

typedef long long			t_ll;

typedef struct	s_num
{
	unsigned int	arr[100];
	unsigned		size_num;
}				t_num;

typedef unsigned long long	t_ull;

typedef struct	s_arr
{
	char		buff[5000];
	size_t		length;
}				t_arr;

typedef struct	s_float
{
	t_num			decimal;
	t_num			fractional;
	double			num;
	unsigned int	mantissa;
	int				exp;
	char			sign;
}				t_float;

typedef struct	s_ldbl
{
	t_num			decimal;
	t_num			fractional;
	long double		num;
	unsigned int	mantissa;
	int				exp;
	char			sign;
}				t_ldbl;

typedef struct	s_printf
{
	uint8_t		flag;
	t_ll		width;
	int			precision;
	uint16_t	size;
	uint64_t	type;
	size_t		length;
	char		buff[MAX_LENGTH + 1];
	va_list		ap;
	unsigned	printed;
	char		undef[2];
	int			fd;
}				t_printf;

void			get_width(t_printf *data, const char **format);
void			get_precision(t_printf *data, const char **format);
void			get_flags(t_printf *data, const char **format);
int				get_size(t_printf *data, const char **format);

int				ft_printf(const char *format, ...);
void			push_buffer(t_printf *data);
int				fill_options(t_printf *data, const char **format);
int				handle_overflow_buffer(t_printf *data, size_t len);
void			get_integer(t_printf *data, long long *n);
void			handle_integers(t_printf *data);

void			utoa_base_buff_ox(t_ull value, unsigned base, t_printf *data);
void			itoa_base_buff(t_ll value, unsigned base, t_printf *data);
char			neg_value(t_ll value, unsigned base, t_printf *data);
char			pos_value(t_ll value, unsigned base, t_printf *data);
char			result(t_ll value, unsigned base, t_printf *data);
t_ll			new_value(t_ll value, unsigned *base, t_ll *val);
size_t			ft_unumlen(t_ull val, unsigned base);

void			itoa_base_buff_u(t_ull value, t_printf *data);
void			get_unsigned(t_printf *data, t_ull *n);
size_t			ft_numlen_u(t_ull val);
void			handle_unsigned(t_printf *data);
void			handle_floats(t_printf *data);
void			handle_octals(t_printf *data);
void			handle_hexdecimals(t_printf *data);
void			handle_bighex(t_printf *data);
void			handle_chars(t_printf *data);
void			handle_strings(t_printf *data);
void			handle_pointers(t_printf *data);
void			handle_uoctal(t_printf *data);
void			handle_ubighex(t_printf *data);
void			handle_uhex(t_printf *data);

void			add_long_short(t_num *a, unsigned b);
void			multiply_long_short(t_num *a, unsigned b);
void			add_long_long(t_num *a, t_num b);
t_num			big_power_of_five(unsigned power);

void			ftoa_base_buff(unsigned int value, t_arr *arr);
void			print_float(t_arr *dec, t_arr *frac, t_printf *data, int i);
void			before_print_float(t_float number, t_printf *data);
int				count_zeros(t_float *n);
int				count_zeros_ldbl(t_ldbl *n);
int				handle_f_prec(t_arr *arr, t_arr *dec, t_printf *data);
int				handle_f_dec(t_arr *arr, char num, char flag);
void			before_print_ldbl(t_ldbl number, t_printf *data);

int				reset_color(t_printf *data, const char **f);
int				read_color(t_printf *data, const char **f);

#endif
