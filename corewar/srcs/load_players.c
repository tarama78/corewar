/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:08:32 by atripard          #+#    #+#             */
/*   Updated: 2018/02/12 13:08:33 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <load_players.h>

int		load_players(t_a *a)
{
	int	fd;
	int	i;

	i = 0;
	while (i < a->num_of_player)
	{
		if ((fd = open(a->file[i].filename, O_RDONLY)) < 0)
			return (ERROR);
		if (check_magic_number(fd) == ERROR)
			return (ERROR);
		if (load_name(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		if (check_prog_size(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		if (load_comment(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		if (load_prog(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		a->player[i].player_number_print = a->file[i].player_number_print;
		++i;
	}
	return (SUCCESS);
}
