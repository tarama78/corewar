/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_turn_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 15:28:13 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/19 15:39:29 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		ft_command(t_a *a)
{
	int		command;

	command = getch();
	if (command == ' ')
		a->nc.pause = !(a->nc.pause);
	else if (command == '-')
		a->speed += (a->speed + CHANGE_SPEED <= 200000) ? CHANGE_SPEED : 0;
	else if (command == '=')
		a->speed = SPEED;
	else if (command == '+')
		a->speed -= (a->speed - CHANGE_SPEED >= 0) ? CHANGE_SPEED : 0;
	return (command);
}

void			free_process(t_a *a)
{
	t_process *tmp;

	tmp = a->process;
	while (tmp)
	{
		a->process = a->process->next;
		free(tmp);
		tmp = a->process;
	}
}

static void		game_loop_2(t_a *a, void (**f)(t_process *, t_a *),
		int time_start)
{
	game_turn(a, f);
	if (a->dump_cycle != -1)
		ft_check_dump(a);
	a->cycle++;
	if (a->visu && clock() - time_start < (unsigned long)a->speed)
		usleep((a->speed - (clock() - time_start)));
}

void			game_loop(t_a *a, void (**f)(t_process *, t_a *))
{
	uint64_t	nxt_cycle_die;
	int			command;
	int			time_start;
	int			end;

	end = 0;
	command = 0;
	nxt_cycle_die = a->cycle_to_die;
	ft_print(a);
	while (command != 27 && ((a->visu && end) || !end))
	{
		if ((a->nc.pause || !a->visu) && a->process)
		{
			time_start = clock();
			if (a->cycle >= nxt_cycle_die)
				nxt_cycle_die += new_cycle(a);
			if (!a->process)
				break ;
			game_loop_2(a, f, time_start);
		}
		(a->visu) && ((command = ft_command(a)) != 27) && ft_print(a);
	}
	if (a->visu && a->process == NULL && ft_print(a))
		while (getch() != 27)
			;
	free_process(a);
}

void			game_turn(t_a *a, void (**f)(t_process *, t_a *))
{
	t_process	*prc;

	prc = a->process;
	while (prc)
	{
		if (--prc->cycle_wait <= 0)
		{
			if (prc->cmd == -1)
				prc->cmd = (a->mem[prc->pc]) & 0x000000FF;
			if (prc->cmd <= 0 || prc->cmd > NB_COMM)
				ft_move(prc, a);
			else if (prc->cycle_wait == 0 && !check_type(prc, a))
				mod_carry(prc, a);
			else
				f[prc->cmd](prc, a);
			if (prc->cycle_wait <= 0)
				prc->cmd = -1;
		}
		if (a->mem_info[prc->pc].process == 0)
			ft_curseur(prc, prc->pc, prc->pc, a);
		prc = prc->next;
	}
}
