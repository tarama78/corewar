/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:39:42 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/22 15:05:04 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	error_malloc(t_a *a)
{
	free_process(a);
	if (a->nc.win_mem)
		ft_free_nc(a);
	exit(EXIT_FAILURE);
}

void	error_init_src(t_a *a)
{
	ft_free_nc(a);
	ft_errprintf("\x1B[31m\e[1mERROR:\x1B[0m\n\tExtend your terminal\n");
	exit(EXIT_FAILURE);
}
