/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:13:45 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/18 08:41:23 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_cycle(t_process *prc, t_a *a)
{
	int		i;

	if (prc->cycle_wait <= -1)
	{
		i = -1;
		while (g_op_tab[++i].opcode != a->mem[prc->pc] && g_op_tab[i].opcode)
			;
		prc->cycle_wait = g_op_tab[i].nb_cycle - 1;
	}
	if (prc->cycle_wait == 0)
		return (1);
	return (0);
}

void	ft_curseur(t_process *prc, int pc, int curs, t_a *a)
{
	char	nb_player;

	a->mem_info[pc].process = 0;
	a->mem_info[curs].process = 1;
	nb_player = 0;
	while (++nb_player <= a->num_of_player)
		if (a->player[nb_player - 1].player_number_print == prc->num_player)
			break ;
	a->mem_info[curs].player_process = nb_player;
}

int		rec_memory_xbyte(t_process *prc, int size, t_a *a)
{
	int	val;
	int	i;

	val = 0;
	i = -1;
	while (++i < size)
	{
		val = val << 8;
		val += ((char)a->mem[prc->pc]) & 0x000000FF;
		prc->pc = (prc->pc + 1) % MEM_SIZE;
	}
	if (size == 2)
		if ((short)val < 0)
			val |= 0xFFFF0000;
	return (val);
}
