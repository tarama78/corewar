/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <atripard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:49:13 by atripard          #+#    #+#             */
/*   Updated: 2018/02/22 20:49:22 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*ft_check_paragraph(char *p)
{
	int len;

	len = ft_strlen(p);
	if (p[len - 1] != '"')
		ft_fruit(1, &p);
	return (p);
}

static void	ft_clear_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		else if (str[i] == COMMENT_CHAR)
			str[i--] = '\0';
		++i;
	}
}

static int	ft_parse_line(int fd, t_a *a, int *num_ln, int *lines)
{
	char	*line;
	char	*trim;

	while (get_next_line(fd, &line) > 0)
	{
		++(*num_ln);
		ft_clear_line(line);
		if (!(trim = ft_strtrim(line)))
		{
			free(line);
			return (ERROR);
		}
		if (trim[0] && ++(*lines))
			if (ft_handle_line(a, trim, *num_ln) == ERROR)
			{
				ft_fruit(2, &trim, &line);
				return (ERROR);
			}
		ft_fruit(1, &trim);
		ft_fruit(1, &line);
	}
	return (SUCCESS);
}

int			ft_parse_file(t_a *a, int fd)
{
	int		num_ln;
	int		lines;
	int		cmd;

	cmd = 0;
	lines = 0;
	num_ln = 0;
	ft_parse_cmd(fd, a, &num_ln, &cmd);
	if (cmd != 3)
	{
		if (cmd == 0)
			ft_err_msg(a, NULL, "no name/comment", 0);
		else if (cmd == 1)
			ft_err_msg(a, NULL, "no comment", 0);
		else if (cmd == 2)
			ft_err_msg(a, NULL, "no name", 0);
		return (ERROR);
	}
	if (ft_parse_line(fd, a, &num_ln, &lines) == ERROR)
		return (ERROR);
	if (lines == 0)
		return (ft_err_msg(a, NULL, "No instructions", 0));
	ft_label(a);
	return (SUCCESS);
}
