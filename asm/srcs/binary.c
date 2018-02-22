/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynacache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:35:36 by ynacache          #+#    #+#             */
/*   Updated: 2018/02/19 12:21:50 by tnicolas         ###   ########.fr       */
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

static int		ft_binary_3(long ik, t_a *data, char **args)
{
	int i;
	int k;

	i = ft_get2arg(ik, 0);
	k = ft_get2arg(ik, 1);
	ft_add_char(data, (char)g_op_tab[i].opcode);
	if (g_op_tab[i].octet_type_arg == 1)
		ft_encoding(data, args);
	while (args[++k])
		if (ft_handle_args(args[k], data, i) == ERROR)
			return (ERROR);
	return (SUCCESS);
}

static int		ft_binary_1(t_a *data, t_line *tmp, int i)
{
	int		j;
	int		k;
	char	**word;
	char	**args;

	while (tmp != NULL && ((k = -1) ? 1 : 1))
	{
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
		if (ft_binary_3(ft_2arg(i, k), data, args) == ERROR)
			return (ERROR);
		data->cmpt += tmp->size;
		tmp = tmp->next;
		ft_free_binary(&word, &args);
	}
	return (SUCCESS);
}

int				ft_binary(char *filename, t_a *data)
{
	t_line	*tmp;
	int		i;
	int		fd;

	data->str = NULL;
	data->len_str = 0;
	tmp = data->line;
	data->cmpt = 0;
	i = -1;
	ft_putname_magic(data);
	if (ft_binary_1(data, tmp, i) == ERROR)
		return (ERROR);
	if ((fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU)) == -1)
		exit(EXIT_FAILURE);
	write(fd, data->str, data->len_str);
	free(data->str);
	close(fd);
	return (SUCCESS);
}
