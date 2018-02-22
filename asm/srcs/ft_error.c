/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:35:14 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/08 17:19:24 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | ft_error.c                                               |
**   |     ft_err_msg(16 lines)                                 |
**   |     ft_warning_msg(8 lines)                              |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <corewar.h>

int			ft_err_msg(t_a *a, t_line *new_ln, char *txt, int quit)
{
	if (new_ln && a)
		ft_errprintf("\t{red}{bold}ERROR:{eoc} {yellow}%s.s\n{eoc}"
				"\t\t{yellow}{bold}line: %d{eoc} ->{bold} %s{eoc}\n"
				"\t\t%s\n", a->file_name, new_ln->num_line, txt, new_ln->line);
	else if (a)
		ft_errprintf("\t{red}{bold}ERROR:{eoc} {yellow}%s.s\n{eoc}"
				"\t\t%s\n", a->file_name, txt);
	else if (new_ln)
		ft_errprintf("\t{red}{bold}ERROR:{eoc}"
				"\t\t{yellow}{bold}line: %d{eoc} ->{bold} %s{eoc}\n"
				"\t\t%s\n", new_ln->num_line, txt, new_ln->line);
	else
		ft_errprintf("\t{red}{bold}ERROR:{eoc}\t\t%s\n", txt);
	if (quit)
	{
		ft_printf("{red}{bold}compilation failed\n{eoc}");
		exit(EXIT_FAILURE);
	}
	return (ERROR);
}

int			ft_warning_msg(t_a *a, t_line *new_ln, char *txt)
{
	if (new_ln)
		ft_errprintf("\t{magenta}{bold}WARNING:{eoc} {yellow}%s.s\n{eoc}"
				"\t\t{yellow}{bold}line: %d{eoc} ->{bold} %s{eoc}\n"
				"\t\t%s\n", a->file_name, new_ln->num_line, txt, new_ln->line);
	else
		ft_errprintf("\t{magenta}{bold}WARNING:{eoc} {yellow}%s.s\n{eoc}"
				"\t\t%s\n", a->file_name, txt);
	return (SUCCESS);
}
