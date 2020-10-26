/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_visual.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:13:25 by acarlett          #+#    #+#             */
/*   Updated: 2020/10/26 21:53:51 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VISUAL_H
# define COREWAR_VISUAL_H

# include <ncurses.h>
# include <time.h>
# include "corewar.h"

# define WIDTH 200
# define HEIGHT 100

# define LINES 30
# define COLUMNS 200

void		test(t_data *data);
void		visual(t_data *data);

# endif