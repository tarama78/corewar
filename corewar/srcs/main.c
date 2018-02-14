/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:34:46 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/13 12:11:52 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		ft_usage(int quit)
{
	ft_putstr("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	if (quit)
		exit(EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	void	(*f[NB_COMM + 1])(t_process *prc, t_a *a);
	t_a		a;

	if (ac == 1)
		ft_usage(1);
	ft_memset(&a, 0, sizeof(a));
	a.dump_cycle = -1;
	if (parse_args(&a, ac, av) == ERROR)
		ft_usage(1);
	if (load_players(&a) == ERROR)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	if (load_memory(&a) == ERROR)
	{
		// Error malloc first process
		// free
		ft_printf("ERROR\n");
		return (0);
	}
	a.cycle_to_die = CYCLE_TO_DIE;
	a.speed = SPEED;
	if (a.visu)
		ft_init(&a);//ncurses
//	ft_print(&a);
//	while (getch() != 27)
//	{
//		ft_print(&a);
//		usleep(50);
//	}
	init_command(f);
	game_loop(&a, f);
	if (a.visu)
		ft_free_nc(&a);//ncurses
}
