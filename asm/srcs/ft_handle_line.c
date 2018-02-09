/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:27:27 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/09 12:04:26 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | ft_handle_line.c                                         |
**   |     ft_start_i(14 lines)                                 |
**   |     ft_get_name(12 lines)                                |
**   |     ft_get_type_dir_ind(24 lines)                        |
**   |     ft_get_type(25 lines)                                |
**   |     ft_get_size_op(17 lines)                             |
**   |     ft_check_arg(23 lines)                               |
**   |     ft_get_clean_ln(25 lines)                            |
**   |     ft_handle_line(23 lines)                             |
**   | MEUUUU too many functions                                |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <corewar.h>

static int	ft_start_i(t_a *a, char *ln, int label)
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

static char	*ft_get_name(char *ln)
{
	int		i;
	char	*ret;

	i = -1;
	while (ft_strchr(LABEL_CHARS, ln[++i]))
		;
	if (!(ret = malloc(sizeof(char) * (i + 1))))
		exit(EXIT_FAILURE);
	ret[i] = '\0';
	while (--i >= 0)
		ret[i] = ln[i];
	return (ret);
}

static int	ft_get_type_dir_ind(t_a *a, char *arg, t_line *new_ln)
{
	int		i;

	i = (arg[0] == DIRECT_CHAR) ? 1 : 0;
	if (arg[i] == LABEL_CHAR)
	{
		while (ft_strchr(LABEL_CHARS, arg[++i]) && arg[i])
			;
		if (arg[i] == '\0')
			return ((arg[0] == DIRECT_CHAR) ? T_DIR : T_IND);
		--a->nb_label;
		return (ft_err_msg(a, new_ln, "syntax error in label", 0));
	}
	else if (ft_isdigit(arg[i]) || arg[i] == '-')
	{
		i = (arg[i] == '-') ? i : i - 1;
		while (ft_isdigit(arg[++i]))
			;
		if (arg[i] == '\0')
			return ((arg[0] == DIRECT_CHAR) ? T_DIR : T_IND);
		--a->nb_label;
		return (ft_err_msg(a, new_ln, "invalid parameter", 0));
	}
	--a->nb_label;
	return (ft_err_msg(a, new_ln, "invalid parameter", 0));
}

static int	ft_get_type(t_a *a, char *arg, t_line *new_ln)
{
	int		i;

	if (arg[0] == 'r')
	{
		i = 0;
		while (ft_isdigit(arg[++i]))
			;
		if (arg[i] == '\0')
		{
			i = ft_atoi(arg + 1);
			if (i >= 1 && i <= REG_NUMBER)
				return (T_REG);
			else
			{
				--a->nb_label;
				return (ft_err_msg(a, new_ln, "reg number does not exist", 0));
			}
		}
		--a->nb_label;
		return (ft_err_msg(a, new_ln, "syntax error in reg", 0));
	}
	else
		return (ft_get_type_dir_ind(a, arg, new_ln));
	--a->nb_label;
	return (ft_err_msg(a, new_ln, "syntax error", 0));
}

static int	ft_get_size_op(t_a *a, t_op *op, char **arg, t_line *new_ln)
{
	int		sz;
	int		i;
	int		type;

	sz = 0;
	i = -1;
	while (++i < op->nb_arg)
	{
		if (arg[i] == NULL)
			return (ft_err_msg(a, new_ln, "not enough arguments", 0));
		if ((type = ft_get_type(a, arg[i], new_ln)) == ERROR)
			return (ERROR);
		if (!(op->type_arg[i] & type))
			return (ft_err_msg(a, new_ln, "invalid parameter type", 0));
		sz += ((type & T_REG) ? 1 : 0) + ((type & T_DIR) ? DIR_SIZE : 0)
			+ ((type & T_IND) ? IND_SIZE : 0);
		sz = (type & T_DIR && op->size_change == 1) ? sz - 2 : sz;
	}
	return (sz);
}

static char *ft_clean_char_custom(char *s)
{
	int		i;
	int		j;
	char	*ret;

	if (!(ret = ft_strtrim(s)))
		return (NULL);
	i = -1;
	while (ret[++i])
	{
		if (ret[i] == ',')
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
	}
	return (ret);
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
	{
		i = -1;
		while (arg[++i])
			free(arg[i]);
		ft_fruit(1, &arg);
		return (ERROR);
	}
	new_ln->size = 1 + op.octet_type_arg + i;
	i = -1;
	while (arg[++i])
		ft_fruit(1, arg + i);
	ft_fruit(2, &tmp, &arg);
	return (SUCCESS);
}

static char	*ft_get_clean_ln(t_a *a, char *ln, t_line *new_ln)
{
	int		i;
	char	*ret;
	char	*tmp;

	if (!(ret = ft_strnew(sizeof(char) * ft_strlen(ln))))
		exit(EXIT_FAILURE);
	i = ft_start_i(a, ln, 0);
	if (ln[i] != '\0')
	{
		while (ft_strchr(LABEL_CHARS, ln[++i]) && ln[i])
			;
		i++;
		if (ln[i - 1] == '\0')
		{
			new_ln->line = ln;
			ft_err_msg(a, new_ln, "invalid line", 0);
			ft_fruit(1, &ret);
			return (NULL);
		}
		if (!(tmp = ft_clean_char_custom(ln + i)))
			exit(EXIT_FAILURE);
		ft_memcpy(ret + i, tmp, ft_strlen(tmp));
		ft_fruit(1, &tmp);
	}
	ft_memcpy(ret, ln, i);
	return (ret);
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
