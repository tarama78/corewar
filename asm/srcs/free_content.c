/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 10:18:21 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/06 11:52:59 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "corewar.h"

void	free_content(t_a *data, int mod)
{
	ft_fruit(2, data->line, data->label);
	if (mod == ERROR)
		exit(0);
}
