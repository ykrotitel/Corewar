/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:30:46 by pkathy            #+#    #+#             */
/*   Updated: 2020/12/12 17:02:20 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H

# define ASSEMBLER_H
# define MAXINT	2147483647
# define MODE	0

# include "../ft_printf/libft/libft.h"
# include "../ft_printf/libft/get_next_line.h"
# include "op.h"

typedef struct		s_arg
{
	int		type;
	char	*value;
}					t_arg;

typedef struct		s_label
{
	char	*name;
}					t_label;

typedef struct		s_op
{
	char	*name;
	int		arg_count;
	int		arg_types[3];
	char	id;
	int		cooldown;
	char	*desc;
	int		is_arg_type_code;
	int		some_sht;
}					t_op;

typedef struct		s_token
{
	t_list	*labels;
	t_op	operation;
	t_list	*args;
	int		position;
	int		line_num;
	int		is_full;
}					t_token;

typedef struct		s_asm
{
	t_op			op_tab[17];
	t_list			*tokens;
	t_list			*last_token;
	char			*name;
	char			*comment;
	unsigned char	*champ_code;
	int				opened_fd;
	int				cmd_mode;
	int				champ_code_size;
	int				was_comment;
	int				was_name;
	int				is_little_endian;
	int				line_count;
	char			*out_name;
}					t_asm;

int					skip_whitespaces(char *str, int *i);
int					is_space(char c);
void				ft_lstadd_end(t_list **alst, t_list *new);
int					create_token(t_asm *asm_ctx, int position);
int					parse(t_asm *asm_ctx, int cur_position);
int					open_file(t_asm *asm_ctx, char *fname);
int					set_operation(t_asm *asm_ctx, char *str);
void				init_op_tab(t_asm *asm_ctx);
int					get_next_arg(t_asm *asm_ctx, char *line, int *i);
void				is_token_valid(t_asm *asm_ctx, t_token *token);
int					get_cmd(t_asm *asm_ctx);
int					get_token_size(t_token *token);
int					clean_trim(char **str_res, char *to_trim);
int					resolve_labels(t_asm *asm_ctx);
void				print_token(t_token *token);
int					assemble(t_asm *asm_ctx);
int					set_header_command(t_asm *asm_ctx);
void				throw_error(t_asm *asm_ctx, const char *msg1,
					const char *msg2);
void				throw_line_error(t_asm *asm_ctx,
					const char *msg1, const char *msg2, int line_num);
int					get_dir_size(t_op operation);
int					get_token_size(t_token *token);
int					get_distance(t_list *node1, t_list *node2);
void				onvert_label(t_asm *asm_ctx, t_arg *arg, t_list *token);
int					resolve_labels(t_asm *asm_ctx);
int					set_champ_code_size(t_asm *asm_ctx);
int					get_big_endian_int(int n);
void				set_byte_code(t_asm *asm_ctx, int data, int size, int *i);
int					set_args_byte_code(t_asm *asm_ctx,
					t_list *arg_l, int dir_size, int *i);
int					set_token_byte_code(t_asm *asm_ctx, t_token *token, int *i);
int					set_champ_byte_code(t_asm *asm_ctx);
int					create_champ(t_asm *asm_ctx);
int					assemble(t_asm *asm_ctx);
void				free_label(void *label_v, size_t label_size);
void				free_arg(void *arg_v, size_t arg_size);
void				free_token(void *token_v, size_t token_size);
void				free_asm(t_asm *asm_ctx);
void				throw_line_error(t_asm *asm_ctx,
					const char *msg1, const char *msg2, int line_num);
void				throw_error(t_asm *asm_ctx, const char *msg1,
					const char *msg2);
t_asm				*init();
int					concat_cmd(t_asm *asm_ctx, char *line, int start, int len);
int					set_operation(t_asm *asm_ctx, char *str);
int					get_next_arg1(t_asm *asm_ctx, char *line, int *i, int i1);
int					get_next_arg(t_asm *asm_ctx, char *line, int *i);
int					is_register_valid(char *val);
int					is_direct_valid(char *val);
int					is_indirect_valid(char *val);
int					is_arg_valid(t_arg *arg, int type);
void				is_arg_list_valid(t_asm *asm_ctx,
					t_list *args, t_op operation, int line);
void				is_token_valid(t_asm *asm_ctx, t_token *token);

#endif
