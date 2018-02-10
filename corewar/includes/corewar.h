/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/10 15:19:30 by bcozic           ###   ########.fr       */
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
	int					reg[REG_NUMBER + 1];
	int					pc;
	int					cycle_wait;
  int				carry;
  int				live;
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

typedef struct			s_mem_info
{
	uint64_t			cycle : 32; //cycle de changement de couleur (pour le surlignement)
	uint64_t			player : 8; //numero du joueur (pour definir la couleur) commence a 1 (0 = aucun joueur)
	uint64_t			process : 1; //= 1 si il y as un process sur la case`
	uint64_t			pad : 23; //libre pour stocker d'autres info
}						t_mem_info;

typedef struct			s_a
{
	t_process			*process;
	t_player			player[MAX_PLAYERS];
	t_champ_file		file[MAX_PLAYERS];
	int					num_of_player;
	int					dump_cycle;
	int					cycle_to_die;
	uint64_t			cycle;
	uint8_t				mem[MEM_SIZE];
	t_mem_info			mem_info[MEM_SIZE];
}						t_a;

int	ft_is_uint(char *str, int *num);
void					init_command(void *(**f)(t_process *, t_a *));
int						check_cycle(t_process *prc, t_a *a);
int						rec_memory(char type, int *curs, t_a *a, int addr);
int						check_type(t_process *prc, t_a *a);
t_process				*add_process(t_a *a, t_process *cpy);
t_process				*first_process(t_a *a, int player, int offset);

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
void					move(t_process *prc, t_a *a);

#endif
