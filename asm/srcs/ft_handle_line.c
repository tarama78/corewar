/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 13:28:19 by tnicolas          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | ft_handle_line.c                                         |
**   |     ft_start_i(13 lines)                                 |
**   |     ft_get_name(12 lines)                                |
**   |     ft_get_type(40 lines)                                |
**   |         MEUUUU too many lines                            |
**   |     ft_get_size_op(17 lines)                             |
**   |     ft_check_arg(23 lines)                               |
**   |     ft_get_clean_ln(19 lines)                            |
**   |     ft_handle_line(24 lines)                             |
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

static int	ft_start_i(t_a *a, char *ln)
{
	int		i;

	i = -1;
	while (ft_strchr(LABEL_CHARS, ln[++i]) && ln[i])
		;
	if (ln[i] == LABEL_CHAR)
	{
		while (ln[++i] == ' ' || ln[i] == '\t')
			;
		a->nb_label++;
		return (i + ft_start_i(a, ln + i));
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
				return (ft_err_msg(a, new_ln, "reg number does not exist"));
		}
		return (ft_err_msg(a, new_ln, "syntax error in reg"));
	}
	else
	{
		i = (arg[0] == DIRECT_CHAR) ? 1 : 0;
		if (arg[i] == LABEL_CHAR)
		{
			while (ft_strchr(LABEL_CHARS, arg[++i]) && arg[i])
				;
			if (arg[i] == '\0')
				return ((arg[0] == DIRECT_CHAR) ? T_DIR : T_IND);
			return (ft_err_msg(a, new_ln, "syntax error in label"));
		}
		else if (ft_isdigit(arg[i]) || arg[i] == '-')
		{
			i = (arg[i] == '-') ? i : i - 1;
			while (ft_isdigit(arg[++i]))
				;
			if (arg[i] == '\0')
				return ((arg[0] == DIRECT_CHAR) ? T_DIR : T_IND);
			return (ft_err_msg(a, new_ln, "invalid parameter"));
		}
		return (ft_err_msg(a, new_ln, "invalid parameter"));
	}
	return (ft_err_msg(a, new_ln, "syntax error"));
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
//		ft_printf("\t%d -> %s (%d)\n", op->type_arg[i], arg[i], ft_get_type(a, arg[i], num_ln));//dd
		if ((type = ft_get_type(a, arg[i], new_ln)) == ERROR)
			return (ERROR);
		if (!(op->type_arg[i] & type))
			return (ft_err_msg(a, new_ln, "invalid parameter type"));
		sz += ((type & T_REG) ? 1 : 0) + ((type & T_DIR) ? DIR_SIZE : 0)
			+ (( type & IND_SIZE) ? 2 : 0);
	}
	return (sz);
}

static int	ft_check_arg(t_a *a, char *name, t_line *new_ln, char *ln)
{
	char	*tmp;
	int		i;
	char	**arg;
	t_op	op;

	if (!(tmp = ft_clean_char(ln, ' ')))
		exit(EXIT_FAILURE);
	if ((tmp[0] == '\0' || name[0] == '\0') && ft_fruit(1, tmp))
		return (ft_err_msg(a, new_ln, "invalid line"));
	if (!(arg = ft_strsplit(tmp, SEPARATOR_CHAR)))
		exit(EXIT_FAILURE);
	i = -1;
	while (ft_strcmp(op_tab[++i].name, name) != 0)
		;
	op = op_tab[i];
	if ((i = ft_get_size_op(a, &op, arg, new_ln)) == ERROR)
		return (ERROR);
	new_ln->size = 1 + op.octet_type_arg + i;
	i = -1;
	while (arg[++i])
		ft_fruit(1, arg[i]);
	ft_fruit(2, tmp, arg);
	return (SUCCESS);
}

static char	*ft_get_clean_ln(t_a *a, char *ln, t_line *new_ln)
{
	int		i;
	char	*ret;
	char	*tmp;

	if (!(ret = ft_strnew(sizeof(char) * ft_strlen(ln))))
		exit(EXIT_FAILURE);
	i = ft_start_i(a, ln);
	if (ln[i] != '\0')
	{
		while (ft_strchr(LABEL_CHARS, ln[++i]) && ln[i])
			;
		i++;
		if (ln[i - 1] == '\0')
		{
			new_ln->line = ln;
			ft_err_msg(a, new_ln, "invalid line");
			return (NULL);
		}
		if (!(tmp = ft_clean_char(ln + i, ' ')))
			exit(EXIT_FAILURE);
		ft_memcpy(ret + i, tmp, ft_strlen(tmp));
		ft_fruit(1, tmp);
	}
	ft_memcpy(ret, ln, i);
	return (ret);
}

int			ft_handle_line(t_a *a, char *ln, int num_ln)
{
	char	*name;
	int		i;
	t_line	*new_ln;

//	ft_printf("{yellow}%s: %s({bold}\"%s\"{eoc}{yellow}){eoc}\n", __FILE__, __func__, ln);//dd
	name = NULL;
	if (!(new_ln = malloc(sizeof(t_line))))
		exit(EXIT_FAILURE);
	new_ln->size = 0;
	new_ln->num_line = num_ln;
	if (!(new_ln->line = ft_get_clean_ln(a, ln, new_ln)))
		return (ERROR);
	i = ft_start_i(a, ln);
	if (i == 0 || ln[i] != '\0')
	{
		name = ft_get_name(ln + i);
		i += ft_strlen(name);
		if (ft_check_arg(a, name, new_ln, ln + i) == ERROR)
			return (ERROR);
	}
	ft_lst_add_end((t_lst**)&a->line, (t_lst*)new_ln);
	ft_fruit(1, name);
	ft_label(a);
	return (SUCCESS);
}
