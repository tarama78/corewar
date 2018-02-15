/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:16:45 by atripard          #+#    #+#             */
/*   Updated: 2018/02/15 14:34:23 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void		load_memory_player(uint8_t *mem,
								t_mem_info *info,
								t_player *player,
								int p_num)
{
	int	i;

	i = 0;
	while (i < player->mem_size)
	{
		mem[i] = player->mem[i];
		info[i].player = p_num;
		++i;
	}
}

void			load_memory(t_a *a)
{
	int			offset;
	int			player;

	player = 0;
	offset = MEM_SIZE / a->num_of_player;
	while (player < a->num_of_player)
	{
		load_memory_player(a->mem + (offset * player),
							a->mem_info + (offset * player),
							&(a->player[player]), player + 1);
		first_process(a, player, offset);
		++player;
	}
}
