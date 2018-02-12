/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atripard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:58:32 by atripard          #+#    #+#             */
/*   Updated: 2018/01/19 19:07:55 by atripard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int	ft_is_uint(char *str, int *num)
{
	int		i;
	long	number;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	if (i > 11)
		return (0);
	number = ft_atol(str);
	if (number > 2147483647 || number < -2147483647)
		return (0);
	*num = number;
	return (1);
}
