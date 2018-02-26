/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_line_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <atripard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:55:21 by tnicolas          #+#    #+#             */
/*   Updated: 2018/02/26 14:45:47 by ynacache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | ft_handle_line_3.c                                       |
**   |     ft_start_i(14 lines)                                 |
**   |     ft_clean_char_custom(24 lines)                       |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <corewar.h>

char		*ft_check_endline(t_a *a, char *ln, int num_ln)
{
	t_line	line;
	char	c;
	char	*ptr;

	c = ln[ft_strlen(ln) - 1];
	if (c == DIRECT_CHAR || c == SEPARATOR_CHAR)
	{
		line.line = ln;
		line.num_line = num_ln;
		ft_err_msg(a, &line, "invalid line", 0);
		ptr = &c;
		return (ptr);
	}
	return (NULL);
}

int			ft_start_i(t_a *a, char *ln, int label)
{
	int		i;

	i = -1;
	while (ft_strchr(LABEL_CHARS, ln[++i]) && ln[i])
		;
	if (ln[i] == LABEL_CHAR)
	{
		while (ln[++i] == ' ' || ln[i] == '\t')
			;
		if (label)
			a->nb_label++;
		return (i + ft_start_i(a, ln + i, label));
	}
	return (0);
}

char		*ft_clean_char_custom(char *s)
{
	int		i;
	int		j;
	char	*ret;

	if (!(ret = ft_strtrim(s)))
		return (NULL);
	i = -1;
	while (ret[++i])
		if (ret[i] == SEPARATOR_CHAR)
		{
			j = 0;
			while (ret[i - j - 1] == ' ')
				++j;
			if (j > 0)
				ft_memmove(ret + i - j, ret + i, ft_strlen(ret + i) + 1);
			i -= j;
			j = 0;
			while (ret[i + j + 1] == ' ')
				++j;
			if (j > 0)
				ft_memmove(ret + i + 1, ret + i + j + 1,
						ft_strlen(ret + i + j + 1) + 1);
		}
	return (ret);
}
