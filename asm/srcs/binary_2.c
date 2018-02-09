/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:43:42 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/09 12:48:21 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		ft_label_address(char *label, t_label *tab_label, int dir)
{
	int i;

	i = -1;
	while (ft_strequ(label + ((dir == 1) ? 2 : 1), tab_label[++i].name) != 1)
		;
	return (tab_label[i].addr);
}

void	ft_handle_args(int file, char *arg, t_a *data, int index)
{
	char	*octet;
	int		i;
	int		value;

	if (arg[0] == 'r')
		ft_putchar_fd((char)ft_atoi(arg + 1), file);
	else
	{
		i = (arg[0] == '%' ? DIR_SIZE : IND_SIZE);
		i = (g_op_tab[index].size_change == 1 ? 2 : i);
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

int		ft_typepara(char *arg)
{
	if (arg[0] == 'r')
		return (REG_CODE);
	else if (arg[0] == DIRECT_CHAR)
		return (DIR_CODE);
	else
		return (IND_CODE);
}

void	ft_encoding(int file, char **words)
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

void	ft_putname_magic(int file, t_a *data)
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