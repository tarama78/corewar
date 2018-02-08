/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:35:36 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/08 18:11:45 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <stdio.h>

static int		ft_label_address(char *label, t_label *tab_label, int dir)
{
	int i;

	i = -1;
	while (ft_strequ(label + ((dir == 1) ? 2 : 1), tab_label[++i].name) != 1)
		;
	return (tab_label[i].addr);
}

static void		ft_handle_args(int file, char *arg, t_a *data, int index_name)
{
	char	*octet;
	int		i;
	int		value;

	if (arg[0] == 'r')
		ft_putchar_fd((char)ft_atoi(arg + 1), file);
	else
	{
		i = (arg[0] == '%' ? DIR_SIZE : IND_SIZE);
		i = (g_op_tab[index_name].size_change == 1 ? 2 : i);
		if (arg[0] == '%' && arg[1] == ':')
		{
			value = ft_label_address(arg, data->label, 1) - data->cmpt;
		}
		else if (arg[0] == ':')
			value = ft_label_address(arg, data->label, 0) - data->cmpt;
		else if (arg[0] == '%')
			value = ft_atoi(arg + 1);
		else
			value = ft_atoi(arg);
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

static void		ft_encoding(int file, char **words)
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
}

void			ft_putname_magic(int file, t_a *data)
{
	int		magic;
	char	*octet;
	int		i;

	i = 4;
	magic = COREWAR_EXEC_MAGIC;
	octet = (char*)&magic;
	while (--i >= 0)
		ft_putchar_fd(octet[i], file);
	write(file, data->name, PROG_NAME_LENGTH);
	write(file, "\0\0\0\0", 4);
	i = 4;
	octet = (char*)&data->prog_size;
	while (--i >= 0)
		ft_putchar_fd(octet[i], file);
	write(file, data->comment, COMMENT_LENGTH);
	write(file, "\0\0\0\0", 4);
}

static int		ft_binary_2(int *j, int *i, char ***word, t_line *tmp)
{
	*j = 1;
	*i = -1;
	if (!(*word = ft_strsplit(tmp->line, ' ')))
		return (ERROR);
	if (ft_strchr((*word)[0], LABEL_CHAR) != NULL)
		++(*j);
	return (SUCCESS);
}

static int		ft_binary_1(int file, t_a *data, t_line *tmp, int i)
{
	int		j;
	int		k;
	char	**word;
	char	**args;

	while (tmp != NULL)
	{
		k = -1;
		if (ft_binary_2(&j, &i, &word, tmp) == ERROR)
			ft_err_msg(data, tmp, "malloc fail", 0);
		if (word[1] == NULL && ((tmp = tmp->next) ? 1 : 1))
			continue ;
		if (!(args = ft_strsplit(word[j], SEPARATOR_CHAR)))
			ft_err_msg(data, tmp, "malloc fail", 0);
		while (++i < 17 && g_op_tab[i].name != 0
				&& ft_strcmp(word[j - 1], g_op_tab[i].name) != 0)
			;
		ft_dprintf(file, "%c", (char)g_op_tab[i].opcode);
		if (g_op_tab[i].octet_type_arg == 1)
			ft_encoding(file, args);
		while (args[++k])
			ft_handle_args(file, args[k], data, i);
		data->cmpt += tmp->size;
		tmp = tmp->next;
	}
	// ft_free_binary avec adress args & word
	return (SUCCESS);
}

int				ft_binary(int file, t_a *data)
{
	t_line	*tmp;
	int		i;

	tmp = data->line;
	data->cmpt = 0;
	i = -1;
	ft_putname_magic(file, data);
	ft_binary_1(file, data, tmp, i);
	return (SUCCESS);
}
