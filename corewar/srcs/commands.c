/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:02:28 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/18 08:40:51 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	mod_carry(t_process *prc, t_a *a)
{
	int	comm;
	int	curs;
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (g_op_tab[++i].opcode != a->mem[prc->pc] && g_op_tab[i].opcode)
		;
	curs = prc->pc + 1;
	comm = a->mem[prc->pc];
	if (comm == 2 || comm == 4 || comm == 5 || comm == 6 || comm == 7
			|| comm == 8 || comm == 10 || comm == 13 || comm == 14)
		prc->carry = 0;
	while (g_op_tab[i].type_arg[++j])
	{
		if (g_op_tab[i].type_arg[j] & 0x01)
			curs++;
		else if (g_op_tab[i].type_arg[j] & 0x02)
			curs += 2;
		else if (g_op_tab[i].type_arg[j] & 0x04)
			curs += 4;
	}
	ft_curseur(prc, prc->pc, curs % MEM_SIZE, a);
	prc->pc = curs % MEM_SIZE;
}

void	rec_memory_2(int *val, t_a *a, t_process *prc)
{
	int	addr;
	int	i;

	i = -1;
	addr = a->mem[prc->pc] << 8;
	prc->pc = (prc->pc + 1) % MEM_SIZE;
	addr += a->mem[prc->pc];
	prc->pc = (prc->pc + 1) % MEM_SIZE;
	addr = addr % IDX_MOD;
	while (++i < IND_SIZE)
	{
		*val = *val << 8;
		*val += (((char)a->mem[(addr + i + prc->tmp_pc)
					% MEM_SIZE])) & 0x000000FF;
	}
	if (IND_SIZE == 2)
		if ((short)(*val) < 0)
			*val = *val | 0xFFFF0000;
}

int		rec_memory(char type, t_process *prc, t_a *a, int size)
{
	int		val;
	int		i;

	val = 0;
	i = -1;
	if (size == 0)
		size = ((type & 0x03) == 0x03) ? IND_SIZE : REG_SIZE;
	if ((type & 0x03) == 0x03 && (prc->pc - prc->tmp_pc) > 1 && size != REG_SIZE
			&& a->mem[prc->tmp_pc] != 3 && a->mem[prc->tmp_pc] != 11)
		rec_memory_2(&val, a, prc);
	else if ((type & 0x03) > 1)
		val = rec_memory_xbyte(prc, size, a);
	else if (type & 0x01)
	{
		val = a->mem[prc->pc];
		if (val <= 0 || val > REG_NUMBER)
			val = 0;
		prc->pc = (prc->pc + 1) % MEM_SIZE;
	}
	return (val);
}

int		check_type_2(int *tmp, int i, int j)
{
	if ((*tmp & 0x0003) == 1 &&
			((g_op_tab[i].type_arg[j] & 0x01) != 0x1))
		return (0);
	else if ((*tmp & 0x0003) == 2 &&
			((g_op_tab[i].type_arg[j] & 0x02) != 0x02))
		return (0);
	else if ((*tmp & 0x0003) == 3 &&
			((g_op_tab[i].type_arg[j] & 0x04) != 0x04))
		return (0);
	if ((*tmp & 0x0003) == 0 &&
			((g_op_tab[i].type_arg[j] & 0x07) != 0x00))
		return (0);
	return (1);
}

int		check_type(t_process *prc, t_a *a)
{
	int		i;
	int		j;
	int		arg_code;
	int		tmp;

	i = -1;
	j = -1;
	arg_code = a->mem[prc->pc + 1];
	while (g_op_tab[++i].opcode != a->mem[prc->pc] && g_op_tab[i].opcode)
		;
	if (g_op_tab[i].opcode != a->mem[prc->pc])
		return (0);
	if (a->mem[prc->pc] == 1 || a->mem[prc->pc] == 9
			|| a->mem[prc->pc] == 12 || a->mem[prc->pc] == 15)
		return (1);
	while (++j < 4)
	{
		tmp = arg_code >> 6;
		if (check_type_2(&tmp, i, j) == 0)
			return (0);
		arg_code = arg_code << 2;
	}
	return (1);
}
