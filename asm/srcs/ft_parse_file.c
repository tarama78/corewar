/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <atripard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:49:13 by atripard          #+#    #+#             */
/*   Updated: 2018/02/26 17:33:50 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

int			ft_err_msg_header(t_a *a, int err)
{
	if (err & (1 << 2))
		return (ft_err_msg(a, NULL, "name too long", 0));
	if (err & (1 << 4))
		return (ft_err_msg(a, NULL, "mutiple name", 0));
	if (err & (1 << 0))
		return (ft_err_msg(a, NULL, "no name", 0));
	if (err & (1 << 6))
		return (ft_err_msg(a, NULL, "don't shit between name and comment", 0));
	if (err & (1 << 3))
		return (ft_err_msg(a, NULL, "comment too long", 0));
	if (err & (1 << 5))
		return (ft_err_msg(a, NULL, "multiple comment", 0));
	if (err & (1 << 1))
		return (ft_err_msg(a, NULL, "no comment", 0));
	return (ERROR);
}

int			ft_parse_file(t_a *a, int fd)
{
	int		num_ln;
	int		lines;
	int		error;

	error = 0;
	lines = 0;
	num_ln = 0;
	ft_parse_cmd(fd, a, &num_ln, &error);
	if (error)
		return (ft_err_msg_header(a, error));
	if (ft_parse_line(fd, a, &num_ln, &lines) == ERROR)
		return (ERROR);
	if (lines == 0)
		return (ft_err_msg(a, NULL, "No instructions", 0));
	ft_label(a);
	return (SUCCESS);
}
