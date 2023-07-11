/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:23:35 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/11 22:30:06 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

void	check_empty_line(char **line)
{
	if (*line && empty_line(*line))
	{
		free(*line);
		*line = ft_strdup(" \n");
	}
}

int	check_extension(char *path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '.')
		{
			if (ft_strcmp(path + i, ".cub") == 0)
				return (1);
		}
		i++;
	}
	return (0);
}
