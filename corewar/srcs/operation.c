/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:22:41 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/10 15:52:37 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add(t_process *prc, t_a *a)
{
	if (!check_cycle(prc, a))
		return ;
	if ((a->mem[prc->pc + 1] & 0x54) == 0)
	{
		prc->reg[a->mem[(prc->pc + 4) % MEM_SIZE]] =
			prc->reg[a->mem[(prc->pc + 2) % MEM_SIZE]]
			+ prc->reg[a->mem[(prc->pc + 3) % MEM_SIZE]];
	}
	prc->pc = (prc->pc + 5) % MEM_SIZE;
	prc->carry = (prc->carry + 1) % 2;
}

void	sub(t_process *prc, t_a *a)
{
	if (!check_cycle(prc, a))
		return ;
	if ((a->mem[prc->pc + 1] & 0x54) == 0)
	{
		prc->reg[a->mem[prc->pc + 4]] =
			prc->reg[a->mem[prc->pc + 2]]
			- prc->reg[a->mem[prc->pc + 3]];
	}
	prc->pc = (prc->pc + 5) % MEM_SIZE;
	prc->carry = (prc->carry + 1) % 2;
}

void	f_or(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	curs;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	v1 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	v2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	prc->reg[a->mem[curs]] = v1 | v2;
	prc->pc = (curs + 1) % MEM_SIZE;
	prc->carry = (prc->carry + 1) % 2;
}

void	f_xor(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	curs;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	v1 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	v2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	prc->reg[a->mem[curs]] = v1 ^ v2;
	prc->pc = (curs + 1) % MEM_SIZE;
	prc->carry = (prc->carry + 1) % 2;
}

void	f_and(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	curs;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	v1 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	v2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	prc->reg[a->mem[curs]] = v1 & v2;
	prc->pc = (curs + 1) % MEM_SIZE;
	prc->carry = (prc->carry + 1) % 2;
}
