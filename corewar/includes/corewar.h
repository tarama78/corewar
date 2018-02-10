/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/10 15:17:02 by tnicolas         ###   ########.fr       */
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
# include <stdbool.h>

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

//////////////////////////ncurses
# include <ncurses.h>
# include <math.h>
# include <time.h>
# define NB_COLORS 6
# define TIME_BOLD_MEM 50
# define WIN_H 10
# define WIN_W 50
typedef struct	s_color
{
	int			border;
	int			black;
	int			text;
	int			defaut;
	int			player[MAX_PLAYERS + 1];
	int			player_live[MAX_PLAYERS + 1];
}				t_color;

typedef struct	s_ncurses
{
	WINDOW		*win_mem;
	WINDOW		*win_info;
	WINDOW		*win_player[MAX_PLAYERS];
	int			sqrt_mem_size;
	t_color		color;
}				t_ncurses;
/////////////////////////////////

typedef struct			s_mem_info
{
	uint64_t			cycle : 32; //cycle de changement de couleur (pour le surlignement);
	uint64_t			player : 8; //numero du joueur (pour definir la couleur) commence a 1 (0 = aucun joueur);
	uint64_t			player_process : 8; //numero du joueur (pour definir la couleur) commence a 1 (0 = aucun joueur);
	uint64_t			process : 1; //= 1 si il y as un process sur la case
	uint64_t			pad : 15; //libre pour stocker d'autres info

}						t_mem_info;

typedef struct			s_a
{
	t_process			*process;
	t_player			player[MAX_PLAYERS];
	int					cycle_to_die;
	uint64_t			cycle;
	uint8_t				mem[MEM_SIZE];
	t_mem_info			mem_info[MEM_SIZE];
	int					num_of_player;
	t_ncurses			nc;
}						t_a;

/*
** ncurses
*/
void		ft_init(t_a *a);
t_color		ft_init_color();
int			ft_get_color(t_a *a, int k);
void		ft_print(t_a *a);
void		ft_free_nc(t_a *a);

#endif
