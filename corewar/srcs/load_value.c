/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 21:29:46 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/10 12:40:22 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ld(t_process *prc, t_a *a)
{
	int		val;
	int		curs;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	val = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	if (rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] == 0xd0))
	{
		prc->reg[a->mem[curs]] = (int)mem[(prc->pc
				+ (val % IDX_MOD)) % MEM_SIZE] << 6;
		prc->reg[a->mem[curs]] += (int)mem[(prc->pc
				+ (val % IDX_MOD + 1)) % MEM_SIZE] << 4;
		prc->reg[a->mem[curs]] += (int)mem[(prc->pc
				+ (val % IDX_MOD + 2)) % MEM_SIZE] << 2;
		prc->reg[a->mem[curs]] += (int)mem[(prc->pc
				+ (val % IDX_MOD +3)) % MEM_SIZE];
	else
		prc->reg[a->mem[curs]] = val;
	prc->pc = (curs + 1) % MEM_SIZE;
	prc->carry = (prc->carry + 1) % 2;
}

void	lld(t_process *prc, t_a *a)
{
	int		val;
	int		curs;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	val = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	if (a->mem[(prc->pc + 1) % MEM_SIZE] == 0xd0)
	{
		prc->reg[a->mem[curs]] = (int)mem[(prc->pc + val) % MEM_SIZE] << 6;
		prc->reg[a->mem[curs]] += (int)mem[(prc->pc + val + 1)
			% MEM_SIZE] << 4;
		prc->reg[a->mem[curs]] += (int)mem[(prc->pc + val + 2)
			% MEM_SIZE] << 2;
		prc->reg[a->mem[curs]] += (int)mem[(prc->pc + val + 3) % MEM_SIZE];
	else
		prc->reg[a->mem[curs]] = val;
	prc->pc = (curs + 1) % MEM_SIZE;
	prc->carry = (prc->carry + 1) % 2;
}

void	ldi(t_process *prc, t_a *a)
{
	int		val;
	int		val2;
	int		curs;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	val = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	val = (a->mem[(prc->pc + 1) % MEM_SIZE] >> 6 & 0x03 == 1) ?
		prc->reg[val] : val;
	val2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	val2 = (a->mem[(prc->pc + 1) % MEM_SIZE] >> 4 & 0x03 == 1) ?
		prc->reg[val2] : val2;
	val = (val + val2) % IDX_MOD;
	prc->reg[a->mem[curs]] = (int)mem[(prc->pc + val) % MEM_SIZE] << 6;
	prc->reg[a->mem[curs]] += (int)mem[(prc->pc + val + 1)
		% MEM_SIZE] << 4;
	prc->reg[a->mem[curs]] += (int)mem[(prc->pc + val + 2)
		% MEM_SIZE] << 2;
	prc->reg[a->mem[curs]] += (int)mem[(prc->pc + val + 3) % MEM_SIZE];
	prc->carry = (prc->carry + 1) % 2;
}

void	lldi(t_process *prc, t_a *a)
{
	int		val;
	int		val2;
	int		curs;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	val = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	val = (a->mem[(prc->pc + 1) % MEM_SIZE] >> 6 & 0x03 == 1) ?
		prc->reg[val] : val;
	val2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	val2 = (a->mem[(prc->pc + 1) % MEM_SIZE] >> 4 & 0x03 == 1) ?
		prc->reg[val2] : val2;
	val = val + val2;
	prc->reg[a->mem[curs]] = (int)mem[(prc->pc + val) % MEM_SIZE] << 6;
	prc->reg[a->mem[curs]] += (int)mem[(prc->pc + val + 1)
		% MEM_SIZE] << 4;
	prc->reg[a->mem[curs]] += (int)mem[(prc->pc + val + 2)
		% MEM_SIZE] << 2;
	prc->reg[a->mem[curs]] += (int)mem[(prc->pc + val + 3) % MEM_SIZE];
	prc->carry = (prc->carry + 1) % 2;
}
