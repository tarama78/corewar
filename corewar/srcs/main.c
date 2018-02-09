/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:34:46 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/09 15:34:59 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		ft_usage(int quit)
{
	ft_putstr("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	if (quit)
		exit(0);
}

int			ft_parse_dump(t_a *a, char *dump)
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

int			ft_add_file(t_champ_file *file, char *file_name, int *n, int player)
{
	int i;

	if (player >= MAX_PLAYERS)
		return (0);
	file[player].filename = file_name;	
	file[player].player_number_print = *n;
	i = 1;	
	*n = 0;
	while (i < player + 1 && *n == file[i].player_number_print)
	{
		++(*n);
		++i;
	}
	return (1);
}

int			ft_parse_arg(t_a *a, int ac, char **av)
{
	int i;
	int	player;
	int	n;

	i = 0;
	n = 0;
	player = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (ft_strequ("-dumpl", av[i]))
			{
				if ((i > 1) || (i + 1 >= ac) || !ft_parse_dump(a, av[++i]))
					return (ERROR);
			}
			else if (ft_strequ("-n", av[i]))
			{
				if ((i + 2 >= ac) || !ft_parse_n(av[++i], &n) || av[i + 1][0] == '-')
					return (ERROR);
			}
		}
		else
			if (!ft_add_file(a->file, av[i], &n, player++))
				return (ERROR);
	}
	a->num_of_player = player;
	return (1);
}

void		print_info(t_a *a)
{
	printf("dump: %d\n", a->dump_cycle);	
	printf("number of player: %d\n\n", a->num_of_player);	

	for (int i = 0; i < a->num_of_player; ++i)
	{
		printf("filename: %s\n", a->file[i].filename);
		printf("player_number_print: %d\n\n", a->file[i].player_number_print);
	}
}

int			main(int ac, char **av)
{
	t_a a;

	if (ac == 1)
		ft_usage(1);
	ft_memset(&a, 0, sizeof(a));
	if (ft_parse_arg(&a, ac, av) == ERROR)
		ft_usage(1);
	print_info(&a);
//	ft_load_player();
}
