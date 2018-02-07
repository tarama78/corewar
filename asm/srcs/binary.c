/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:40:53 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/06 18:50:59 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../libft/includes/ft_printf.h"
#include <stdio.h>

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

void	ft_handle_args(int file, char *arg)
{
	int i;

	i = 0;
	if (arg[0] == '%' && arg[1] == ':')
		ft_dprintf(file, "%s", arg + 2);
	else
		ft_dprintf(file, "%s", arg + 1);

}

int		ft_typepara(char *arg)
{
	if (arg[0] == 'r')
		return (1);
	else if (arg[0] == '%')
		return (2);
	else
		return (3);
}

void	ft_encoding(int file, int nb_arg, char **words)
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
}

int		ft_binaire(int file, t_a *data, t_line *tab_line)
{
	t_line *tmp;
	char **words;
	char **args;
	int i;
	int j;
	int k;

	tmp = tab_line;
	i = -1;
	while (tmp != NULL)
	{
		j = 1;
		k = -1;
		words = ft_strsplit(tmp->line, ' ');
		if (ft_strchr(words[0], ':') != NULL)
				++j;
		args = ft_strsplit(words[j], ',');
		while (i < 17 && op_tab[++i].name != 0
				&& ft_strcmp(words[j - 1], op_tab[i].name) != 0)
			;
		ft_dprintf(file, "%s", ft_itoa(op_tab[i].opcode));
		if (op_tab[i].ok_codage == 1)
			ft_encoding(file, op_tab[i].nb_arg, args);
		while (args[++k])
			ft_handle_args(file, args[k]);
		tmp = tmp->next;
	}
	return (1);
}
