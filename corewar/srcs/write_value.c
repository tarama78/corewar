/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:20:55 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/18 06:40:53 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	ft_swap(int val)
{
	int	rev;
	int	tmp;

	rev = 0;
	tmp = val & 0xFF000000;
	rev += (tmp >> 24) & 0x000000FF;
	tmp = val & 0x00FF0000;
	rev += (tmp >> 8) & 0x0000FF00;
	tmp = val & 0x0000FF00;
	rev += (tmp << 8) & 0x00FF0000;
	tmp = val & 0x000000FF;
	rev += (tmp << 24) & 0xFF000000;
	return (rev);
}

static void	write_in_mem(t_a *a, t_process *prc, int reg, int addr)
{
	int		i;
	char	nb_player;
	int		tmp;

	nb_player = 0;
	while (++nb_player <= a->num_of_player)
		if (a->player[nb_player - 1].player_number_print == prc->num_player)
			break ;
	i = -1;
	tmp = ft_swap(prc->reg[reg]);
	while (addr < 0)
		addr += MEM_SIZE;
	while (++i < 4)
	{
		a->mem[(addr + i) % MEM_SIZE] = (char)tmp;
		a->mem_info[(addr + i) % MEM_SIZE].cycle = a->cycle;
		a->mem_info[(addr + i) % MEM_SIZE].player = nb_player;
		tmp = tmp >> 8;
	}
}

void		st(t_process *prc, t_a *a)
{
	int		addr;
	int		reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	addr = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, IND_SIZE);
	if (a->mem[(prc->tmp_pc + 1) % MEM_SIZE] == 0x50)
		prc->reg[addr] = prc->reg[reg];
	else
	{
		addr = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
			prc->reg[addr] : addr;
		addr = addr % IDX_MOD;
		write_in_mem(a, prc, reg, (prc->tmp_pc + addr) % MEM_SIZE);
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
	prc->reg[0] = 0;
}

void		sti(t_process *prc, t_a *a)
{
	int		addr;
	int		addr2;
	int		reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	addr = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, IND_SIZE);
	addr = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
		prc->reg[addr] : addr;
	addr2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, IND_SIZE);
	addr2 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2 & 0x03) == 1) ?
		prc->reg[addr2] : addr2;
	addr = (addr + addr2) % IDX_MOD;
	write_in_mem(a, prc, reg, (prc->tmp_pc + addr) % MEM_SIZE);
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}
