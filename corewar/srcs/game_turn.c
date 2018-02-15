/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:22:00 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/15 16:44:22 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		kill_prc_2(t_a *a, t_process **prc)
{
	t_process	*tmp;

	if ((*prc)->next->live == 0)
	{
		tmp = (*prc)->next->next;
		a->mem_info[(*prc)->next->pc].process = 0;
		a->player[(*prc)->next->player_index].nb_process--;
		free((*prc)->next);
		(*prc)->next = tmp;
	}
	(*prc) = (*prc)->next;
	if (*prc)
		(*prc)->live = 0;
}

void			kill_prc(t_a *a)
{
	t_process	*prc;

	if (!a->process)
		return ;
	while (a->process->live == 0)
	{
		prc = a->process;
		a->process = a->process->next;
		a->mem_info[prc->pc].process = 0;
		a->player[prc->player_index].nb_process--;
		free(prc);
		if (!a->process)
			return ;
	}
	prc = a->process;
	prc->live = 0;
	while (prc && prc->next)
		kill_prc_2(a, &prc);
}

int				new_cycle(t_a *a)
{
	int		i;

	kill_prc(a);
	a->live = 0;
	i = -1;
	while (++i < a->num_of_player)
	{
		if (a->player[i].nb_live_current != 0)
			a->winner = a->player + i;
	}
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

static void		ft_print_dump(t_a *a)
{
	int k;
	int i;
	int cmpt;

	k = 0;
	cmpt = 0;
	i = 0;
	while (k < MEM_SIZE)
	{
		ft_printf("%#05x : ", 32 * i);
		while (cmpt < 32 && k < MEM_SIZE)
		{
			ft_printf("%02hhx ", a->mem[k++]);
			cmpt++;
		}
		i++;
		ft_putstr("\n");
		cmpt = 0;
	}
}

void			ft_check_dump(t_a *a)
{
	if (a->dump_cycle == 0)
	{
		ft_print_dump(a);
		exit(EXIT_SUCCESS);
	}
	else
		(a->dump_cycle)--;
}
