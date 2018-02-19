/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_winner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 14:12:11 by atripard          #+#    #+#             */
/*   Updated: 2018/02/19 14:12:30 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		ft_print_winner(t_a *a, int *i)
{
	char 	*name;
	int		num;

	++(*i);
	name = a->winner->name;
	num = a->winner->player_number_print;
	mvwprintw(a->nc.win_info, ++(*i), 4, "Player %d (", num);
	wattron(a->nc.win_info, a->nc.color.player[a->winner->n + 1] | A_BOLD);
	mvwprintw(a->nc.win_info, *i, 15, "%s", name);
	wattron(a->nc.win_info, a->nc.color.text);
	mvwprintw(a->nc.win_info, *i, 15 + ft_strlen(name), ") won");
}
