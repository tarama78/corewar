/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:40:10 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/15 14:24:33 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	winner(t_a *a)
{
	if (a->winner)
		ft_printf("le joueur %d(%s) a gagne\n",
			a->winner->player_number_print,
			a->winner->name);
}
