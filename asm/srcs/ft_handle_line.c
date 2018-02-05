/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:42:32 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/05 18:26:35 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | ft_handle_line.c                                         |
**   |     ft_start_i(12 lines)                                 |
**   |     ft_get_name(12 lines)                                |
**   |     ft_check_arg(7 lines)                                |
**   |     ft_handle_line(16 lines)                             |
**   |     main(10 lines)                                       |
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
	while (ft_isalpha(ln[++i]))
		;
	if (ln[i] == ':')
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

static void	ft_check_arg(char *name, t_line *new_ln, char *ln)
{
	char	*tmp;
	int		i;
	char	**arg;
	t_op	op;

	if (!(tmp = ft_clean_char(ln, ' ')))
		exit(EXIT_FAILURE);
	if (!(arg = ft_strsplit(tmp, ',')))
		exit(EXIT_FAILURE);
	i = -1;
	while (ft_strcmp(op_tab[++i].name, name) != 0)
		;
	op = op_tab[i];
	ft_printf(">>> %s\n", op.name);
	i = -1;
	while (arg[++i])
		ft_fruit(1, arg[i]);
	ft_fruit(2, tmp, arg);
}

void		ft_handle_line(t_a *a, char *ln, int num_ln)
{
	char	*name;
	int		i;
	t_line	*new_ln;

	ft_printf("{yellow}%s: %s({bold}\"%s\"{eoc}{yellow}){eoc}\n", __FILE__, __func__, ln);

	if (!(new_ln = malloc(sizeof(t_line))))
		exit(EXIT_FAILURE);
	new_ln->line = ft_strdup(ln);
	i = ft_start_i(a, ln);
	name = ft_get_name(ln + i);
	i += ft_strlen(name);
	ft_check_arg(name, new_ln, ln + i);
	ft_lst_add_end((t_lst**)&a->line, (t_lst*)new_ln);
//	ft_printf("\t(name |%s|) (i %d) (reste |%s|)\n", name, i, ft_clean_char(ln + i, ' '));
	ft_fruit(1, name);
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
	ft_handle_line(&a, "add r1,   %:label ,  r15", 12);
	ft_handle_line(&a, "label: zjmp  %12", 12);
	return (0);
}
