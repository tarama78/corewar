/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:43:42 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/16 15:51:44 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		ft_label_address(char *label, t_label *tlabel, t_a *data)
{
	int i;
	int dir;

	i = -1;
	dir = ((label[0] == '%' && label[1] == ':') ? 1 : 0);
	if (tlabel == NULL || data->nb_label == 0)
		return (ERROR);
	while (i < data->nb_label &&
			ft_strequ(label + ((dir == 1) ? 2 : 1), tlabel[++i].name) != 1)
		;
	if (i == data->nb_label)
		return (ERROR);
	return (i);
}

int		ft_handle_args(int file, char *arg, t_a *data, int index)
{
	char	*octet;
	int		i;
	int		value;
	int		k;

	k = MEM_SIZE + 10;
	if (arg[0] == 'r')
	{
		ft_putchar_fd((char)ft_atoi(arg + 1), file);
		return (SUCCESS);
	}
	i = (arg[0] == DIRECT_CHAR ? DIR_SIZE : IND_SIZE);
	i = (g_op_tab[index].size_change == 1 ? 2 : i);
	if ((arg[0] == DIRECT_CHAR && arg[1] == LABEL_CHAR) || arg[0] == LABEL_CHAR)
		k = ft_label_address(arg, data->label, data);
	if (k == ERROR)
		return (ERROR);
	if (k != MEM_SIZE + 10)
		value = data->label[k].addr - data->cmpt;
	else
		value = ((arg[0] == DIRECT_CHAR) ? ft_atoi(arg + 1) : ft_atoi(arg));
	octet = (char*)&value;
	while (--i >= 0)
		ft_putchar_fd(octet[i], file);
	return (SUCCESS);
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
