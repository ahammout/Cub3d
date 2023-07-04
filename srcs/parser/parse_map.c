/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 04:46:55 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/04 01:25:40 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

char	*equalize_line(t_data *data, size_t i, size_t l)
{
	char	*new_line;
	int		j;
	int		sp;

	sp = l - ft_strlen(data->map[i]);
	new_line = malloc(sizeof (char) * l + 1);
	j = 0;
	while (data->map[i][j])
	{
		new_line[j] = data->map[i][j];
		j++;
	}
	while(sp > 0)
	{
		new_line[j] = ' ';
		j++;
		sp--;
	}
	new_line[j] = '\0';
	free(data->map[i]);
	return (new_line);
}

size_t	long_line(char **map)
{
	size_t i;
	size_t max;

	i = 1;
	max = ft_strlen(map[0]);
	while (map[i])
	{
		if (max < ft_strlen(map[i]))
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

void	equalize_map(t_data *data)
{
	size_t i;
	size_t	l;

	l = long_line(data->map);
	i = 0;
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) != l)
			data->map[i] = equalize_line(data, i, l);
		i++;
	}
}

int	one_player(char *line, int *player)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] == 'N' || line[i] == 'S' \
				|| line[i] == 'E' || line[i] == 'W')
				*player += 1;
			i++;
		}
		if (*player > 1)
			return (ft_putstr_fd("Cub3d: Multiple players", 2), -1);
	}
	return (0);
}

int	check_map(char *line)
{
	char	*comps;
	int		i;
	int		j;

	i = 0;
	if (!line)
		return (0);
	comps = ft_strdup("\nSWNE01 ");
	while (line[i])
	{
		j = 0;
		while (comps[j])
		{
			if (line[i] == comps[j])
				break ;
			j++;
		}
		if (!comps[j])
			return (ft_putstr_fd("Cub3d: Invalid comp", 2), -1);
		i++;
	}
	free(comps);
	return (0);
}

void	handle_map(t_data *data, int map_fd, char *holder)
{
	char	*line;
	int		player;
	char	*to_free;
	int		i;

	line = ft_strdup("");
	i = 0;
	player = 0;
	while (line)
	{
		free(line);
		line = get_next_line(map_fd);
		if (check_map(line) == -1 || one_player(line, &player) == -1)
			exit_error(data, 1, NULL);
		to_free = holder;
		holder = ft_strjoin(holder, line);
		if (line)
			free(to_free);
		i++;
	}
	if (player == 0)
		exit_error(data, 1, "Cub3d: The player is missing!");
	if (holder)
		data->map = ft_split(holder, '\n');
	free(holder);
	analyze_map(data);
	equalize_map(data);
}
