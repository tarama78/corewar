/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:07:32 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/06 11:49:52 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_printf.h"
#include "corewar.h"

static void	init_struct(t_a *data)
{
	data->name = NULL;
//	data->comment = NULL;
	data->line = NULL;
	data->nb_label = 0;
	data->label = NULL;
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
			file_name(argv[argc]);
			init_struct(&data);
			data.name = argv[argc];
			//APPEL FONCTION
			ft_printf("%s\n", data.name);
			close(fd);
		}
	}
	return (0);
}
