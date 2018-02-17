/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:02:28 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/16 18:59:41 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	mod_carry(t_process *prc, t_a *a)
{
	int	comm;
	int	curs;
	int	code;
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (g_op_tab[++i].opcode != a->mem[prc->pc] && g_op_tab[i].opcode)
		;
	curs = prc->pc + 1;
	code = a->mem[curs % MEM_SIZE];
	comm = a->mem[prc->pc];
	if (comm == 2 || comm == 4 || comm == 5 || comm == 6 || comm == 7
			|| comm == 8 || comm == 10 || comm == 13 || comm == 14)
		prc->carry = 0;
	while (g_op_tab[i].type_arg[++j])
	{
		if (((code >> 8) & 0x03) == 0)
			code = code << 2;
		if ((g_op_tab[i].type_arg[j] & 0x01) && ((code >> 8) & 0x03) == 1)
			curs++;
		else if ((g_op_tab[i].type_arg[j] & 0x02) && ((code >> 8) & 0x03) == 2)
			curs += 2;
		else if ((g_op_tab[i].type_arg[j] & 0x04) && ((code >> 8) & 0x03) == 3)
			curs += 4;
		code = code << 2;
	}
	curs = curs % MEM_SIZE;
	ft_curseur(prc, prc->pc, curs, a);
	prc->pc = curs;
}

void	rec_memory_2(int *val, t_a *a, int *curs)
{
	*val = a->mem[*curs] << 24;
	*curs = (*curs + 1) % MEM_SIZE;
	*val += a->mem[*curs] << 16;
	*curs = (*curs + 1) % MEM_SIZE;
	*val += a->mem[*curs] << 8;
	*curs = (*curs + 1) % MEM_SIZE;
	*val += a->mem[*curs];
	*curs = (*curs + 1) % MEM_SIZE;
}

int		rec_memory(char type, int *curs, t_a *a, int addr)
{
	int		val;

	val = 0;
	if ((type & 0x03) == 0x02 && !addr)
		rec_memory_2(&val, a, curs);
	else if ((type & 0x03) > 1)
	{
		val = ((char)a->mem[*curs] << 8) & 0x0000FF00;
		*curs = (*curs + 1) % MEM_SIZE;
		val += (((char)a->mem[*curs])) & 0x000000FF;
		val = val & 0x0000FFFF;
		if ((short)val < 0)
			val = val | 0xFFFF0000;
		*curs = (*curs + 1) % MEM_SIZE;
	}
	else if (type & 0x01)
	{
		val = a->mem[*curs];
		if (val <= 0 || val > REG_NUMBER)
			val = 0;
		*curs = (*curs + 1) % MEM_SIZE;
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
