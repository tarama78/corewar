/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:20:55 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/10 21:44:28 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	write_in_mem(t_a *a, t_process *prc, int reg, int addr)
{
	int		i;
	char	nb_player;

	nb_player = 0;
	while (++nb_player <= a->num_of_player)
		if (a->player[nb_player - 1].player_number_print == prc->num_player)
			break ;
	i = -1;
	while (++i < 4)
	{
		a->mem_info[(prc->pc + addr + i) % MEM_SIZE].cycle = a->cycle;
		a->mem_info[(prc->pc + addr + i) % MEM_SIZE].player = nb_player;
		a->mem[(prc->pc + addr + i) % MEM_SIZE]
		= (char)(prc->reg[reg] >> (6 - (2 * i)));
	}
}

void		st(t_process *prc, t_a *a)
{
	int		addr;
	int		curs;
	int		reg;

	if (!check_cycle(prc, a))
		return ;
	curs = (prc->pc + 2) % MEM_SIZE;
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 1);
	addr = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 1);
	addr = ((a->mem[(prc->pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
		prc->reg[addr] : addr;
	addr = addr % IDX_MOD;
	write_in_mem(a, prc, reg, addr);
	prc->pc = curs;
}

void		sti(t_process *prc, t_a *a)
{
	int		addr;
	int		addr2;
	int		curs;
	int		reg;

	if (!check_cycle(prc, a))
		return ;
	curs = (prc->pc + 2) % MEM_SIZE;
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	addr = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 1);
	addr = ((a->mem[(prc->pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
		prc->reg[addr] : addr;
	addr2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 2, &curs, a, 1);
	addr2 = ((a->mem[(prc->pc + 1) % MEM_SIZE] >> 2 & 0x03) == 1) ?
		prc->reg[addr2] : addr2;
	addr = (addr + addr2) % IDX_MOD;
	write_in_mem(a, prc, reg, addr);
	prc->pc = curs;
}
