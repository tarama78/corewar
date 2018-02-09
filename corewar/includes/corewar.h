/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/09 20:45:51 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <op.h>
# include <libft.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

# define SUCCESS 0
# define ERROR -1

typedef struct		s_op
{
	char			*name;
	int				nb_arg;
	int				type_arg[MAX_ARGS_NUMBER];
	int				opcode;
	int				nb_cycle;
	char			*descrition;
	int				octet_type_arg;
	int				size_change;
}					t_op;

extern t_op			g_op_tab[17];

typedef struct			s_process
{
	struct s_process	*next;
	int					num_player;
	int					reg[REG_NUMBER];
	int					pc;
	int					cycle_wait;
	bool				carry;
	bool				live;
}						t_process;

typedef struct			s_player
{
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	int					player_number_print;
	int					last_live_cycle;
	int					nb_live_total;
	int					nb_live_current;
	size_t				nb_process;
}						t_player;

typedef struct	s_color
{
	int			border;
	int			black;
	int			defaut;
	int			player[MAX_PLAYERS + 1];
}				t_color;

typedef struct	s_ncurses
{
	WINDOW		*win_mem;
	WINDOW		*win_info;
	int			sqrt_mem_size;
	t_color		color;
}				t_ncurses;

typedef struct			s_a
{
	t_process			*process;
	t_player			player[MAX_PLAYERS];
	int					cycle_to_die;
	uint64_t			cycle;
	uint8_t				mem[MEM_SIZE];
	uint8_t				mem_color[MEM_SIZE];
	t_ncurses			nc;
}						t_a;

#endif
