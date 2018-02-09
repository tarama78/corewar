/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 10:18:21 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/09 10:25:58 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "corewar.h"

int		free_content(t_a *data, char *error)
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
	if (data->label)
	{
		i = -1;
		while (++i < data->nb_label)
			if (data->label[i].name)
				free(data->label[i].name);
		free(data->label);
	}
	if (error)
	{
		ft_dprintf(2, "%s\n", error);
		return (ERROR);
	}
	return (SUCCESS);
}
