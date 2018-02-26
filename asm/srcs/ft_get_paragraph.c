/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_paragraph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <atripard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:32:39 by atripard          #+#    #+#             */
/*   Updated: 2018/02/26 16:41:15 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

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

static char	*ft_check_paragraph(char *p)
{
	int len;

	len = ft_strlen(p);
	if (p[len - 1] != '"')
		ft_fruit(1, &p);
	return (p);
}

char		*ft_get_paragraph(int fd, int *num_ln, char *str)
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
	if ((count = ft_count_char(str + i, '\"')) == 2)
		return (ft_check_paragraph(p));
	else if (count > 2)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		++(*num_ln);
		if ((count = ft_count_char(line, '\"')) > 1 ||
			(!(p = ft_strjoin_ln(p, line))))
			return (NULL);
		if (count == 1)
			return (ft_check_paragraph(p));
	}
	return (NULL);
}
