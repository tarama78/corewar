/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:35:36 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/09 12:48:23 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int		ft_free_binary(char ***word, char ***args)
{
	int		i;

	i = -1;
	if (word != NULL)
	{
		while ((*word)[++i])
			ft_fruit(1, &((*word)[i]));
		ft_fruit(1, word);
	}
	i = -1;
	if (args != NULL)
	{
		while ((*args)[++i])
			ft_fruit(1, &((*args)[i]));
		ft_fruit(1, args);
	}
	return (SUCCESS);
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

static int		ft_binary_3(long ik, t_a *data, int file, char **args)
{
	int i;
	int k;

	i = ft_get2arg(ik, 0);
	k = ft_get2arg(ik, 1);
	ft_dprintf(file, "%c", (char)g_op_tab[i].opcode);
	if (g_op_tab[i].octet_type_arg == 1)
		ft_encoding(file, args);
	while (args[++k])
		ft_handle_args(file, args[k], data, i);
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
			return (ERROR);
		if (word[1] == NULL && ((tmp = tmp->next) ? 1 : 1) &&
				ft_free_binary(&word, NULL) == SUCCESS)
			continue ;
		if (!(args = ft_strsplit(word[j], SEPARATOR_CHAR)) &&
				ft_free_binary(&word, NULL))
			return (ERROR);
		while (++i < 17 && g_op_tab[i].name != 0
				&& ft_strcmp(word[j - 1], g_op_tab[i].name) != 0)
			;
		ft_binary_3(ft_2arg(i, k), data, file, args);
		data->cmpt += tmp->size;
		tmp = tmp->next;
		ft_free_binary(&word, &args);
	}
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
