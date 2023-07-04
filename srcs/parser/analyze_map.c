/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 03:13:33 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/04 13:27:34 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

int	is_wall(char *line)
{
	int	i;

	i = 0;
	if (empty_line(line))
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' \
			&& line[i] != '1' && line[i] != '\n' \
			&& line[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	check_sides(t_data *data)
{
	int	y;

	y = 1;
	while (data->map[y + 1])
	{
		if ((data->map[y][ft_strlen(data->map[y]) - 1] != '1' \
			&& data->map[y][ft_strlen(data->map[y]) - 1] != ' ') \
			|| (data->map[y][0] != '1' && data->map[y][0] != ' '))
			return (-1);
		y++;
	}
	if (!is_wall(data->map[ft_2dstrlen(data->map) - 1]))
		return (-1);
	return (0);
}

int	surrounded_map(t_data *data)
{
	int	x;
	int	y;

	if (check_sides(data) == -1)
		return (-1);
	y = 1;
	while (data->map[y + 1])
	{
		x = 0;
		while (data->map[y][x])
		{
			/// This condition will make the function over 25 lines
			if (data->map[y][x] == 'S' || data->map[y][x] == 'W' \
				|| data->map[y][x] == 'N' || data->map[y][x] == 'E')
			{
				data->p_x = x;
				data->p_y = y;
			}
			if (data->map[y][x] == '0' || is_direction(data->map[y][x]))
			{
				if (is_whitespace(data->map[y - 1][x]) \
					||is_whitespace(data->map[y + 1][x]) \
					||is_whitespace(data->map[y][x + 1]) \
					||is_whitespace(data->map[y][x - 1]))
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	cut_empty_lines(t_data *data)
{
	int		i;

	i = ft_2dstrlen(data->map) - 1;
	while (empty_line(data->map[i]))
	{
		free(data->map[i]);
		data->map[i] = NULL;
		i--;
	}
}

void	analyze_map(t_data *data)
{
	int	i;

	cut_empty_lines(data);
	i = 0;
	while (data->map[i])
	{
		if (empty_line(data->map[i]))
			exit_error(data, 1, "Cub3d: Empty line inside the map!");
		i++;
	}
	if (surrounded_map(data) == -1)
		exit_error(data, 1, "Cub3d: Map must be souronded by Walls");
}
