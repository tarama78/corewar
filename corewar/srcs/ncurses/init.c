/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:35:13 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/15 17:59:45 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | init.c                                                   |
**   |     ft_init_windows_1(23 lines)                          |
**   |     ft_init_windows_2(19 lines)                          |
**   |     ft_init(15 lines)                                    |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <corewar.h>

static void	ft_init_windows_1(t_a *a)
{
	int		i;
	int		moins_i;

	a->nc.win_info = subwin(stdscr, WIN_H, WIN_W, 0,
			a->nc.sqrt_mem_size * 3 + 4);
	i = -1;
	while (++i < a->num_of_player)
	{
		if (WIN_H * (i + 1) - i - 1 + WIN_H <= a->nc.sqrt_mem_size + 3)
			a->nc.win_player[i] = subwin(stdscr, WIN_H, WIN_W, WIN_H * (i + 1)
					- i - 1, a->nc.sqrt_mem_size * 3 + 4);
		else
			break ;
	}
	moins_i = --i;
	if (a->nc.sqrt_mem_size * 3 + 5 + WIN_W * 2 < COLS)
		while (++i < a->num_of_player)
			a->nc.win_player[i] = subwin(stdscr, WIN_H, WIN_W, (WIN_H - 1) *
					(i - moins_i - 1), a->nc.sqrt_mem_size * 3 + 3 + WIN_W);
	else
		while (++i < a->num_of_player)
			a->nc.win_player[i] = subwin(stdscr, WIN_H, WIN_W,
					a->nc.sqrt_mem_size + 2, (WIN_W - 1) * (i - moins_i - 1));
}

static void	ft_init_windows_2(t_a *a)
{
	int		i;
	int		moins_i;

	a->nc.win_info = subwin(stdscr, WIN_H, WIN_W, a->nc.sqrt_mem_size + 2, 0);
	i = -1;
	while (++i < a->num_of_player)
	{
		if (WIN_W * (i + 1) - i - 1 + WIN_W <= a->nc.sqrt_mem_size * 3 + 5)
			a->nc.win_player[i] = subwin(stdscr, WIN_H, WIN_W,
					a->nc.sqrt_mem_size + 2, WIN_W * (i + 1) - i - 1);
		else
			break ;
	}
	moins_i = --i;
	while (++i < a->num_of_player)
	{
		a->nc.win_player[i] = subwin(stdscr, WIN_H, WIN_W, a->nc.sqrt_mem_size
				+ 2 + WIN_H - 1, (WIN_W - 1) * (i - moins_i - 1));
	}
}

static int			ft_testmalloc(t_a *a)
{
	int i;
	int check;

	check = SUCCESS;

	if (a->nc.win_mem == NULL || a->nc.win_info == NULL)
		check = ERROR;
	i= -1;
	while (++i < a->num_of_player)
		if (a->nc.win_player[i] == NULL)
			check = ERROR;
	if (check == SUCCESS)
		return (SUCCESS);
	delwin(a->nc.win_mem);
	delwin(a->nc.win_info);
	i= -1;
	while (++i < a->num_of_player)
		delwin(a->nc.win_player[i]);
	return (ERROR);
}

void		ft_init(t_a *a)
{
	delwin(NULL);
	a->nc.win_mem = NULL;
	a->nc.win_info = NULL;
	initscr();
	start_color();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);
	a->nc.color = ft_init_color();
	a->nc.sqrt_mem_size = sqrt(MEM_SIZE);
	a->nc.win_mem = subwin(stdscr, a->nc.sqrt_mem_size + 3,
			a->nc.sqrt_mem_size * 3 + 5, 0, 0);
	if (a->nc.sqrt_mem_size * 3 + 5 + WIN_W < COLS)
		ft_init_windows_1(a);
	else
		ft_init_windows_2(a);
	ft_testmalloc(a);
}
