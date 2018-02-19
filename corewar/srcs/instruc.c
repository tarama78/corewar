/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:30:49 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/19 20:10:54 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_aff(t_process *prc, t_a *a)
{
	int		value;
	int		reg;
	char	*octet;
	int		i;

	i = 4;
	if (!(check_cycle(prc)))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 2) % MEM_SIZE;
	reg = rec_memory(1, prc, a, 0);
	if (reg != -1)
	{
		value = prc->reg[reg];
		octet = (char*)&value;
		while (--i >= 0)
			ft_putchar_fd(octet[i], STDOUT_FILENO);
	}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	ft_zjmp(t_process *prc, t_a *a)
{
	int		addr;

	if (!(check_cycle(prc)))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 1) % MEM_SIZE;
	addr = rec_memory(3, prc, a, IND_SIZE);
	addr = addr % IDX_MOD;
	addr = (prc->tmp_pc + addr) % MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	if (prc->carry == 1)
	{
		ft_curseur(prc, prc->tmp_pc, addr, a);
		prc->pc = addr;
		if (prc->pc < 0)
			prc->pc += MEM_SIZE;
	}
	else
		ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	live(t_process *prc, t_a *a)
{
	int		player_nb;
	int		i;

	if (!(check_cycle(prc)))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 1) % MEM_SIZE;
	player_nb = rec_memory(2, prc, a, 4);
	prc->live = 1;
	i = -1;
	while (++i < a->num_of_player)
		if (a->player[i].player_number_print == player_nb)
		{
			a->player[i].last_live_cycle = (int)a->cycle;
			a->player[i].nb_live_total++;
			a->player[i].nb_live_current++;
		}
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	ft_fork(t_process *prc, t_a *a)
{
	int			addr;
	t_process	*new_prc;

	if (!(check_cycle(prc)))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 1) % MEM_SIZE;
	addr = rec_memory(3, prc, a, IND_SIZE);
	addr = addr % IDX_MOD;
	new_prc = add_process(a, prc);
	new_prc->pc = (prc->tmp_pc + addr) % MEM_SIZE;
	if (new_prc->pc < 0)
		new_prc->pc += MEM_SIZE;
	ft_curseur(prc, prc->tmp_pc, new_prc->pc, a);
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}

void	lfork(t_process *prc, t_a *a)
{
	int			addr;
	t_process	*new_prc;

	if (!(check_cycle(prc)))
		return ;
	prc->tmp_pc = prc->pc;
	prc->pc = (prc->pc + 1) % MEM_SIZE;
	addr = rec_memory(3, prc, a, IND_SIZE);
	new_prc = add_process(a, prc);
	new_prc->pc = (prc->tmp_pc + addr) % MEM_SIZE;
	if (new_prc->pc < 0)
		new_prc->pc += MEM_SIZE;
	ft_curseur(prc, prc->tmp_pc, new_prc->pc, a);
	ft_curseur(prc, prc->tmp_pc, prc->pc, a);
}
