/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 04:46:55 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/10 04:50:40 by ahammout         ###   ########.fr       */
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
	while (sp > 0)
	{
		new_line[j] = ' ';
		j++;
		sp--;
	}
	new_line[j] = '\0';
	free(data->map[i]);
	return (new_line);
}

void	equalize_map(t_data *data)
{
	size_t	i;
	size_t	long_;

	i = 1;
	long_ = ft_strlen(data->map[0]);
	while (data->map[i])
	{
		if (long_ < ft_strlen(data->map[i]))
			long_ = ft_strlen(data->map[i]);
		i++;
	}
	i = 0;
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) != long_)
			data->map[i] = equalize_line(data, i, long_);
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
			return (ft_putstr_fd("Cub3d: Multiple players\n", 2), -1);
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
			return (ft_putstr_fd("Cub3d: Invalid comp\n", 2), -1);
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

	line = ft_strdup("");
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
	}
	if (player == 0)
		exit_error(data, 1, "Cub3d: The player is missing!\n");
	if (holder)
		data->map = ft_split(holder, '\n');
	free(holder);
	analyze_map(data);
	equalize_map(data);
}
