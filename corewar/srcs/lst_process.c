/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:26:40 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/10 13:33:23 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*add_process(t_a *a, t_process *cpy)
{
	t_process *new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (0);
	//ERROR MALLOC
	ft_memcpy(new, cpy, sizeof(cpy));
	new->next = a->process;
	a_process = new;
	new->num_player = cpy->num_player;
	return (new);
}
