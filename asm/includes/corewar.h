/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/06 10:58:49 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <op.h>
# include <libft.h>

typedef struct		s_op
{
	char			*name;
	int				nb_arg;
	int				type_arg[3];
	int				opcode;
	int				nb_cycle;
	char			*descrition;
	int				jesaispas1;
	int				jesaispas2;
}					t_op;

extern t_op			op_tab[17];

typedef struct		s_line
{
	struct s_line	*next;
	char			*line;
	int				size;
}					t_line;

typedef struct		s_label
{
	char			*name;
	int				addr;
}					t_label;

typedef struct		s_a
{
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	t_line			*line;
	int				nb_label;
	t_label			*label;
}					t_a;

typedef struct		s_lst
{
	struct s_lst	*next;
}					t_lst;

void		ft_lst_add_end(t_lst **begin, t_lst *new);
void		ft_handle_line(t_a *a, char *ln, int num_ln);

#endif
