/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/09 16:16:55 by ynacache         ###   ########.fr       */
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

/*
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
	uint8_t				mem[CHAMP_MAX_SIZE];
	int					mem_size;
	int					player_number_print;
	int					last_live_cycle;
	int					nb_live_total;
	int					nb_live_current;
	size_t				nb_process;
}						t_player;

*/
typedef struct			s_champ_file
{
	int					player_number_print;	
	char				*filename;
}						t_champ_file;

typedef struct			s_a
{
//	t_process			*process;
//	t_player			player[MAX_PLAYER];
	t_champ_file		file[MAX_PLAYERS];
	int					num_of_player;
	int					dump_cycle;
	int					cycle_to_die;
	uint64_t			cycle;
	uint8_t				mem[MEM_SIZE];
}						t_a;

int	ft_is_uint(char *str, int *num);

#endif
