/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:02:28 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/10 13:59:50 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_cycle(t_process *prc, t_a *a)
{
	char	nb_player;

	if (prc->cycle_wait == -1)
	{
		while (g_op_tab[++i].opcode != a->mem[prc->pc] && g_op_tab[i].opcode)
			;
		prc->cycle_wait = g_op_tab[i].nb_cycle;
		a->mem_info[prc->pc].process = 1;
		nb_player = 0;
		while (a->player[++nb_player - 1] && nb_player <= MAX_PLAYER)
			if (a->player[nb_player - 1]->player_number_print == prc->num_player)
				break ;
		a->mem_info[prc->pc].player_process = nb_player;
	}
	else if (prc->cycle_wait >= 0)
		prc->cycle_wait--;
	if (prc->cycle_wait == -1)
	{
		a->mem_info[prc->pc]->process = 0;
		return (1);
	}
	return (0);
}

int		rec_memory(char type, int *curs, t_a *a, int addr)
{
	int		val;

	val = 0;
	if (type & 0x03 == 0x03 && !addr)
	{
		val = a->mem[*curs] << 6;
		*curs = (*curs + 1) % MEM_SIZE;
		val += a->mem[*curs] << 4;
		*curs = (*curs + 1) % MEM_SIZE;
		val += a->mem[*curs] << 2;
		*curs = (*curs + 1) % MEM_SIZE;
		val += a->mem[*curs];
		*curs = (*curs + 1) % MEM_SIZE;
	}
	else if (type & 0x02)
	{
		val = a->mem[*curs] << 2;
		*curs = (*curs + 1) % MEM_SIZE;
		val += a->mem[*curs];
		*curs = (*curs + 1) % MEM_SIZE;
	}
	else if (type & 0x01)
	{
		val = a->mem[*curs];
		*curs = (*curs + 1) % MEM_SIZE;
	}
	return (val);
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
