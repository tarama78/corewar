/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 10:18:21 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/06 15:21:09 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "corewar.h"

void	free_content(t_a *data, int mod)
{
	t_line	*tmp;
	int		i;

	tmp = data->line;
	while (tmp)
	{
		data->line = data->line->next;
		free(tmp->line);
		free(tmp);
		tmp = data->line;
	}
	i = -1;
	while (++i < data->nb_label)
	{
		free(data->label[i].name);
	}
	free(data->label);
	if (mod == ERROR)
		exit(0);
}
