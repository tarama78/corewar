/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:27:27 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/09 16:05:28 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | ft_handle_line.c                                         |
**   |     ft_start_i(14 lines)                                 |
**   |     ft_clean_char_custom(24 lines)                       |
**   |     ft_free_arg(7 lines)                                 |
**   |     ft_check_arg(23 lines)                               |
**   |     ft_handle_line(23 lines)                             |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <corewar.h>

int			ft_start_i(t_a *a, char *ln, int label)
{
	int		i;

	i = -1;
	while (ft_strchr(LABEL_CHARS, ln[++i]) && ln[i])
		;
	if (ln[i] == LABEL_CHAR)
	{
		while (ln[++i] == ' ' || ln[i] == '\t')
			;
		if (label)
			a->nb_label++;
		return (i + ft_start_i(a, ln + i, label));
	}
	return (0);
}

char		*ft_clean_char_custom(char *s)
{
	int		i;
	int		j;
	char	*ret;

	if (!(ret = ft_strtrim(s)))
		return (NULL);
	i = -1;
	while (ret[++i])
		if (ret[i] == SEPARATOR_CHAR)
		{
			j = 0;
			while (ret[i - j - 1] == ' ')
				++j;
			if (j > 0)
				ft_memmove(ret + i - j, ret + i, ft_strlen(ret + i) + 1);
			i -= j;
			j = 0;
			while (ret[i + j + 1] == ' ')
				++j;
			if (j > 0)
				ft_memmove(ret + i + 1, ret + i + j + 1,
						ft_strlen(ret + i + j + 1) + 1);
		}
	return (ret);
}

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
	while (ft_strcmp(g_op_tab[++i].name, name) != 0)
		;
	op = g_op_tab[i];
	if ((i = ft_get_size_op(a, &op, arg, new_ln)) == ERROR && ft_fruit(1, &tmp))
		return (ft_free_arg(arg));
	new_ln->size = 1 + op.octet_type_arg + i;
	i = -1;
	while (arg[++i])
		ft_fruit(1, arg + i);
	ft_fruit(2, &tmp, &arg);
	return (SUCCESS);
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
		name = ft_get_name(ln + i);
		i += ft_strlen(name);
		if (ft_check_arg(a, name, new_ln, ln + i) == ERROR &&
				ft_fruit(3, &name, &new_ln->line, &new_ln))
			return (ERROR);
	}
	ft_lst_add_end((t_lst**)&a->line, (t_lst*)new_ln);
	ft_fruit(1, &name);
	return (SUCCESS);
}
