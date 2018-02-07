/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:07:32 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/07 18:45:55 by tnicolas         ###   ########.fr       */
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

static int	ft_open_files(char *filename, int *fd1, int *fd2)
{
	char	*name2;

	if (!(name2 = malloc(sizeof(char) * (ft_strlen(filename) + 5))))
		exit(EXIT_FAILURE);
	ft_strncpy(name2, filename, ft_strlen(filename) + 1);
	file_name(name2);
	ft_strcat(name2, ".cor");
	if ((*fd1 = open(filename, O_RDONLY)) == -1)
		ft_printf("{red}Can't read source file{yellow} %s{eoc}\n", filename);
	if ((*fd2 = open(name2, O_CREAT | O_RDWR)) == -1)
		exit(EXIT_FAILURE);
	free(name2);
	return (SUCCESS);
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
	i = 0;
	while (++i < argc)
	{
		if (ft_open_files(argv[i], &fd, &fd_2) == SUCCESS)
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
			close(fd_2);
			if (i + 1 < argc)
				ft_printf("\n");
		}
	}
	return (ret);
}
