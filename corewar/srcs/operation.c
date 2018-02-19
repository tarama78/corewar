/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:22:41 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/18 06:30:45 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add(t_process *prc, t_a *a)
{
	int	reg1;
	int	reg2;
	int	reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	reg1 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	reg2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (!(reg == 0 || reg1 == 0 || reg2 == 0))
		prc->reg[reg] = prc->reg[reg1] + prc->reg[reg2];
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
	if (prc->reg[reg] == 0 && reg != 0)
		prc->carry = 1;
	else
		prc->carry = 0;
	prc->reg[0] = 0;
}

void	sub(t_process *prc, t_a *a)
{
	int	reg1;
	int	reg2;
	int	reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	reg1 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	reg2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (!(reg == 0 || reg1 == 0 || reg2 == 0))
		prc->reg[reg] = prc->reg[reg1] - prc->reg[reg2];
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
	if (prc->reg[reg] == 0 && reg != 0)
		prc->carry = 1;
	else
		prc->carry = 0;
	prc->reg[0] = 0;
}

void	f_or(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	v2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	v2 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1) ?
		prc->reg[v2] : v2;
	v1 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	v1 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
		prc->reg[v1] : v1;
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (reg != 0)
		prc->reg[reg] = v1 | v2;
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
	if (prc->reg[reg] == 0 && reg != 0)
		prc->carry = 1;
	else
		prc->carry = 0;
	prc->reg[0] = 0;
}

void	f_xor(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	v2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	v2 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1) ?
		prc->reg[v2] : v2;
	v1 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	v1 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
		prc->reg[v1] : v1;
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (reg != 0)
		prc->reg[reg] = v1 ^ v2;
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
	if (prc->reg[reg] == 0 && reg != 0)
		prc->carry = 1;
	else
		prc->carry = 0;
	prc->reg[0] = 0;
}

void	f_and(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	reg;

	if (!check_cycle(prc, a))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	v2 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6, prc, a, 0);
	v2 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 6 & 0x03) == 1) ?
		prc->reg[v2] : v2;
	v1 = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4, prc, a, 0);
	v1 = ((a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 4 & 0x03) == 1) ?
		prc->reg[v1] : v1;
	reg = rec_memory(a->mem[(prc->tmp_pc + 1) % MEM_SIZE] >> 2, prc, a, 0);
	if (reg != 0)
		prc->reg[reg] = v1 & v2;
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
	if (prc->reg[reg] == 0 && reg != 0)
		prc->carry = 1;
	else
		prc->carry = 0;
	prc->reg[0] = 0;
}
