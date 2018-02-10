/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:22:00 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/10 18:58:52 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		kill_prc(t_a *a)
{
	t_process	*prc;
	t_process	*tmp;

	if (!a->process)
		return ;
	while (a->process->live == 0)
	{
		prc = a->process;
		a->process = a->process->next;
		free(prc);
		if (!a->process)
			return ;
	}
	prc = a->process;
	while (prc && prc->next)
	{
		if (prc->next->live == 0)
		{
			tmp = prc->next->next;
			free(prc->next);
			prc->next = tmp;
		}	
	}
}

static int		new_cycle(t_a *a)
{
	int		i;

	kill_prc(a);
	a->live = 0;
	i = -1;
	while (++i < a->num_of_player)
	{
		a->live += a->player[i].nb_live_current;
		a->player[i].nb_live_current = 0;
	}
	if (a->live >= NBR_LIVE || (a->cycle - a->last_dec_cycle >= MAX_CHECKS))
	{
		a->cycle_to_die -= CYCLE_DELTA;
		a->last_dec_cycle = a->cycle;
	}
	return (a->cycle_to_die);
}

void	game_loop(t_a *a, void (**f)(t_process *, t_a *))
{
	int			live;
	uint64_t	nxt_cycle_die;

	live = 1;
	nxt_cycle_die = a->cycle_to_die;
	ft_print(a);
	ft_printf("%d\n", a->cycle_to_die);
	while (a->process && getch() != 27)
	{
		a->cycle++;
		if (a->cycle >= nxt_cycle_die)
			nxt_cycle_die += new_cycle(a);
		game_turn(a, f);
		ft_print(a);
	}
}

void	game_turn(t_a *a, void (**f)(t_process *, t_a *))
{
	t_process	*prc;

	prc = a->process;
	while (prc)
	{
		if (!check_type(prc, a))
			ft_move(prc, a);
		else if (a->mem[prc->pc] <= NB_COMM)
			f[a->mem[prc->pc]](prc, a);
		prc = prc->next;
	}
}
