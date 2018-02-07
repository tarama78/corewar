/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:40:53 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/07 18:59:51 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <stdio.h>

static void		ft_handle_args(int file, char *arg, t_label *label, int *cmpt, int index_name)
{
	char *octet;
	int i;
	int value;

	if (arg[0] == 'r')
	{
		cmpt += 1;
		ft_putchar_fd((char)ft_atoi(arg + 1), file);
	}
	else
	{
		i = op_tab[index_name].diroct;
		if (arg[0] == '%' && arg[1] == ':')
			value = label->addr - *cmpt;
		else if (arg[0] == '%')
			value = ft_atoi(arg + 1);
		else
			value = ft_atoi(arg);
		cmpt += i;
		octet = (char*)&value;
		while (--i >= 0)
			ft_putchar_fd(octet[i], file);
	}
}

static int		ft_typepara(char *arg)
{
	if (arg[0] == 'r')
		return (REG_CODE);
	else if (arg[0] == DIRECT_CHAR)
		return (DIR_CODE);
	else
		return (IND_CODE);
}

static void		ft_encoding(int file, char **words, int *cmpt)
{
	int				i;
	unsigned char	octet;
	int				decal;

	octet = 0;
	decal = 8;
	i = -1;
	while (words[++i] != NULL)
	{
		decal -= 2;
		octet += ft_typepara(words[i]) << decal;
	}
	ft_dprintf(file, "%c", octet);
	*cmpt += 1;
}

void			ft_putname_magic(int file, t_a *data)
{
	int magic;
	char *octet;
	int i;

	i = 4;
	magic = COREWAR_EXEC_MAGIC;
	octet = (char*)&magic;
	while (--i >= 0)
		ft_putchar_fd(octet[i], file);
	write(file, data->name, PROG_NAME_LENGTH);
	write(file, data->comment, COMMENT_LENGTH);
}

int				ft_binary(int file, t_a *data)
{
	t_line *tmp;
	char **words;
	char **args;
	int i;
	int j;
	int k;

	int cmpt;

	tmp = data->line;
	cmpt = 0;
	ft_putname_magic(file, data);
	while (tmp != NULL)
	{
		j = 1;
		k = -1;
		i = -1;
		words = ft_strsplit(tmp->line, ' ');
		if (ft_strchr(words[0], LABEL_CHAR) != NULL)
				++j;
		args = ft_strsplit(words[j], SEPARATOR_CHAR);
		while (++i < 17 && op_tab[i].name != 0
				&& ft_strcmp(words[j - 1], op_tab[i].name) != 0)
			;
		ft_dprintf(file, "%c", (char)op_tab[i].opcode);
		cmpt += 1;
		if (op_tab[i].octet_type_arg == 1)
			ft_encoding(file, args, &cmpt);
		while (args[++k])
			ft_handle_args(file, args[k], data->label, &cmpt, i);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
