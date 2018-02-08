/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:49:13 by atripard          #+#    #+#             */
/*   Updated: 2018/02/08 12:12:10 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char	*ft_strjoin_ln(char *s1, char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (0);
	if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	ft_strcat(str, s1);
	ft_strcat(str, "\n");
	ft_strcat(str, s2);
	free(s1);
	free(s2);
	return (str);
}

static int		ft_count_char(char *str, char c)
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
	char *line;
	char *p;
	int count;
	int	i;

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

static int		ft_get_cmd(int fd, int *num_ln, char **name, char **comment)
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
		free(line);
		if (ft_strnequ(trim, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			*name = ft_get_paragraph(fd, num_ln, trim);
		else if (ft_strnequ(trim, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
			*comment = ft_get_paragraph(fd, num_ln, trim);
		free(trim);
	}
	return (1);
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

static int		ft_parse_line(int fd, t_a *a, int *num_ln)
{
	char *line;
	char *trim;

	while (get_next_line(fd, &line) > 0)
	{
		++(*num_ln);
		ft_clear_line(line);
		if (!(trim = ft_strtrim(line)))
		{
			free(line);
			return (0);
		}
		if (trim[0])
			if (ft_handle_line(a, trim, *num_ln) == ERROR)
			{
				ft_fruit(2, trim, line);
				return (ERROR);
			}
		free(trim);
		free(line);
	}
	return (1);
}


static void	ft_parse_cmd(int fd, t_a *a, int *num_ln)
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
	}
	if (comment)
	{
		len = ft_strlen(comment) - 1;
		if (len > 0 && len <= COMMENT_LENGTH && comment[len] == '\"')
			ft_strncat(a->comment, comment, len);
		free(comment);
	}
	else
		ft_warning_msg(a, NULL, "no comment");
}

int		ft_parse_file(t_a *a, int fd)
{
	int		num_ln;

	num_ln = 0;
	ft_parse_cmd(fd, a, &num_ln);
	if (!a->name[0])
		return (ERROR);
	if (ft_parse_line(fd, a, &num_ln) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
