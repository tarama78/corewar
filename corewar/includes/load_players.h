/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:02:42 by atripard          #+#    #+#             */
/*   Updated: 2018/02/12 16:04:15 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_PLAYERS_H
# define LOAD_PLAYERS_H

#include <corewar.h>

int		check_magic_number(int fd);
int		check_prog_size(int fd, t_player *player);
int		load_name(int fd, t_player *player);
int		load_comment(int fd, t_player *player);
int		load_prog(int fd, t_player *player);

#endif
