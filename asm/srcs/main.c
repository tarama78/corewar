/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:07:32 by bcozic            #+#    #+#             */
/*   Updated: 2018/02/22 14:25:50 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | main.c                                                   |
**   |     file_name(9 lines)                                   |
**   |     ft_open_files(13 lines)                              |
**   |     ft_compile_file2(10 lines)                           |
**   |     ft_compile_file(19 lines)                            |
**   |     main(24 lines)                                       |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <fcntl.h>
#include <corewar.h>

static void	file_name(char *name)
{
	int i;

	i = (int)ft_strlen(name);
	while (i-- > 0)
		if (name[i] == '.')
		{
			name[i] = '\0';
			return ;
		}
}

static int	ft_open_files(char *filename, int *fd1, char **name2, int *ret)
{
	if (!(*name2 = malloc(sizeof(char) * (ft_strlen(filename) + 5))))
		ft_err_msg(NULL, NULL, "malloc fail", 1);
	ft_strncpy(*name2, filename, ft_strlen(filename) + 1);
	file_name(*name2);
	ft_strcat(*name2, ".cor");
	if ((*fd1 = open(filename, O_RDONLY)) == -1)
	{
		*ret = EXIT_FAILURE;
		free(name2);
		ft_printf("{red}Can't read source file{yellow} %s{eoc}\n", filename);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	ft_compile_file2(t_a *data, char *filename, char *argvi)
{
	if (ft_binary(filename, data) == ERROR)
	{
		ft_printf("{red}{bold}compilation failed: {eoc}"
				"{yellow}%s{eoc}\n",
				"bad label");
		return (ERROR);
	}
	ft_printf("{green}{bold}compilation success: {eoc}{yellow}%s"
				".cor{eoc}\n", argvi);
	return (SUCCESS);
}

static int	ft_compile_file(t_a *data, int fd, char *filename, char *argvi)
{
	int ret;

	ret = EXIT_SUCCESS;
	ft_bzero(data, sizeof(t_a));
	file_name(argvi);
	data->file_name = argvi;
	ft_printf("{bold}{yellow}compilation: {eoc}{yellow}%s.s{eoc}\n",
				data->file_name);
	if (ft_parse_file(data, fd) == ERROR)
	{
		ft_printf("{red}{bold}compilation failed: {eoc}"
					"{yellow}%s.s{eoc}\n", argvi);
		ret = EXIT_FAILURE;
	}
	else if (ft_compile_file2(data, filename, argvi) == ERROR)
		return (EXIT_FAILURE);
	free_content(data, 0);
	close(fd);
	return (ret);
}

int			main(int argc, char **argv)
{
	t_a		data;
	int		fd;
	char	*filename;
	int		i;
	int		ret;

	ft_test_malloc(128);
	ret = EXIT_SUCCESS;
	if (argc == 1)
	{
		ft_printf("usage: ./asm <files.s>\n");
		return (ret);
	}
	i = 0;
	while (++i < argc)
		if (ft_open_files(argv[i], &fd, &filename, &ret) == SUCCESS)
		{
			ret = (ft_compile_file(&data, fd, filename, argv[i]) == EXIT_SUCCESS
					&& ret == EXIT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
			if (i + 1 < argc)
				ft_printf("\n");
			free(filename);
		}
	return (ret);
}
