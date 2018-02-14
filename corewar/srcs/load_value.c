/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 21:29:46 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/14 14:10:54 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ld(t_process *prc, t_a *a)
{
	int		val;
	int		curs;
	int		reg;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	val = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	if (a->mem[(prc->pc + 1) % MEM_SIZE] == 0xd0)
	{
		val %= IDX_MOD;
		prc->reg[reg] = a->mem[(prc->pc
				+ val) % MEM_SIZE] << 24;
		prc->reg[reg] += a->mem[(prc->pc
				+ val + 1) % MEM_SIZE] << 16;
		prc->reg[reg] += a->mem[(prc->pc
				+ val % + 2) % MEM_SIZE] << 8;
		prc->reg[reg] += a->mem[(prc->pc
				+ val % + 3) % MEM_SIZE];
	}
	else
		prc->reg[reg] = val;
	ft_curseur(prc, prc->pc, curs, a);
	prc->pc = curs;
	if (prc->reg[reg] == 0)
		prc->carry = 1;
	else
		prc->carry = 0;
}

void	lld(t_process *prc, t_a *a)
{
	int		val;
	int		curs;
	int		reg;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	val = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 1);
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	if (a->mem[(prc->pc + 1) % MEM_SIZE] == 0xd0)
	{
		prc->reg[reg] = a->mem[(prc->pc + val) % MEM_SIZE] << 24;
		prc->reg[reg] += a->mem[(prc->pc + val + 1)
			% MEM_SIZE] << 16;
		prc->reg[reg] += a->mem[(prc->pc + val + 2)
			% MEM_SIZE] << 8;
		prc->reg[reg] += a->mem[(prc->pc + val + 3) % MEM_SIZE];
	}
	else
		prc->reg[reg] = val;
	ft_curseur(prc, prc->pc, curs, a);
	prc->pc = curs;
	if (prc->reg[reg] == 0)
		prc->carry = 1;
	else
		prc->carry = 0;
}

void	ldi(t_process *prc, t_a *a)
{
	int		val;
	int		val2;
	int		curs;
	int		reg;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	val = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 1);
	val = ((a->mem[(prc->pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1) ?
		prc->reg[val] : val;
	val2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 1);
	val2 = ((a->mem[(prc->pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
		prc->reg[val2] : val2;
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 2, &curs, a, 0);
	val = (val + val2) % IDX_MOD;
	prc->reg[reg] = a->mem[(prc->pc + val) % MEM_SIZE] << 24;
	prc->reg[reg] += a->mem[(prc->pc + val + 1)
		% MEM_SIZE] << 16;
	prc->reg[reg] += a->mem[(prc->pc + val + 2)
		% MEM_SIZE] << 8;
	prc->reg[reg] += a->mem[(prc->pc + val + 3) % MEM_SIZE];
	ft_curseur(prc, prc->pc, curs, a);
	prc->pc = curs;
	if (prc->reg[reg] == 0)
		prc->carry = 1;
	else
		prc->carry = 0;
}

void	lldi(t_process *prc, t_a *a)
{
	int		val;
	int		val2;
	int		curs;
	int		reg;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	val = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	val = ((a->mem[(prc->pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1) ?
		prc->reg[val] : val;
	val2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	val2 = ((a->mem[(prc->pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
		prc->reg[val2] : val2;
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 2, &curs, a, 0);
	val = val + val2;
	prc->reg[reg] = a->mem[(prc->pc + val) % MEM_SIZE] << 24;
	prc->reg[reg] += a->mem[(prc->pc + val + 1)
		% MEM_SIZE] << 16;
	prc->reg[reg] += a->mem[(prc->pc + val + 2)
		% MEM_SIZE] << 8;
	prc->reg[reg] += a->mem[(prc->pc + val + 3) % MEM_SIZE];
	ft_curseur(prc, prc->pc, curs, a);
	prc->pc = curs;
	if (prc->reg[reg] == 0)
		prc->carry = 1;
	else
		prc->carry = 0;
}
