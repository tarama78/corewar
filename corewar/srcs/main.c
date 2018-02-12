/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:34:46 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/10 21:17:11 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		ft_usage(int quit)
{
	ft_putstr("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	if (quit)
		exit(0);
}

int			main(int ac, char **av)
{
	t_a a;
	void	(*f[NB_COMM + 1])(t_process *prc, t_a *a);

	if (ac == 1)
		ft_usage(1);
	ft_memset(&a, 0, sizeof(a));
	if (parse_args(&a, ac, av) == ERROR)
		ft_usage(1);
	if (load_players(&a) == ERROR)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	load_memory(&a);
	a.cycle_to_die = CYCLE_TO_DIE;
	ft_init(&a);//ncurses
//	ft_print(&a);
//	while (getch() != 27)
//	{
//		ft_print(&a);
//		usleep(50);
//	}
	init_command(f);
	game_loop(&a, f);
	ft_free_nc(&a);//ncurses
}
