/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_turn_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 15:28:13 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/18 02:45:50 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
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

	a->nc.pause = 0;
	command = 0;
	nxt_cycle_die = a->cycle_to_die;
	if (a->visu)
		ft_print(a);
	fd = open("debug", O_WRONLY);
	while (a->process && command != 27)
	{
		if (a->nc.pause || !a->visu)
		{
			time_start = clock();
			if (a->cycle >= nxt_cycle_die)
				nxt_cycle_die += new_cycle(a);
			if (!a->process)
				break ;
			game_loop_2(a, f, time_start);
		}
		if (a->visu && (command = ft_command(a)) != 27)
			ft_print(a);
	}
	close(fd);
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
			ft_dprintf(fd, "clyle %d, prc %d player %#x, r1 %#x, r2 %#x, r3, %#x, r4 %#x, r5 %#x, r6 %#x, r7 %#x, r8 %#x, r9 %#x, r10 %#x, r11 %#x, r12 %#x, r13 %#x, r14 %#x, r15 %#x, r16 %#x\n", a->cycle, prc->nb_prc, prc->num_player, prc->reg[1], prc->reg[2], prc->reg[3], prc->reg[4], prc->reg[5], prc->reg[6], prc->reg[7], prc->reg[8], prc->reg[9], prc->reg[10], prc->reg[11], prc->reg[12], prc->reg[13], prc->reg[14], prc->reg[15], prc->reg[16]);
			if (a->mem[prc->pc] <= 0 || a->mem[prc->pc] > 16)
				ft_move(prc, a);
			else if (prc->cycle_wait == 0 && !check_type(prc, a))
				mod_carry(prc, a);
			else if (a->mem[prc->pc] <= NB_COMM)
				f[a->mem[prc->pc]](prc, a);
		}
		if (a->mem_info[prc->pc].process == 0)
			ft_curseur(prc, prc->pc, prc->pc, a);
		prc = prc->next;
	}
}
