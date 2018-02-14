/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:20:08 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/10 14:50:09 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | color.c                                                  |
**   |     ft_get_color_player(4 lines)                         |
**   |     ft_init_color(25 lines)                              |
**   |     ft_get_color(15 lines)                               |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include "../commun/includes/op.h"
#include "../corewar/includes/corewar.h"

static int	ft_get_color_player(int player)
{
	static int	colors[NB_COLORS] = {COLOR_GREEN, COLOR_YELLOW, COLOR_MAGENTA,
		COLOR_BLUE, COLOR_RED, COLOR_CYAN};

	return (colors[(player - 1) % NB_COLORS]);
}

t_color		ft_init_color()
{
	t_color	c;
	int		i;
	int		start_i;

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	c.border = COLOR_PAIR(1) | A_BOLD;
	init_pair(2, COLOR_BLACK, COLOR_BLACK);
	c.black = COLOR_PAIR(2);
	init_pair(3, COLOR_BLACK, COLOR_BLACK);
	c.defaut = COLOR_PAIR(3) | A_BOLD;
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	c.text = COLOR_PAIR(4) | A_BOLD;

	c.player[0] = c.defaut;
	start_i = 10;
	i = 0;
	while (++i < MAX_PLAYERS)
	{
		init_pair(start_i + i, ft_get_color_player(i), COLOR_BLACK);
		c.player[i] = COLOR_PAIR(start_i + i);
		init_pair(start_i + i + MAX_PLAYERS, COLOR_WHITE,
				ft_get_color_player(i));
		c.player_live[i] = COLOR_PAIR(start_i + i + MAX_PLAYERS) | A_BOLD;
	}
	return (c);
}

int			ft_get_color(t_a *a, int k)
{
	int		color;

	color = a->nc.color.player[a->mem_info[k].player % MAX_PLAYERS];
	if (a->mem_info[k].process == 1)
	{
		color = a->nc.color.player[a->mem_info[k].player_process % MAX_PLAYERS] | A_REVERSE;
		if (a->mem[k] == 0x01)
			color = a->nc.color.player_live[
				a->mem_info[k].player_process % MAX_PLAYERS];
	}
	if ((a->cycle > TIME_BOLD_MEM && a->cycle - TIME_BOLD_MEM <=
				a->mem_info[k].cycle) || (a->cycle <= TIME_BOLD_MEM &&
					a->mem_info[k].cycle > 0))
		color |= A_BOLD;
	return (color);
}
