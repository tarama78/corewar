/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:07:32 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/07 14:23:36 by ynacache         ###   ########.fr       */
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
	int fd_2;
	int	ret_parse;
	int	i;
	int	ret;

	ret = EXIT_SUCCESS;
	if (argc == 1)
	{
		ft_printf("usage: ./asm file.s\n");
		return (0);
	}
	fd_2 = open("txt.cor", O_CREAT | O_RDWR);
	i = 0;
	while (++i < argc)
	{
		if ((fd = open(argv[i], O_RDONLY)) == -1)
			ft_printf("{red}Can't read source file{yellow} %s{eoc}\n", argv[i]);
		else
		{
			init_struct(&data);
			file_name(argv[i]);
			data.file_name = argv[i];
			ft_printf("{bold}{yellow}compilation: {eoc}{yellow}%s.s{eoc}\n",
					data.file_name);
			if ((ret_parse = ft_parse_file(&data, fd)) == 0 || ret_parse == ERROR)
			{
				ft_printf("{red}{bold}compilation failed: {eoc}{yellow}%s.s{eoc}"
						"\n", data.file_name);
				ret = EXIT_FAILURE;
			}
			else
      {
			ft_binary(fd_2, &data);
				ft_printf("{green}{bold}compilation success: {eoc}{yellow}%s"
						".cor{eoc}\n", data.file_name);
      }
			free_content(&data, 0);
			close(fd);
			if (i + 1 < argc)
				ft_printf("\n");
		}
	}
	return (ret);
}
