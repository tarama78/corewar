/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 12:58:42 by atripard          #+#    #+#             */
/*   Updated: 2018/02/12 14:23:42 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int	ft_parse_dump(t_a *a, char *dump)
{
	int	num;

	if (!ft_is_uint(dump, &num))
		return (0);
	a->dump_cycle = num;
	return (1);
}

int			ft_parse_n(char *s, int *n)
{
	if (!ft_is_uint(s, n))
		return (0);
	return (1);
}

static int	ft_add_file(t_champ_file *file, char *file_name, int *n, int player)
{
	int next_number;
	int i;

	if (player >= MAX_PLAYERS)
		return (0);
	file[player].filename = file_name;
	file[player].player_number_print = *n;
	i = 0;
	next_number = 1;
	while (i < player + 1)
	{
		if (next_number == file[i].player_number_print)
		{
			++next_number;
			i = -1;
		}
		++i;
	}
	*n = next_number;
	return (1);
}

int			parse_args(t_a *a, int ac, char **av)
{
	int i;
	int	player;
	int	n;

	i = 0;
	n = 1;
	player = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (ft_strequ("-dumpl", av[i]))
			{
				if (((i > 1) || (i + 1 >= ac) || !ft_parse_dump(a, av[++i])))
					return (ERROR);
			}
			else if (ft_strequ("-n", av[i]))
			{
				if (((i + 2 >= ac) || !ft_parse_n(av[++i], &n) || (av[i + 1][0] == '-')))
					return (ERROR);
			}
			else if (ft_strequ("-v", av[i]))
				a->visu = 1;
			else
				return (ERROR);
		}
		else if (!ft_add_file(a->file, av[i], &n, player++))
			return (ERROR);
	}
	a->num_of_player = player;
	return (SUCCESS);
}
