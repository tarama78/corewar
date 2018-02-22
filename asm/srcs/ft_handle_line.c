/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:27:27 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/22 14:45:13 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | ft_handle_line.c                                         |
**   |     ft_free_arg(7 lines)                                 |
**   |     ft_check_arg(23 lines)                               |
**   |     ft_islabel(25 lines)                                 |
**   |     ft_check_double_label(12 lines)                      |
**   |     ft_handle_line(24 lines)                             |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <corewar.h>

static int	ft_free_arg(char **arg)
{
	int		i;

	i = -1;
	while (arg[++i])
		free(arg[i]);
	free(arg);
	return (ERROR);
}

static int	ft_check_arg(t_a *a, char *name, t_line *new_ln, char *ln)
{
	char	*tmp;
	int		i;
	char	**arg;
	t_op	op;

	if (!(tmp = ft_clean_char_custom(ln)))
		exit(EXIT_FAILURE);
	if ((tmp[0] == '\0' || name[0] == '\0') && ft_fruit(1, &tmp))
		return (ft_err_msg(a, new_ln, "invalid line", 0));
	if (!(arg = ft_strsplit(tmp, SEPARATOR_CHAR)))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < 17 && ft_strcmp(g_op_tab[i].name, name) != 0)
		;
	if (i == 17 && ft_fruit(1, &tmp) && ft_fruit_tab(1, &arg))
		return (ft_err_msg(a, new_ln, "invalid instruction name", 0));
	op = g_op_tab[i];
	if ((i = ft_get_size_op(a, &op, arg, new_ln)) == ERROR && ft_fruit(1, &tmp))
		return (ft_free_arg(arg));
	new_ln->size = 1 + op.octet_type_arg + i;
	ft_fruit_tab(1, &arg);
	ft_fruit(1, &tmp);
	return (SUCCESS);
}

static int	ft_islabel(t_line *ln, int ret)
{
	int		nb_label;
	int		i;

	if (ln == NULL)
		return (0);
	nb_label = 0;
	i = 0;
	while (ln->line[i])
	{
		while (ft_strchr(LABEL_CHARS, ln->line[++i]) && ln->line[i])
			;
		if (ln->line[i] == LABEL_CHAR)
			nb_label++;
		else
			break ;
		while (ln->line[++i] == ' ')
			;
		if (ln->line[i] == '\0')
			break ;
	}
	if (ln->line[i] == '\0' && nb_label == 1)
		return (1);
	if (ln->line[i] != '\0' && nb_label == 1 && ret == 1)
		return (0);
	return (nb_label);
}

static void	ft_check_double_label(t_a *a, t_line *new_ln)
{
	int		nb_lab;

	if ((nb_lab = ft_islabel(new_ln, 0)) == 0)
		return ;
	if (nb_lab >= 2)
	{
		ft_warning_msg(a, new_ln, "more than 1 label on a single line");
		return ;
	}
	if (ft_islabel((t_line*)ft_lst_get_last((t_lst*)a->line), 1) != 1)
		return ;
	ft_warning_msg(a, new_ln, "2 label in a row");
}

int			ft_handle_line(t_a *a, char *ln, int num_ln)
{
	char	*name;
	int		i;
	t_line	*new_ln;

	name = NULL;
	if (!(new_ln = malloc(sizeof(t_line))))
		exit(EXIT_FAILURE);
	new_ln->size = 0;
	new_ln->num_line = num_ln;
	if (!(new_ln->line = ft_get_clean_ln(a, ln, new_ln)) && ft_free(1, new_ln))
		return (ERROR);
	i = ft_start_i(a, ln, 1);
	if (i == 0 || ln[i] != '\0')
	{
		name = ft_get_name(ln + i, a, new_ln);
		i += ft_strlen(name);
		if (ft_check_arg(a, name, new_ln, ln + i) == ERROR &&
				ft_fruit(3, &name, &new_ln->line, &new_ln))
			return (ERROR);
	}
	ft_check_double_label(a, new_ln);
	ft_lst_add_end((t_lst**)&a->line, (t_lst*)new_ln);
	ft_fruit(1, &name);
	return (SUCCESS);
}
