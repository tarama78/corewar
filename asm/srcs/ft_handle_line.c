/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:42:32 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/05 17:00:54 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | ft_handle_line.c                                         |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <corewar.h>

void		ft_handle_line(t_a *a, char *ln, int num_ln)
{
	
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int			main(int ac, char **av)
{
	int		i;
	t_a		a;

	(void)ac;
	(void)av;
	(void)i;
	ft_handle_line(&a, "add r1,   %:label     ,   r15", 12);
	return (0);
}
