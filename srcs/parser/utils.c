/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 21:34:40 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/10 05:16:31 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

int	is_whitespace(char c)
{
	if (!c || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_2dstrlen(char **str2d)
{
	int	i;

	i = 0;
	if (!str2d)
		return (i);
	while (str2d[i])
		i++;
	return (i);
}

int	empty_line(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_isprint(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	all_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
