/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/06 18:17:47 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <stdlib.h>

typedef struct		s_op
{
	char			*name;
	int				nb_arg;
	int				type_arg[3];
	int				opcode;
	int				nb_cycle;
	char			*descrition;
	int				ok_codage;
	int				jesaispas2;
}					t_op;

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
	char			*file_name;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	t_line			*tab_line;
	int				nb_label;
	t_label			*tab_label;
}					t_a;

void		ft_handle_line(t_a *a, char *ln, int num_ln);

#endif
