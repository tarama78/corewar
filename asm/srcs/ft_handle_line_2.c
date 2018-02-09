/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_line_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:31:22 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/09 12:34:45 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | ft_handle_line_2.c                                       |
**   |     ft_get_type_dir_ind(24 lines)                        |
**   |     ft_get_type(25 lines)                                |
**   |     ft_get_size_op(19 lines)                             |
**   |     ft_get_clean_ln(25 lines)                            |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <corewar.h>

char		*ft_get_name(char *ln)
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

int			ft_get_size_op(t_a *a, t_op *op, char **arg, t_line *new_ln)
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

char		*ft_get_clean_ln(t_a *a, char *ln, t_line *new_ln)
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
	return (ft_memcpy(ret, ln, i));
}
