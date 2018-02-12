/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:02:28 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/12 17:10:32 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_cycle(t_process *prc, t_a *a)
{
//	char	nb_player;
	int		i;

	if (prc->cycle_wait == -1)
	{
		i = -1;
		while (g_op_tab[++i].opcode != a->mem[prc->pc] && g_op_tab[i].opcode)
			;
		prc->cycle_wait = g_op_tab[i].nb_cycle;
//		a->mem_info[prc->pc].process = 1;
//		nb_player = 0;
//		while (++nb_player <= a->num_of_player)
//			if (a->player[nb_player - 1].player_number_print == prc->num_player)
//				break ;
//		a->mem_info[prc->pc].player_process = nb_player;
	}
	if (prc->cycle_wait >= 0)
		prc->cycle_wait--;
	if (prc->cycle_wait == -1)
	{
//		a->mem_info[prc->pc].process = 0;
		return (1);
	}
	return (0);
}

void ft_curseur(t_process *prc, int pc, int curs, t_a *a)
{
	char	nb_player;

	a->mem_info[pc].process = 0;
	a->mem_info[curs].process = 1;
	nb_player = 0;
	while (++nb_player <= a->num_of_player)
		if (a->player[nb_player - 1].player_number_print == prc->num_player)
			break ;
	a->mem_info[curs].player_process = nb_player;
}

int		rec_memory(char type, int *curs, t_a *a, int addr)
{
	int		val;

	val = 0;
	if ((type & 0x03) == 0x02 && !addr)
	{
		val = a->mem[*curs] << 24;
		*curs = (*curs + 1) % MEM_SIZE;
		val += a->mem[*curs] << 16;
		*curs = (*curs + 1) % MEM_SIZE;
		val += a->mem[*curs] << 8;
		*curs = (*curs + 1) % MEM_SIZE;
		val += a->mem[*curs];
		*curs = (*curs + 1) % MEM_SIZE;
	}
	else if ((type & 0x03) > 1)
	{
		val = a->mem[*curs] << 8;
		*curs = (*curs + 1) % MEM_SIZE;
		val = (char)a->mem[*curs];
		*curs = (*curs + 1) % MEM_SIZE;

	}
	else if (type & 0x01)
	{
		val = a->mem[*curs];
		val = val % (REG_NUMBER + 1);
		*curs = (*curs + 1) % MEM_SIZE;
	}
	return (val);
}

/*static int		ft_check_carry(t_process *prc, int i)
{
	(void)i;
	if (ft_strequ(g_op_tab[i].name,"lfork") ||
			ft_strequ(g_op_tab[i].name, "add") ||
			ft_strequ(g_op_tab[i].name, "sub") ||
			ft_strequ(g_op_tab[i].name, "or") ||
			ft_strequ(g_op_tab[i].name, "xor") ||
			ft_strequ(g_op_tab[i].name, "and"))
	{
		prc->carry = 0;
		return (0);
	}
	if (ft_strequ(g_op_tab[i].name, "ld") ||
			ft_strequ(g_op_tab[i].name, "lld") ||
			ft_strequ(g_op_tab[i].name, "ldi") ||
			ft_strequ(g_op_tab[i].name, "lldi"))
	{
		prc->carry = 0;
		return (0);
	}
	return (1);
}*/

int		check_type(t_process *prc, t_a *a)
{
	int		i;
	int		j;
	char	arg_code;
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
	while (++j < g_op_tab[i].nb_arg)
	{
		tmp = arg_code >> 6;
		if (tmp == 1 && ((g_op_tab[i].type_arg[j] & 0x01) != 0x1))
			return (0);
		else if (tmp == 2 && ((g_op_tab[i].type_arg[j] & 0x02) != 0x02))
			return (0);
		else if (tmp == 3 && ((g_op_tab[i].type_arg[j] & 0x03) != 0x03))
			return (0);
		if (tmp == 0)
			return (0);
		arg_code = arg_code << 2;
	}
	if (arg_code != 0)
		return (0);
	return (1);
}
