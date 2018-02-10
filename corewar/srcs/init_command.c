/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:26:17 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/10 14:41:08 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	init_command(void *(**f)(t_process *, t_a *))
{
	f[0] = &move;
	f[1] = &live;
	f[2] = &ld;
	f[3] = &st;
	f[4] = &add;
	f[5] = &sub;
	f[6] = &and;
	f[7] = &f_or;
	f[8] = &f_xor;
	f[9] = &ft_zjmp;
	f[10] = &ldi;
	f[11] = &sti;
	f[12] = &fork;
	f[13] = &lld;
	f[14] = &lldi;
	f[15] = &lfork;
	f[16] = &aff;
}

void	move(t_process *prc, t_a *a)
{
	prc->pc = (prc->pc + 1) % MEM_SIZE;
}
