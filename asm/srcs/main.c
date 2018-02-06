/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:07:32 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/06 18:00:29 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_printf.h"
#include "corewar.h"

static void	init_struct(t_a *data)
{
	ft_bzero(data->comment, sizeof(data->comment));
	ft_bzero(data->name, sizeof(data->name));
	data->line = NULL;
	data->nb_label = 0;
	data->label = NULL;
	data->file_name = NULL;
}

static void	file_name(char *name)
{
	int	i;

	i = (int)ft_strlen(name);
	while (i-- > 0)
		if (name[i] == '.')
		{
			name[i] = '\0';
			return ;
		}
}

int			main(int argc, char **argv)
{
	t_a	data;
	int	fd;

	if (argc == 1)
	{
		ft_printf("usage: ./asm file.s\n");
		return (0);
	}
	while (--argc > 0)
	{
		if ((fd = open(argv[argc], O_RDONLY)) == -1)
			ft_printf("Can't read source file %s\n", argv[argc]);
		else
		{
			init_struct(&data);
			file_name(argv[argc]);
			data.file_name = argv[argc];
			if (!ft_parse_file(&data, fd))
				ft_printf("failed\n");
			free_content(&data, 0);
			close(fd);
		}
	}
	return (0);
}