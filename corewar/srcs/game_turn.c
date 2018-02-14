/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:22:00 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/13 12:34:15 by ynacache         ###   ########.fr       */
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
		a->mem_info[prc->pc].process = 0;
		a->player[prc->player_index].nb_process--;
		free(prc);
		if (!a->process)
			return ;
	}
	prc = a->process;
	prc->live = 0;
	while (prc && prc->next)
	{
		if (prc->next->live == 0)
		{
			tmp = prc->next->next;
			a->mem_info[prc->next->pc].process = 0;
			a->player[prc->next->player_index].nb_process--;
			free(prc->next);
			prc->next = tmp;
		}
		prc = prc->next;
		if (prc)
			prc->live = 0;
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
		a->live += a->player[i + 1].nb_live_current;
		a->player[i + 1].nb_live_current = 0;
	}
	if (a->live >= NBR_LIVE || (a->cycle - a->last_dec_cycle >= MAX_CHECKS))
	{
		a->cycle_to_die -= CYCLE_DELTA;
		a->last_dec_cycle = a->cycle;
	}
	return (a->cycle_to_die);
}

void		ft_print_dump(t_a *a)
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

void		ft_check_dump(t_a *a)
{
	if (a->dump_cycle == 0)
	{
		ft_print_dump(a);
		exit(EXIT_SUCCESS);
	}
	else
		(a->dump_cycle)--;
}

static int	ft_command(t_a *a, int *pause)
{
	int		command;

	command = getch();
	if (command == ' ')
		*pause = !(*pause);//(pause + 1) % 2;
	else if (command == '-')
		a->speed += (a->speed + CHANGE_SPEED <= 200000) ? CHANGE_SPEED : 0;
	else if (command == '=')
		a->speed = SPEED;
	else if (command == '+')
		a->speed -= (a->speed - CHANGE_SPEED >= 0) ?  CHANGE_SPEED : 0;
	return (command);
}

void	game_loop(t_a *a, void (**f)(t_process *, t_a *))
{
	uint64_t	nxt_cycle_die;
	int			command;
	int			pause;
	int			time_start;

	pause = 0;
	command = 0;
//	nodelay(stdscr, TRUE);
	nxt_cycle_die = a->cycle_to_die;
	if (a->visu)
		ft_print(a);
	while (a->process && command != 27)
	{
		if (pause || !a->visu)
		{
			time_start = clock();
			if (a->cycle >= nxt_cycle_die)
				nxt_cycle_die += new_cycle(a);
			if (!a->process)
				return ;
			game_turn(a, f);
	  	if (a->dump_cycle != -1)
		  	ft_check_dump(a);
			a->cycle++;
			if (a->visu && clock() - time_start < (unsigned long)a->speed)
				usleep((a->speed - (clock() - time_start)));
		}
		if (a->visu)
    {
      command = ft_command(a, &pause);
			ft_print(a);
	  }
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
