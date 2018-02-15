/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:34:46 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/15 17:12:13 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		ft_usage(int quit, char *name)
{
	ft_printf("Usage: %s [-v -dump N] <[-n N] champion1.cor> <...>\n"
			"\t-v %8t: visual mode\n"
			"\t-dump N %3t: Dumps memory after N cycles then exits\n"
			"\t-n N %6t: players number\n", name);
	if (quit)
		exit(EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	void	(*f[NB_COMM + 1])(t_process *prc, t_a *a);
	t_a		a;

	if (ac == 1)
		ft_usage(1, av[0]);
	ft_memset(&a, 0, sizeof(a));
	a.dump_cycle = -1;
	if (parse_args(&a, ac, av) == ERROR)
		ft_usage(1, av[0]);
	if (load_players(&a) == ERROR)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	load_memory(&a);
	a.cycle_to_die = CYCLE_TO_DIE;
	a.speed = SPEED;
	if (a.visu)
		ft_init(&a);
	init_command(f);
	game_loop(&a, f);
	winner(&a);
	if (a.visu)
		ft_free_nc(&a);
}
