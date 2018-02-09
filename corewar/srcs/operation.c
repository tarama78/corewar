/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:22:41 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/09 17:43:58 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	add(t_process *prc, t_a *a)
{
	if (!check_cycle(10, prc))
		return ;
	if (a->mem[prc->pc + 1] & 0x54 == 0)
	{
		prc->reg[a->mem[prc->pc + 4]] =
			prc->reg[a->mem[prc->pc + 2]]
			+ prc->reg[a->mem[prc->pc + 3]];
	}
	prc->pc += 5;
	prc->carry = (prc->carry + 1) % 2;
}

void	sub(t_process *prc, t_a *a)
{
	if (!check_cycle(10, prc))
		return ;
	if (a->mem[prc->pc + 1] & 0x54 == 0)
	{
		prc->reg[a->mem[prc->pc + 4]] =
			prc->reg[a->mem[prc->pc + 2]]
			- prc->reg[a->mem[prc->pc + 3]];
	}
	prc->pc += 5;
	prc->carry = (prc->carry + 1) % 2;
}

void	or(t_process *prc, t_a *a)
{
	int	v1;
	int	v2;
	int	curs;

	curs = prc->pc + 2;
	if (a->mem[prc->pc + 1] & 0x0F != 0x04)
	{
		prc->pc += 5;
		return ;
	}
	if (!check_cycle(6, prc))
		return ;
	v1 = rec_memory(a->mem[prc->pc + 1] >> 4, &curs, a);
	v2 = rec_memory(a->mem[prc->pc + 1] >> 6, &curs, a);
	prc->reg[a->mem[curs]] = v1 + v2;
	prc->pc += 5;
	prc->carry = (prc->carry + 1) % 2;
}
