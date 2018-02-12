/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:22:41 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/12 15:24:29 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add(t_process *prc, t_a *a)
{
	int	reg1;
	int	reg2;
	int	reg;
	int	curs;

	if (!check_cycle(prc, a))
		return ;
	curs = (prc->pc + 2) % MEM_SIZE;
	reg1 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	reg2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 2, &curs, a, 0);
	prc->reg[reg] = prc->reg[reg1] + prc->reg[reg2];
	ft_curseur(prc, prc->pc, curs, a);
	prc->pc = curs;
	prc->carry = 1;
}

void	sub(t_process *prc, t_a *a)
{
	int	reg1;
	int	reg2;
	int	reg;
	int	curs;

	if (!check_cycle(prc, a))
		return ;
	curs = (prc->pc + 2) % MEM_SIZE;
	reg1 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	reg2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 2, &curs, a, 0);
	prc->reg[reg] = prc->reg[reg1] - prc->reg[reg2];
	ft_curseur(prc, prc->pc, curs, a);
	prc->pc = curs;
	prc->carry = 1;
}

void	f_or(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	curs;
	int	reg;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	v2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	v1 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 2, &curs, a, 0);
	prc->reg[reg] = v1 | v2;
	ft_curseur(prc, prc->pc, curs, a);
	prc->pc = curs;
	prc->carry = 1;
}

void	f_xor(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	curs;
	int	reg;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	v2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	v1 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 2, &curs, a, 0);
	prc->reg[reg] = v1 ^ v2;
	ft_curseur(prc, prc->pc, curs, a);
	prc->pc = curs;
	prc->carry = 1;
}

void	f_and(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	curs;
	int	reg;

	curs = (prc->pc + 2) % MEM_SIZE;
	if (!check_cycle(prc, a))
		return ;
	v2 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 6, &curs, a, 0);
	v1 = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 4, &curs, a, 0);
	reg = rec_memory(a->mem[(prc->pc + 1) % MEM_SIZE] >> 2, &curs, a, 0);
	prc->reg[reg] = v1 & v2;
	ft_curseur(prc, prc->pc, curs, a);
	prc->pc = curs;
	prc->carry = 1;
}
