/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:26:17 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/12 11:47:51 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_command(void (**f)(t_process *, t_a *))
{
	f[0] = &ft_move;
	f[1] = &live;
	f[2] = &ld;
	f[3] = &st;
	f[4] = &add;
	f[5] = &sub;
	f[6] = &f_and;
	f[7] = &f_or;
	f[8] = &f_xor;
	f[9] = &ft_zjmp;
	f[10] = &ldi;
	f[11] = &sti;
	f[12] = &ft_fork;
	f[13] = &lld;
	f[14] = &lldi;
	f[15] = &lfork;
	f[16] = &ft_aff;
}

void	ft_move(t_process *prc, t_a *a)
{
	char	i;

	i = 0;
	a->mem_info[prc->pc].process = 0;
	check_cycle(prc, a);
	check_cycle(prc, a);
	while (++i <= a->num_of_player)
		if (a->player[i - 1].player_number_print == prc->num_player)
			break ;
	prc->pc = (prc->pc + 1) % MEM_SIZE;
	a->mem_info[prc->pc].process = 1;
	a->mem_info[prc->pc].player_process = i;
}
