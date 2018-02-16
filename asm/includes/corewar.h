/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:28:54 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/16 15:57:54 by ynacache         ###   ########.fr       */
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
t_lst				*ft_lst_get_last(t_lst *lst);
void				ft_lst_add_end(t_lst **begin, t_lst *new);
char				*ft_get_name(char *ln);
int					ft_get_size_op(t_a *a, t_op *op, char **arg, t_line *new_l);
char				*ft_get_clean_ln(t_a *a, char *ln, t_line *new_ln);
int					ft_start_i(t_a *a, char *ln, int label);
char				*ft_clean_char_custom(char *s);
int					ft_handle_line(t_a *a, char *ln, int num_ln);
void				ft_label(t_a *data);
int					free_content(t_a *data, char *error);
int					ft_parse_file(t_a *a, int fd);
void				ft_parse_cmd(int fd, t_a *a, int *num_ln, int *cmd);
int					ft_label_address(char *label, t_label *tab_label,
																	t_a *data);
int					ft_handle_args(int file, char *arg, t_a *data, int index);
int					ft_typepara(char *arg);
void				ft_encoding(int file, char **words);
void				ft_putname_magic(int file, t_a *data);
int					ft_binary(int file, t_a *data);

#endif
