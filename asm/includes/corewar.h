/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/08 18:11:54 by tnicolas         ###   ########.fr       */
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

typedef struct		s_line
{
	struct s_line	*next;
	char			*line;
	int				num_line;
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
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	t_line			*line;
	t_label			*label;
	int				nb_label;
	int				cmpt;
	int				prog_size;
}					t_a;

typedef struct		s_lst
{
	struct s_lst	*next;
}					t_lst;

int					ft_err_msg(t_a *a, t_line *new_ln, char *txt, int quit);
int					ft_warning_msg(t_a *a, t_line *new_ln, char *txt);
void				ft_lst_add_end(t_lst **begin, t_lst *new);
int					ft_handle_line(t_a *a, char *ln, int num_ln);
void				ft_label(t_a *data);
int					free_content(t_a *data, char *error);
int					ft_parse_file(t_a *a, int fd);
int					ft_binary(int file, t_a *data);

#endif
