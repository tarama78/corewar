/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:07:32 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/07 15:54:15 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
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
	int	ret_parse;
	int	ret;

	ret = EXIT_SUCCESS;
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
			if ((ret_parse = ft_parse_file(&data, fd)) == 0 || ret_parse == ERROR)
			{
				ft_printf("{red}compilation failed {yellow}%s.s{eoc}\n",
						data.file_name);
				ret = EXIT_FAILURE;
			}
			else
				ft_printf("{green}compilation success: {yellow}%s.cor{eoc}\n",
						data.file_name);
			free_content(&data, 0);
			close(fd);
		}
	}
	return (ret);
}
