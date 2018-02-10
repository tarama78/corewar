/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:18:53 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/10 16:33:57 by tnicolas         ###   ########.fr       */
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

#include <corewar.h>

static void	ft_print_border(t_a *a)
{
	int		i;

	wattron(a->nc.win_mem, a->nc.color.border);
	wborder(a->nc.win_mem, '|', '|', '-', '-', '+', '+', '+', '+');
	wattroff(a->nc.win_mem, a->nc.color.border);
	wattron(a->nc.win_info, a->nc.color.border);
	wborder(a->nc.win_info, '|', '|', '-', '-', '+', '+', '+', '+');
	wattroff(a->nc.win_info, a->nc.color.border);
	i = -1;
	while (++i < a->num_of_player)
	{
		wattron(a->nc.win_player[i], a->nc.color.border);
		wborder(a->nc.win_player[i], '|', '|', '-', '-', '+', '+', '+', '+');
		wattroff(a->nc.win_player[i], a->nc.color.border);
	}
}

static void	ft_print_memory(t_a *a)
{
	int		i;
	int		j;
	int		k;
	int		color;

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

static void	ft_print_info(t_a *a)
{
	wattron(a->nc.win_info, a->nc.color.text);
	mvwprintw(a->nc.win_info, 1, WIN_W / 2 - 4, "COREWAR");
	mvwprintw(a->nc.win_info, 2, 2, "Cycle: %d", a->cycle);
	wattroff(a->nc.win_info, a->nc.color.text);
}

static void	ft_print_player(t_a *a, int n)
{
	wattron(a->nc.win_player[n], a->nc.color.text);
	mvwprintw(a->nc.win_player[n], 1, 2, "Player %d: ", a->player[n].player_number_print);
	wattroff(a->nc.win_player[n], a->nc.color.text);
	wattron(a->nc.win_player[n], a->nc.color.player[n + 1] | A_BOLD);
	wprintw(a->nc.win_player[n], "%.*s", WIN_W - 13, a->player[n].name);
	wattroff(a->nc.win_player[n], a->nc.color.player[n + 1] | A_BOLD);
	wattron(a->nc.win_player[n], a->nc.color.text);
	mvwprintw(a->nc.win_player[n], 3, 4, "Process: %23d", a->player[n].nb_process);
	mvwprintw(a->nc.win_player[n], 4, 4, "Last live: %21d", -1);
	mvwprintw(a->nc.win_player[n], 5, 4, "Last live in cur period: %7d", -1);
	wattroff(a->nc.win_player[n], a->nc.color.text);
}

void		ft_print(t_a *a)
{
	int		i;

	ft_print_border(a);
	ft_print_memory(a);
	wrefresh(a->nc.win_mem);
	ft_print_info(a);
	wrefresh(a->nc.win_info);
	i = -1;
	while (++i < a->num_of_player)
	{
		ft_print_player(a, i);
		wrefresh(a->nc.win_player[i]);
	}
}
