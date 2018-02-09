/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/09 22:34:55 by bcozic           ###   ########.fr       */
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
	int					reg[NB_REG];
	int					pc;
	int					cycle_wait;
	bool				carry;
	bool				live;
}						t_process;

typedef struct			s_player
{
	char				name[NAME_SIZE + 1];
	char				comment[COMMENT_SIZE + 1];
	int					player_number_print;
	int					last_live_cycle;
	int					nb_live_total;
	int					nb_live_current;
	size_t				nb_process;
}						t_player;

typedef struct			s_a
{
	t_process			*process;
	t_player			player[MAX_PLAYER];
	int					cycle_to_die;
	uint64_t			cycle;
	uint8_t				mem[MEM_SIZE];
}						t_a;

int						check_cycle(t_process *prc, t_a *a);
int						rec_memory(char type, int *curs, t_a *a, int addr);
int						check_type(t_process *prc, t_a *a);

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

#endif
