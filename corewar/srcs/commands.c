/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:02:28 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/09 17:48:08 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
