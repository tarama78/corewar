/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:26:40 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/10 18:41:51 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*add_process(t_a *a, t_process *cpy)
{
	t_process *new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (0);
	//ERROR MALLOC
	ft_memcpy(new, cpy, sizeof(t_process));
	new->next = a->process;
	a->process = new;
	new->num_player = cpy->num_player;
	new->player_index = cpy->player_index;
	a->player[new->player_index].nb_process++;
	return (new);
}

t_process	*first_process(t_a *a, int player, int offset)
{
	t_process *new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (0);
	//ERROR MALLOC
	new->next = a->process;
	a->process = new;
	new->num_player = a->player[player].player_number_print;
	ft_bzero(new->reg, sizeof(new->reg));
	a->player[player].nb_process++;
	new->reg[1] = new->num_player;
	new->player_index = player;
	new->pc = offset * player;
	new->cycle_wait = -1;
	new->carry = 0;
	new->live = 0;
	return (new);
}
