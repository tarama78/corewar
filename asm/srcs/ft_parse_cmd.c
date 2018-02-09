/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:20:48 by atripard          #+#    #+#             */
/*   Updated: 2018/02/09 11:30:54 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char	*ft_strjoin_ln(char *s1, char *s2)
{
	char	*str;

	str = NULL;
	if (s1 && s2 && (str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
	{
		ft_strcat(str, s1);
		ft_strcat(str, "\n");
		ft_strcat(str, s2);
	}
	free(s1);
	free(s2);
	return (str);
}

static int	ft_count_char(char *str, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			++count;
		++i;
	}
	return (count);
}

static char	*ft_get_paragraph(int fd, int *num_ln, char *str)
{
	char	*line;
	char	*p;
	int		count;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\"')
		++i;
	if (!(str[i]))
		return (NULL);
	p = ft_strdup(str + i + 1);
	if (ft_count_char(str + i, '\"') == 2)
		return (p);
	while (get_next_line(fd, &line) > 0)
	{
		++(*num_ln);
		count = ft_count_char(line, '\"');
		if (!(p = ft_strjoin_ln(p, line)))
			return (NULL);
		if (count == 1)
			return (p);
	}
	return (NULL);
}

static int	ft_get_cmd(int fd, int *num_ln, char **name, char **comment)
{
	char	*line;
	char	*trim;

	*name = NULL;
	*comment = NULL;
	while (!(*name && *comment) && get_next_line(fd, &line) > 0)
	{
		++(*num_ln);
		if (!(trim = ft_strtrim(line)))
		{
			free(line);
			return (0);
		}
		if (ft_strnequ(trim, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			*name = ft_get_paragraph(fd, num_ln, trim);
		else if (ft_strnequ(trim, COMMENT_CMD_STRING,
					ft_strlen(COMMENT_CMD_STRING)))
			*comment = ft_get_paragraph(fd, num_ln, trim);
		free(line);
		free(trim);
	}
	return (1);
}

void		ft_parse_cmd(int fd, t_a *a, int *num_ln, int *cmd)
{
	char	*name;
	char	*comment;
	int		len;

	ft_get_cmd(fd, num_ln, &name, &comment);
	if (name)
	{
		len = ft_strlen(name) - 1;
		if (len > 0 && len <= PROG_NAME_LENGTH && name[len] == '\"')
			ft_strncat(a->name, name, len);
		free(name);
		*cmd += 1;
	}
	if (comment)
	{
		len = ft_strlen(comment) - 1;
		if (len > 0 && len <= COMMENT_LENGTH && comment[len] == '\"')
			ft_strncat(a->comment, comment, len);
		free(comment);
		*cmd += 2;
	}
}
