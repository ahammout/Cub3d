/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:52:13 by ahammout          #+#    #+#             */
/*   Updated: 2023/05/29 17:03:26 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int is_whitespace(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int	white_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int all_isdigit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}