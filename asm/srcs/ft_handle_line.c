/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 13:28:19 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/06 15:10:55 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | ft_handle_line.c                                         |
**   |     ft_err_msg(4 lines)                                  |
**   |     ft_start_i(13 lines)                                 |
**   |     ft_get_name(12 lines)                                |
**   |     ft_get_type(41 lines)                                |
**   |         MEUUUU too many lines                            |
**   |     ft_get_size_op(16 lines)                             |
**   |     ft_check_arg(19 lines)                               |
**   |     ft_handle_line(23 lines)                             |
**   |     main(14 lines)                                       |
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

static void	ft_err_msg(t_a *a, t_line *new_ln, char *txt)
{
	ft_errprintf("{red}ERROR:{eoc} {yellow}%s.s\n{eoc}"
			"\t{yellow}{bold}line: %d{eoc} ->{bold} %s{eoc}\n"
			"\t%s\n", "A->NOMDUFICHIER", new_ln->num_line, txt, new_ln->line);
	exit(EXIT_FAILURE);
}

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
		return (i);
	}
	return (0);
}

static char	*ft_get_name(char *ln)
{
	int		i;
	char	*ret;

	i = -1;
	while (ft_isalpha(ln[++i]))
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
				ft_err_msg(a, new_ln, "reg number does not exist");
		}
		ft_err_msg(a, new_ln, "syntax error in reg");
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
			ft_err_msg(a, new_ln, "syntax error in label");
		}
		else if (ft_isdigit(arg[i]))
		{
			i--;
			while (ft_isdigit(arg[++i]))
				;
			if (arg[i] == '\0')
				return ((arg[0] == DIRECT_CHAR) ? T_DIR : T_IND);
			ft_err_msg(a, new_ln, "invalid parameter");
		}
		ft_err_msg(a, new_ln, "invalid parameter");
	}
	ft_err_msg(a, new_ln, "syntax error");
	return (0);
}

static int	ft_get_size_op(t_a *a, char *ln, t_op *op, char **arg, t_line *new_ln)
{
	int		sz;
	int		i;
	int		type;

	sz = 0;
	i = -1;
	while (++i < op->nb_arg)
	{
//		ft_printf("\t%d -> %s (%d)\n", op->type_arg[i], arg[i], ft_get_type(a, arg[i], num_ln));
		type = ft_get_type(a, arg[i], new_ln);
		if (!(op->type_arg[i] & type))
			ft_err_msg(a, new_ln, "invalid parameter type");
		sz += ((type & T_REG) ? 1 : 0) + ((type & T_DIR) ? DIR_SIZE : 0)
			+ (( type & IND_SIZE) ? 2 : 0);
	}
	return (sz);
}

static void	ft_check_arg(t_a *a, char *name, t_line *new_ln, char *ln)
{
	char	*tmp;
	int		i;
	char	**arg;
	t_op	op;

	if (!(tmp = ft_clean_char(ln, ' ')))
		exit(EXIT_FAILURE);
	if (!(arg = ft_strsplit(tmp, SEPARATOR_CHAR)))
		exit(EXIT_FAILURE);
	i = -1;
	while (ft_strcmp(op_tab[++i].name, name) != 0)
		;
	op = op_tab[i];
	new_ln->size = 1 + op.octet_type_arg +
		ft_get_size_op(a, ln, &op, arg, new_ln);
	i = -1;
	while (arg[++i])
		ft_fruit(1, arg[i]);
	ft_fruit(2, tmp, arg);
}

int			ft_handle_line(t_a *a, char *ln, int num_ln)
{
	char	*name;
	int		i;
	t_line	*new_ln;

//	ft_printf("{yellow}%s: %s({bold}\"%s\"{eoc}{yellow}){eoc}\n", __FILE__, __func__, ln);

	name = NULL;
	if (!(new_ln = malloc(sizeof(t_line))))
		exit(EXIT_FAILURE);
	new_ln->line = ft_strdup(ln);
	new_ln->size = 0;
	new_ln->num_line = num_ln;
	i = ft_start_i(a, ln);
	if (i == 0 || ln[i] != '\0')
	{
		name = ft_get_name(ln + i);
		i += ft_strlen(name);
		ft_check_arg(a, name, new_ln, ln + i);
	}
	ft_lst_add_end((t_lst**)&a->line, (t_lst*)new_ln);
	ft_fruit(1, name);

//	ft_printf("\tsize: %d\n", new_ln->size);
	return (SUCCESS);
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int			main(int ac, char **av)
{
	int		i;
	t_a		a;

	(void)ac;
	(void)av;
	(void)i;
	a.line = NULL;
	a.nb_label = 0;
	ft_handle_line(&a, "add r1, r12 ,r15", 1);
	ft_handle_line(&a, "label: zjmp  %12", 2);
	ft_handle_line(&a, "ldi :seksek, %15648, r7", 3);
	ft_handle_line(&a, "autre_label:", 4);
//	ft_handle_line(&a, "label3:label5: label120: aff r16", 5);
	ft_label(&a);
	for (int i = 0; i < a.nb_label; i++)
	{
		ft_printf("%d %s\n", a.label[i].addr, a.label[i].name);
	}
	free_content(&a, 0);
	return (0);
}
