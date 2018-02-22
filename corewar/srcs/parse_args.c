/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <atripard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 12:58:42 by atripard          #+#    #+#             */
/*   Updated: 2018/02/22 21:20:31 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int	ft_add_file(t_champ_file *file, char *file_name, t_a *a, int player)
{
	if (player >= MAX_PLAYERS)
		return (0);
	file[player].filename = file_name;
	if (a->n)
	{
		file[player].player_number_print = a->n_val;
		file[player].n = 1;
		a->n = 0;
	}
	return (1);
}

static int	check_dump(char *value, t_a *a, int ac, int *i)
{
	if (*i + 1 >= ac)
		return (ERROR);
	if (!ft_is_uint(value, &(a->dump_cycle)))
		return (ERROR);
	++(*i);
	return (SUCCESS);
}

static int	check_n(char **av, t_a *a, int ac, int *i)
{
	if (*i + 2 >= ac || av[*i + 2][0] == '-')
		return (ERROR);
	if (!ft_is_int(av[*i + 1], &(a->n_val)))
		return (ERROR);
	a->n = 1;
	++(*i);
	return (SUCCESS);
}

static int	check_option(int ac, char **av, t_a *a, int *i)
{
	if (ft_strequ("-dump", av[*i]))
		return (check_dump(av[*i + 1], a, ac, i));
	else if (ft_strequ("-n", av[*i]))
		return (check_n(av, a, ac, i));
	else if (ft_strequ("-v", av[*i]))
		a->visu = 1;
	else if (ft_strequ("-live", av[*i]))
		a->live_option = 1;
	else
		return (ERROR);
	return (SUCCESS);
}

int			parse_args(t_a *a, int ac, char **av)
{
	int player;
	int i;

	i = 0;
	player = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (check_option(ac, av, a, &i) == ERROR)
				return (ERROR);
		}
		else if (!ft_add_file(a->file, av[i], a, player++))
			return (ERROR);
	}
	if (!(a->num_of_player = player))
		return (ERROR);
	return (SUCCESS);
}
