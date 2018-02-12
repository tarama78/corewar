/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:08:32 by atripard          #+#    #+#             */
/*   Updated: 2018/02/12 13:08:33 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		check_magic_number(int fd)
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

int		check_prog_size(int fd, t_player *player)
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
		ft_printf("%s is too big, %u > %u\n",
			player->name, *((uint32_t*)(&size)), CHAMP_MAX_SIZE);
		return (ERROR);
	}
	player->mem_size = *((uint32_t*)(&size));
	return (SUCCESS);
}

int		load_name(int fd, t_player *player)
{
	if (read(fd, player->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		return (ERROR);
	return (SUCCESS);
}

int		load_comment(int fd, t_player *player)
{
	if (read(fd, player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		return (ERROR);
	return (SUCCESS);
}

int		load_prog(int fd, t_player *player)
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

int		load_players(t_a *a)
{
	int	fd;
	int	i;

	i = 0;
	while (i < a->num_of_player)
	{
		if ((fd = open(a->file[i].filename, O_RDONLY)) < 0)
			return (ERROR);
		if (check_magic_number(fd) == ERROR)
			return (ERROR);
		if (load_name(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		if (check_prog_size(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		if (load_comment(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		if (load_prog(fd, &(a->player[i])) == ERROR)
			return (ERROR);
		a->player[i].player_number_print = a->file[i].player_number_print;
		++i;
	}
	return (SUCCESS);
}
