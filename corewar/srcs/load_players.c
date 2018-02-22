/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:08:32 by atripard          #+#    #+#             */
/*   Updated: 2018/02/15 14:18:46 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <load_players.h>

void	ft_intro(t_a *a)
{
	t_player	*tmp;
	int			i;

	tmp = a->player;
	i = -1;
	ft_putstr("Introducing contestants : \n");
	while (++i < a->num_of_player)
		ft_printf("* Player %d, weighing %d, \"%s\", (\"%s\") !\n",
				tmp[i].player_number_print, tmp[i].mem_size,
				tmp[i].name, tmp[i].comment);
}

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
		a->player[i].n = i;
		++i;
	}
	ft_intro(a);
	return (SUCCESS);
}
