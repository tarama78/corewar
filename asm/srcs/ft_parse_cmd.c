/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <atripard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:20:48 by atripard          #+#    #+#             */
/*   Updated: 2018/02/26 17:57:21 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int			ft_invalid(char *trim, char **line)
{
	int		i;

	i = -1;
	{
		while (trim[++i] == ' ' || trim[i] == '\t')
			;
		if (trim[i] != COMMENT_CHAR && ft_fruit(2, line, &trim))
			return (1);
	}
	return (0);
}

static int			ft_get_cmd(int fd, int *num_ln, char **name, char **comment)
{
	char	*line;
	char	*trim;

	while (!(*name && *comment) && get_next_line(fd, &line) > 0 && ++(*num_ln))
	{
		if (!(trim = ft_strtrim(line)) && ft_fruit(1, &line))
			return (0);
		if (ft_strnequ(trim, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{
			if (*name && ft_fruit(2, &line, &trim))
				return (1 << 4);
			*name = ft_get_paragraph(fd, num_ln, trim);
		}
		else if (ft_strnequ(trim, COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)))
		{
			if (*comment && ft_fruit(2, &line, &trim))
				return (1 << 5);
			*comment = ft_get_paragraph(fd, num_ln, trim);
		}
		else if (trim[0] && ft_invalid(trim, &line))
			return (1 << 6);
		ft_fruit(2, &line, &trim);
	}
	return (0);
}

static inline void	ft_check_name(t_a *a, char *name, int *error)
{
	int		len;

	len = ft_strlen(name) - 1;
	if (len > 0 && len <= PROG_NAME_LENGTH && name[len] == '\"')
		ft_strncat(a->name, name, len);
	else if (len > PROG_NAME_LENGTH)
		*error |= 1 << 2;
	free(name);
}

static inline void	ft_check_comment(t_a *a, char *comment, int *error)
{
	int		len;

	len = ft_strlen(comment) - 1;
	if (len > 0 && len <= COMMENT_LENGTH && comment[len] == '\"')
		ft_strncat(a->comment, comment, len);
	else if (len > COMMENT_LENGTH)
		*error |= 1 << 2;
	free(comment);
}

void				ft_parse_cmd(int fd, t_a *a, int *num_ln, int *error)
{
	char	*name;
	char	*comment;

	name = NULL;
	comment = NULL;
	*error = ft_get_cmd(fd, num_ln, &name, &comment);
	if (name)
		ft_check_name(a, name, error);
	else
		*error |= 1 << 0;
	if (comment)
		ft_check_comment(a, comment, error);
	else
		*error |= 1 << 1;
}
