/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 21:29:46 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/19 18:51:58 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ld(t_process *prc, t_a *a)
{
	int		val;
	int		reg;

	if (!check_cycle(prc))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	val = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	if (reg != -1)
	{
		if (a->mem[(prc->tmp_pc + 1) % MEM_SIZE] == 0xd0)
		{
			val %= IDX_MOD;
			load_value(prc, val, a, reg);
		}
		else
			prc->reg[reg] = val;
		prc->carry = ((prc->reg[reg] == 0) ? 1 : 0);
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	lld(t_process *prc, t_a *a)
{
	int		val;
	int		reg;

	if (!check_cycle(prc))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	val = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	if (reg != -1)
	{
		if (a->mem[(prc->tmp_pc + 1) % MEM_SIZE] == 0xd0)
			load_value(prc, val, a, reg);
		else
			prc->reg[reg] = val;
		prc->carry = ((prc->reg[reg] == 0) ? 1 : 0);
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	ldi(t_process *prc, t_a *a)
{
	int		val;
	int		val2;
	int		reg;

	if (!check_cycle(prc))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	val = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6,
			prc, a, IND_SIZE);
	val2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4,
			prc, a, IND_SIZE);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (!(reg == -1 || ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1
					&& val == -1) || ((a->mem[(prc->tmp_pc + 1)
							% MEM_SIZE] >> 4 & 0x03) == 1 && val2 == -1)))
	{
		val = if_registre(val, prc, 6, a);
		val2 = if_registre(val2, prc, 4, a);
		val = ((val + val2) % IDX_MOD);
		load_value(prc, val, a, reg);
		prc->carry = ((prc->reg[reg] == 0) ? 1 : 0);
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	lldi(t_process *prc, t_a *a)
{
	int		val;
	int		val2;
	int		reg;

	if (!check_cycle(prc))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	val = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6,
			prc, a, IND_SIZE);
	val2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4,
			prc, a, IND_SIZE);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (!(reg == -1 || ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1
					&& val == -1) || ((a->mem[(prc->tmp_pc + 1)
							% MEM_SIZE] >> 4 & 0x03) == 1 && val2 == -1)))
	{
		val = if_registre(val, prc, 6, a);
		val2 = if_registre(val2, prc, 4, a);
		val = val + val2;
		load_value(prc, val, a, reg);
		prc->carry = ((prc->reg[reg] == 0) ? 1 : 0);
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}
