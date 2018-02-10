/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 15:34:46 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/10 16:26:14 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		ft_usage(int quit)
{
	ft_putstr("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	if (quit)
		exit(0);
}

int			ft_parse_dump(t_a *a, char *dump)
{
	int	num;

	if (!ft_is_uint(dump, &num))
		return (0);
	a->dump_cycle = num;
	return (1);
}

int			ft_parse_n(char *s, int *n)
{
	if (!ft_is_uint(s, n))
		return (0);
	return (1);
}

int			ft_add_file(t_champ_file *file, char *file_name, int *n, int player)
{
	int next_number;
	int i;

	if (player >= MAX_PLAYERS)
		return (0);
	file[player].filename = file_name;	
	file[player].player_number_print = *n;
	i = 0;
	next_number = 1;
	while (i < player + 1)
	{
		if (next_number == file[i].player_number_print)
		{
			++next_number;
			i = -1;
		}
		++i;
	}
	*n = next_number;
	return (1);
}

int			ft_parse_arg(t_a *a, int ac, char **av)
{
	int i;
	int	player;
	int	n;

	i = 0;
	n = 1;
	player = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (ft_strequ("-dumpl", av[i]))
			{
				if (((i > 1) || (i + 1 >= ac) || !ft_parse_dump(a, av[++i])))
					return (ERROR);
			}
			else if (ft_strequ("-n", av[i]))
			{
				if (((i + 2 >= ac) || !ft_parse_n(av[++i], &n) || (av[i + 1][0] == '-')))
					return (ERROR);
			}
			else
				return (ERROR);
		}
		else
			if (!ft_add_file(a->file, av[i], &n, player++))
				return (ERROR);
	}
	a->num_of_player = player;
	return (SUCCESS);
}

int 	ft_check_magic_number(int fd)
{
	int			i;
	uint32_t	magic;
	char		*byte;

	i = 4;
	magic = 0;
	byte = (char*)&magic;
	while (--i >= 0)
	{
		if (read(fd, byte + i, 1) <= 0)
			return (ERROR);
	}
	if (magic == COREWAR_EXEC_MAGIC)
		return (SUCCESS);
	else
		return (ERROR);
}

int		ft_check_prog_size(int fd, t_player *player)
{
	int			i;
	char		*byte;
	uint64_t	size;

	i = 8;
	size = 0;
	byte = (char*)&size;
	while (--i >= 0)
	{
		if (read(fd, byte + i, 1) <= 0)
			return (ERROR);
	}
	if (*((uint32_t*)(&size) + 1) != 0)
			return (ERROR);
	if (*((uint32_t*)(&size)) > CHAMP_MAX_SIZE)
	{
		ft_printf("champ too big, %u > %u\n", *((uint32_t*)(&size)), CHAMP_MAX_SIZE);
		return (ERROR);
	}
	player->mem_size = *((uint32_t*)(&size));
	return (SUCCESS);
}

int		ft_load_name(int fd, t_player *player)
{
	if (read(fd, player->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		return (ERROR);
	return (SUCCESS);
}

int		ft_load_comment(int fd, t_player *player)
{
	if (read(fd, player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		return (ERROR);
	return (SUCCESS);
}

int		ft_load_prog(int fd, t_player *player)
{
	int			i;
	uint32_t	padding;
	char		*byte;

	i = 4;
	byte = (char*)&padding;
	while (--i >= 0)
	{
		if (read(fd, byte + i, 1) <= 0)
			return (ERROR);
	}
	if (padding != 0)
		return (ERROR);
	if (read(fd, player->mem, player->mem_size) != player->mem_size)
		return (ERROR);
	return (SUCCESS);
}

int		ft_load_player(t_a *a)
{
	int	fd;
	int	i;

	i = 0;
	while (i < a->num_of_player)
	{
		if ((fd = open(a->file[i].filename, O_RDONLY)) < 0)
			return (ERROR);
		if (ft_check_magic_number(fd) == ERROR)
			return (ERROR);
		if (ft_load_name(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		if (ft_check_prog_size(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		if (ft_load_comment(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		if (ft_load_prog(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		a->player[i].player_number_print = a->file[i].player_number_print;
		++i;
	}
	return (SUCCESS);
}

void		print_info(t_a *a)
{
	printf("dump: %d\n", a->dump_cycle);	
	printf("number of player: %d\n\n", a->num_of_player);	

	for (int i = 0; i < a->num_of_player; ++i)
	{
		printf("filename: %s\n", a->file[i].filename);
		printf("player_number_print: %d\n\n", a->file[i].player_number_print);
	}
}

void	ft_load_memory_player(uint8_t *mem, t_mem_info *info, t_player *player, int p_num)
{
	int	i;

	i = 0;
	while (i < player->mem_size)
	{
		mem[i] = player->mem[i];
		info[i].player = p_num;
		++i;
	}
}

void	ft_load_memory(t_a *a)
{
	int offset;
	int	i;
	t_process	*new_prc;

	i = 0;
	offset = MEM_SIZE / a->num_of_player;
	while (i < a->num_of_player)
	{
		ft_load_memory_player(a->mem + (offset * i), a->mem_info + (offset * i), &(a->player[i]), i + 1);
		new_prc = first_process(a, i, offset);
		++i;
	}
}

int			main(int ac, char **av)
{
	t_a a;

	if (ac == 1)
		ft_usage(1);
	ft_memset(&a, 0, sizeof(a));
	if (ft_parse_arg(&a, ac, av) == ERROR)
		ft_usage(1);
	if (ft_load_player(&a) == ERROR)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	ft_load_memory(&a);
	ft_init(&a);//ncurses
	ft_print(&a);
	while (getch() != 27)
	{
		ft_print(&a);
		usleep(50);
	}
	ft_free_nc(&a);//ncurses
	//resolv_game(&a)
}
