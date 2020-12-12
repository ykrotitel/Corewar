/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2020/12/11 16:22:17 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op	g_op_tab[17] = {{"live", 1, {T_DIR}, 1, 10, 0, 4, &live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 4, &ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 4, &st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 4, &add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 4, &sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 1, 4, &and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 1, 4, &or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 1, 4, &xor},
	{"zjmp", 1, {T_DIR}, 9, 20, 0, 2, &zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		10, 25, 1, 2, &ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		11, 25, 1, 2, &sti},
	{"fork", 1, {T_DIR}, 12, 800, 0, 2, &fork_},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 4, &lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		14, 50, 1, 2, &lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, 0, 2, &lfork},
	{"aff", 1, {T_REG}, 16, 2, 1, 4, &aff},
	{0, 0, {0}, 0, 0, 0, 0, 0}};
