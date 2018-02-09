/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:20:55 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/09 22:35:11 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	st(t_process *prc, t_a *a)
{
	int		addr;
	int		curs;
	int		reg;

	curs = (prc->pc + 2) % mem_size;
	reg = rec_memory(a->mem[prc->pc + 1] >> 4, &curs, a, 1);
	addr = rec_memory(a->mem[prc->pc + 1] >> 4, &curs, a, 1);
	addr = (a->mem[prc->pc + 1] >> 4 & 0x03 == 1) ? prc->reg[addr] : addr;
	addr = addr % idx_mod;
	mem[(prc->pc + addr) % mem_size] = (uint8_t)prc->reg[reg] >> 6;
	mem[(prc->pc + addr + 1) % mem_size]
		= (uint8_t)prc->reg[mem[reg]] >> 4;
	mem[(prc->pc + addr + 2) % mem_size]
		= (uint8_t)prc->reg[mem[reg]] >> 2;
	mem[(prc->pc + addr + 3) % mem_size]
		= (uint8_t)prc->reg[mem[reg]];
	prc->pc = (curs + 1) % mem_size;
}

void	sti(t_process *prc, t_a *a)
{
	int		addr;
	int		addr2;
	int		curs;
	int		reg;

	curs = (prc->pc + 2) % mem_size;
	reg = rec_memory(a->mem[prc->pc + 1] >> 4, &curs, a, 1);
	addr = rec_memory(a->mem[prc->pc + 1] >> 4, &curs, a, 1);
	addr = (a->mem[prc->pc + 1] >> 4 & 0x03 == 1) ? prc->reg[addr] : addr;
	addr2 = rec_memory(a->mem[prc->pc + 1] >> 4, &curs, a, 1);
	addr = (a->mem[prc->pc + 1] >> 4 & 0x03 == 1) ? prc->reg[addr2] : addr2;
	addr = (addr + addr2) % idx_mod;
	mem[(prc->pc + addr) % mem_size] = (uint8_t)prc->reg[reg] >> 6;
	mem[(prc->pc + addr + 1) % mem_size]
		= (uint8_t)prc->reg[mem[reg]] >> 4;
	mem[(prc->pc + addr + 2) % mem_size]
		= (uint8_t)prc->reg[mem[reg]] >> 2;
	mem[(prc->pc + addr + 3) % mem_size]
		= (uint8_t)prc->reg[mem[reg]];
	prc->pc = (curs + 1) % mem_size;
}
