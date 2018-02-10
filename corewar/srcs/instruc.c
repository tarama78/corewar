/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:30:49 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/10 15:19:26 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

live
fork
lfork

void	ft_aff(t_process *prc, t_a *a)
{
	int		value;
	char	*octet;
	int		i;

	i = 4;
	if (!(check_cycle(prc, a)))
			return ;
	value = prc->reg[a->mem[(prc->pc + 2 % MEM_SIZE)]];
	octet = (char*)&value;
	while (--i >= 0)
		ft_putchar_fd(octet[i], STDOUT_FILENO);
	prc->pc = (prc->pc + 3) % MEM_SIZE;
}

void	ft_zjump(t_process *prc, t_a *a)
{
	int		addr;
	int		curs;

	curs = (prc->pc + 1) % MEM_SIZE;
	if (!(check_cycle(prc, a)))
			return ;
	addr = rec_memory(2, &curs, a, 0);
	addr = addr % IDX_MOD;
	if (prc->carry == 1)
	{
		prc->pc = (prc->pc + addr) % MEM_SIZE
	}
	else
		prc->pc = (curs + 1) % MEM_SIZE;
}

void	live(t_process *prc, t_a *a)
{
	int		player_nb;
	int		curs;
	int		i;

	curs = (prc->pc + 1) % MEM_SIZE;
	player_nb = rec_memory(3, &curs, a, 0);
	prc->live = 1;
	i = -1;
	while (a->player[++i] && i < MAX_PLAYER)
		if (a->player[i]->player_number_print == player_nb)
		{
			a->player[i]->last_live_cycle = (int)a->cycle;
			a->player[i]->nb_live_total++;
			a->player[i]->nb_live_current++;
		}
	prc->pc = (curs + 1) % MEM_SIZE;
}

void	ft_fork(t_process *prc, t_a *a)
{
	int			addr;
	int			curs;
	t_process	new_prc;

	curs = (prc->pc + 1) % MEM_SIZE;
	if (!(check_cycle(prc, a)))
			return ;
	addr = rec_memory(2, &curs, a, 0);
	addr = addr % IDX_MOD;
	new_prc = add_process(a, prc);
	new_prc->pc = (prc->pc + addr) % MEM_SIZE
	prc->pc = (curs + 1) % MEM_SIZE;
}

void	lfork(t_process *prc, t_a *a)
{
	int			addr;
	int			curs;
	t_process	new_prc;

	curs = (prc->pc + 1) % MEM_SIZE;
	if (!(check_cycle(prc, a)))
			return ;
	addr = rec_memory(2, &curs, a, 0);
	new_prc = add_process(a, prc);
	new_prc->pc = (prc->pc + addr) % MEM_SIZE
	prc->pc = (curs + 1) % MEM_SIZE;
}
