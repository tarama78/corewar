/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 12:58:42 by atripard          #+#    #+#             */
/*   Updated: 2018/02/15 18:12:04 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

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

static int	check_dump(char *value, t_a *a, int ac, int *i)
{
	if (*i + 1 >= ac)
		return (0);
	if (!ft_is_uint(value, &(a->dump_cycle)))
		return (0);
	++(*i);
	return (1);
}

static int	check_n(char **av, t_a *a, int ac, int *i)
{
	if (*i + 2 >= ac || av[*i + 2][0] == '-')
		return (0);
	if (!ft_is_uint(av[*i + 1], &(a->n)))
		return (0);
	++(*i);
	return (1);
}

static int	check_option(int ac, char **av, t_a *a, int *i)
{
	if (ft_strequ("-dump", av[*i]))
	{
		if (!check_dump(av[*i + 1], a, ac, i))
			return (ERROR);
		return (SUCCESS);
	}
	else if (ft_strequ("-n", av[*i]))
	{
		if (!check_n(av, a, ac, i))
			return (ERROR);
		return (SUCCESS);
	}
	else if (ft_strequ("-v", av[*i]))
	{
		a->visu = 1;
		return (SUCCESS);
	}
	else
		return (ERROR);
}

int			parse_args(t_a *a, int ac, char **av)
{
	int player;
	int i;

	i = 0;
	a->n = 1;
	player = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (check_option(ac, av, a, &i) == ERROR)
				return (ERROR);
		}
		else if (!ft_add_file(a->file, av[i], &(a->n), player++))
			return (ERROR);
	}
	if (!(a->num_of_player = player))
		return (ERROR);
	return (SUCCESS);
}
