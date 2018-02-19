/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 21:29:46 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/19 13:30:02 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ld(t_process *prc, t_a *a)
{
	int		val;
	int		reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	val = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	if (a->mem[(prc->tmp_pc + 1) % MEM_SIZE] == 0xd0)
	{
		val %= IDX_MOD;
		prc->reg[reg] = a->mem[(prc->tmp_pc + val) % MEM_SIZE] << 24;
		prc->reg[reg] += a->mem[(prc->tmp_pc + val + 1) % MEM_SIZE] << 16;
		prc->reg[reg] += a->mem[(prc->tmp_pc + val + 2) % MEM_SIZE] << 8;
		prc->reg[reg] += a->mem[(prc->tmp_pc + val + 3) % MEM_SIZE];
	}
	else
		prc->reg[reg] = val;
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
	prc->carry = ((prc->reg[reg] == 0) ? 1 : 0);
	prc->reg[0] = 0;
}

void	lld(t_process *prc, t_a *a)
{
	int		val;
	int		reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	val = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	if (a->mem[(prc->tmp_pc + 1) % MEM_SIZE] == 0xd0)
	{
		prc->reg[reg] = a->mem[(prc->tmp_pc + val) % MEM_SIZE] << 24;
		prc->reg[reg] += a->mem[(prc->tmp_pc + val + 1) % MEM_SIZE] << 16;
		prc->reg[reg] += a->mem[(prc->tmp_pc + val + 2) % MEM_SIZE] << 8;
		prc->reg[reg] += a->mem[(prc->tmp_pc + val + 3) % MEM_SIZE];
	}
	else
		prc->reg[reg] = val;
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
	if (prc->reg[reg] == 0)
		prc->carry = 1;
	else
		prc->carry = 0;
	prc->reg[0] = 0;
}

void	ldi(t_process *prc, t_a *a)
{
	int		val;
	int		val2;
	int		reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	val = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6,
			prc, a, IND_SIZE);
	val = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1) ?
		prc->reg[val] : val;
	val2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4,
			prc, a, IND_SIZE);
	val2 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
		prc->reg[val2] : val2;
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	val = ((val + val2) % IDX_MOD);
	prc->reg[reg] = a->mem[(prc->tmp_pc + val) % MEM_SIZE] << 24;
	prc->reg[reg] += a->mem[(prc->tmp_pc + val + 1) % MEM_SIZE] << 16;
	prc->reg[reg] += a->mem[(prc->tmp_pc + val + 2) % MEM_SIZE] << 8;
	prc->reg[reg] += a->mem[(prc->tmp_pc + val + 3) % MEM_SIZE];
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
	prc->carry = ((prc->reg[reg] == 0) ? 1 : 0);
	prc->reg[0] = 0;
}

void	lldi(t_process *prc, t_a *a)
{
	int		val;
	int		val2;
	int		reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	val = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6,
			prc, a, IND_SIZE);
	val = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1) ?
		prc->reg[val] : val;
	val2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4,
			prc, a, IND_SIZE);
	val2 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
		prc->reg[val2] : val2;
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	val = val + val2;
	prc->reg[reg] = a->mem[(prc->tmp_pc + val) % MEM_SIZE] << 24;
	prc->reg[reg] += a->mem[(prc->tmp_pc + val + 1) % MEM_SIZE] << 16;
	prc->reg[reg] += a->mem[(prc->tmp_pc + val + 2) % MEM_SIZE] << 8;
	prc->reg[reg] += a->mem[(prc->tmp_pc + val + 3) % MEM_SIZE];
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
	prc->carry = ((prc->reg[reg] == 0) ? 1 : 0);
	prc->reg[0] = 0;
}
