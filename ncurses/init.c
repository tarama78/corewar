/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:35:13 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/10 15:17:45 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | init.c                                                   |
**   |     ft_init(9 lines)                                     |
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

void		ft_init(t_a *a)
{
	int		i;

	a->nc.win_mem = NULL;
	a->nc.win_info = NULL;
	initscr();
	start_color();
	noecho();
	curs_set(0);
	a->nc.color = ft_init_color();
	a->nc.sqrt_mem_size = sqrt(MEM_SIZE);
	a->nc.win_mem = subwin(stdscr, a->nc.sqrt_mem_size + 3, a->nc.sqrt_mem_size * 3 + 5, 0, 0);
	a->nc.win_info = subwin(stdscr, WIN_H, WIN_W, a->nc.sqrt_mem_size + 2, 0);
	i = -1;
	while (++i < a->num_of_player)
	{
		a->nc.win_player[i] = subwin(stdscr, WIN_H, WIN_W, a->nc.sqrt_mem_size + 2, WIN_W * (i + 1) - i - 1);
	}
}
