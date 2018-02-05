/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/05 16:36:53 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <op.h>

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

void		ft_handle_line(t_a *a, char *ln, int num_ln);

#endif
