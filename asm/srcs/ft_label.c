/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:21:37 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/09 22:47:47 by bcozic           ###   ########.fr       */
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
		ft_err_msg(NULL, line, "malloc fail", 1);
	label->addr = addr;
}

static void	check_label_name(t_a *a, int id_label, t_line *line)
{
	int	i;

	i = -1;
	while (a->label[++i].name)
		if (!ft_strcmp(a->label[i].name, a->label[id_label].name)
				&& i != id_label)
		{
			ft_warning_msg(a, line, "duplicate name label");
			return ;
		}
}

void		ft_label(t_a *data)
{
	t_line	*current;
	int		len_name;
	int		addr;
	int		i;

	if (!(data->label = (t_label *)malloc(sizeof(t_label) * data->nb_label)))
		ft_err_msg(data, NULL, "malloc fail", 1);
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
		{
			new_label(&data->label[++i], len_name, addr, current);
			check_label_name(data, i, current);
		}
		addr += current->size;
		current = current->next;
	}
	i = -1;
	data->prog_size = addr;
}
