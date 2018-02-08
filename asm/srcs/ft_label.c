/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:21:37 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/08 17:16:40 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <unistd.h>
#include "ft_printf.h"

static int	check_line(t_line *line)
{
	int	i;

	i = -1;
	while (line->line[++i])
	{
		if (line->line[i] == LABEL_CHAR)
			return (i);
		if (!ft_strchr(LABEL_CHARS, line->line[i]))
			return (0);
	}
	return (0);
}

static void	new_label(t_label *label, int len_name, int addr, t_line *line)
{
	if (!(label->name = ft_strndup(line->line, len_name)))
	{
		ft_err_msg(NULL, line, "malloc fail", 1);
		//FREE ALL
	}
	label->addr = addr;
}

void		ft_label(t_a *data)
{
	t_line	*current;
	int		len_name;
	int		addr;
	int		i;

	if (!(data->label = (t_label *)malloc(sizeof(t_label) * data->nb_label)))
	{
		ft_err_msg(data, NULL, "malloc fail", 1);
		//FREE ALL
	}
	i = -1;
	while (++i < data->nb_label)
		ft_bzero(&data->label[i], sizeof(t_label));
	addr = 0;
	i = -1;
	current = data->line;
	while (current)
	{
		len_name = 0;
		len_name = check_line(current);
		if (len_name)
			new_label(&data->label[++i], len_name, addr, current);
		addr += current->size;
		current = current->next;
	}
	i = -1;
	data->prog_size = addr;
}
