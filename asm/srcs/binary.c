/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:40:53 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/07 15:29:59 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <stdio.h>

static void		ft_handle_args(int file, char *arg, t_label *label, int *cmpt)
{
	int i;

	i = 0;
	if (arg[0] == '%' && arg[1] == ':')
	{
		printf("adress --> %d\n", label->addr);
		printf("arg in handle arg --> %s", arg + 2);
//		ft_dprintf(file, "%s", arg + 2);
		ft_putchar_fd((char)(label->addr >> 8), file);
		ft_putchar_fd((char)(label->addr << 8), file);
	}
	else
	{
		printf("arg in handle arg --> %s et aoit -->%d\n", arg, ft_atoi(arg + 1));
//		ft_dprintf(file, "%hhd", ft_atoi(arg + 1));
//		if (arg[0] == '%')
//		{
//			ft_putchar_fd((char)ft_atoi(arg + 1) >> 24, file);
//			ft_putchar_fd((char)ft_atoi(arg + 1) >> 16, file);
//		}
		if (arg[0] != 'r')
			ft_putchar_fd((char)ft_atoi(arg + 1) >> 8, file);
		ft_putchar_fd((char)ft_atoi(arg + 1), file);
		cmpt += 2;
	}
}

static int		ft_typepara(char *arg)
{
	if (arg[0] == 'r')
		return (1);
	else if (arg[0] == '%')
		return (2);
	else
		return (3);
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
	int magic = COREWAR_EXEC_MAGIC;
	char *ptr = (char*)&magic;
	int i;

	i = 4;

	while (--i >= 0)
		ft_putchar_fd(ptr[i], file);
	write(file, data->name, 128);
	write(file, data->comment, 2048);
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
		if (ft_strchr(words[0], ':') != NULL)
				++j;
		args = ft_strsplit(words[j], ',');
		while (++i < 17 && op_tab[i].name != 0
				&& ft_strcmp(words[j - 1], op_tab[i].name) != 0)
			;
		printf("///////////line --> %s\n", tmp->line);
		ft_dprintf(file, "%c", (char)op_tab[i].opcode);
		cmpt += 1;
		if (op_tab[i].octet_type_arg == 1)
			ft_encoding(file, args, &cmpt);
		while (args[++k])
		{
			printf("arg --> %s\n", args[k]);
			ft_handle_args(file, args[k], data->label, &cmpt);
		}
		tmp = tmp->next;
	}
	return (1);
}
