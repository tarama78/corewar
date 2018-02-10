/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:18:53 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/10 14:14:24 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | print.c                                                  |
**   |     ft_print_memory(28 lines)                            |
**   |         MEUUUU too many lines                            |
**   |     ft_print(3 lines)                                    |
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

static void	ft_print_memory(t_a *a)
{
	int		i;
	int		j;
	int		k;
	int		color;

	wattron(a->nc.win_mem, a->nc.color.border);
	wborder(a->nc.win_mem, '|', '|', '-', '-', '+', '+', '+', '+');
	wattroff(a->nc.win_mem, a->nc.color.border);
	i = 1;
	k = 0;
	while (++i < a->nc.sqrt_mem_size + 1)
	{
		j = 0;
		while ((j += 3) < a->nc.sqrt_mem_size * 3 + 1)
		{
			color = ft_get_color(a, k);
			wattron(a->nc.win_mem, color);
			mvwprintw(a->nc.win_mem, i, j, "%02hhx", a->mem[k]);
			wattroff(a->nc.win_mem, color);
			if (j + 2 <= a->nc.sqrt_mem_size)
			{
				wattron(a->nc.win_mem, a->nc.color.black);
				mvwprintw(a->nc.win_mem, i, j + 2, " ");
				wattroff(a->nc.win_mem, a->nc.color.black);
			}
			k++;
		}
	}
}

void		ft_print(t_a *a)
{
	clear();
	ft_print_memory(a);
	wrefresh(a->nc.win_mem);
}
