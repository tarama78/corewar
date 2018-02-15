/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/15 14:36:30 by bcozic           ###   ########.fr       */
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
# define NB_COMM 16

typedef struct			s_op
{
	char				*name;
	int					nb_arg;
	int					type_arg[MAX_ARGS_NUMBER];
	int					opcode;
	int					nb_cycle;
	char				*descrition;
	int					octet_type_arg;
	int					size_change;
}						t_op;

extern t_op				g_op_tab[17];

typedef struct			s_process
{
	struct s_process	*next;
	int					num_player;
	int					player_index;
	int					reg[REG_NUMBER + 1];
	int					pc;
	int					cycle_wait;
	int					carry;
	int					live;
}						t_process;


typedef struct			s_player
{
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	uint8_t				mem[CHAMP_MAX_SIZE];
	int					mem_size;
	int					player_number_print;
	int					last_live_cycle;
	int					nb_live_total;
	int					nb_live_current;
	size_t				nb_process;
}						t_player;

typedef struct			s_champ_file
{
	int					player_number_print;
	char				*filename;
}						t_champ_file;

//////////////////////////ncurses
# include <ncurses.h>
# include <math.h>
# include <time.h>
# define NB_COLORS 6
# define SPEED 100000 // plus la val est grande plus c'est lent (a->speed)
# define CHANGE_SPEED 10000
# define TIME_BOLD_MEM 50
# define WIN_H 12
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
	int			pause;
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
	t_player			*winner;

	t_champ_file		file[MAX_PLAYERS];
	int					live;
	int					visu;
	int					num_of_player;
	int					dump_cycle;
	int					n;
	uint64_t			cycle_to_die;
	uint64_t			last_dec_cycle;
	uint64_t			nxt_cycle_die;
	uint64_t			cycle;
	uint8_t				mem[MEM_SIZE];
	t_ncurses			nc;
	t_mem_info			mem_info[MEM_SIZE];
	long				speed;
}						t_a;

int						ft_is_uint(char *str, int *num);
int						parse_args(t_a *a, int ac, char **av);
int						load_players(t_a *a);
void					load_memory(t_a *a);
void					init_command(void (**f)(t_process *, t_a *));
int						check_cycle(t_process *prc, t_a *a);
int						rec_memory(char type, int *curs, t_a *a, int addr);
int						check_type(t_process *prc, t_a *a);
void					add_process(t_a *a, t_process *cpy);
void					first_process(t_a *a, int player, int offset);
void					game_loop(t_a *a, void (**f)(t_process *, t_a *));
void					game_turn(t_a *a, void (**f)(t_process *, t_a *));

void					add(t_process *prc, t_a *a);
void					sub(t_process *prc, t_a *a);
void					f_or(t_process *prc, t_a *a);
void					f_xor(t_process *prc, t_a *a);
void					f_and(t_process *prc, t_a *a);
void					ld(t_process *prc, t_a *a);
void					lld(t_process *prc, t_a *a);
void					ldi(t_process *prc, t_a *a);
void					lldi(t_process *prc, t_a *a);
void					st(t_process *prc, t_a *a);
void					sti(t_process *prc, t_a *a);
void					ft_aff(t_process *prc, t_a *a);
void					ft_zjmp(t_process *prc, t_a *a);
void					live(t_process *prc, t_a *a);
void					ft_fork(t_process *prc, t_a *a);
void					lfork(t_process *prc, t_a *a);
void					ft_move(t_process *prc, t_a *a);

void 					ft_curseur(t_process *prc, int pc, int curs, t_a *a);
void					winner(t_a *a);


/*
** ncurses
*/
void		ft_init(t_a *a);
t_color		ft_init_color();
int			ft_get_color(t_a *a, int k);
void		ft_print(t_a *a);
void		ft_free_nc(t_a *a);

#endif
