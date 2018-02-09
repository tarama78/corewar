/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:02:28 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/09 21:04:44 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_cycle(int cycle, t_process *prc)
{
	if (prc->cycle_wait == -1)
		prc->cycle_wait = cycle;
	else if (prc->cycle_wait >= 0)
		prc->cycle_wait--;
	if (prc->cycle_wait == -1)
		return (1);
	return (0);
}

int		rec_memory(char type, int *curs, t_a *a, int addr)
{
	if (type & 0x03 == 0x03 && !addr)
	{
		*curs += 3;
		return (*(int *)(a->mem + *curs - 3));
	}
	if (type & 0x02)
	{
		*curs += 2;
		return ((int)*(short *)(a->mem + *curs - 1));
	}
	if (type & 0x01)
	{
		*curs += 1;
		return ((int)*(char *)(a->mem + *curs - 1));
	}
	return (0);
}

//UTILISE AVANT LE TABLEAU DE POINTEUR SUR FONCTION,
//SI NON VALIDE, AVANCER D'UNE CASE

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
	while (g_op_tab[i].type_arg[++j])
	{
		tmp = arg_code >> 6;
		if (tmp == 1 && (g_op_tab[i].type_arg[j] & 0x01 != 0x1))
			return (0);
		else if (tmp == 2 && (g_op_tab[i].type_arg[j] & 0x02 != 0x02))
			return (0);
		else if (tmp == 3 && (g_op_tab[i].type_arg[j] & 0x03 != 0x03))
			return (0);
		if (tmp == 0)
			return (0);
		arg_code = arg_code << 2;
	}
	if (arg_code != 0)
		return (0);
	return (1)
}
