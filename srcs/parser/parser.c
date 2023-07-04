/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:55:47 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/04 01:05:29 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

char	**get_element(t_data *data, int identifier)
{
	t_info	*tmp;

	tmp = data->info;
	while (tmp)
	{
		if (tmp->type == identifier)
			return (tmp->elem);
		tmp = tmp->next;
	}
	return (NULL);
}

int	detect_directions(t_data *data, char *line)
{
	int	i;

	i = 0;
	if (line[i] == 'S' && line[i + 1] == 'O' && is_whitespace(line[i + 2]))
		data->info->type = SO;
	else if (line[i] == 'W' && line[i + 1] == 'E' && is_whitespace(line[i + 2]))
		data->info->type = WE;
	else if (line[i] == 'N' && line[i + 1] == 'O' && is_whitespace(line[i + 2]))
		data->info->type = NO;
	else if (line[i] == 'E' && line[i + 1] == 'A' && is_whitespace(line[i + 2]))
		data->info->type = EA;
	if (data->info->type != 0)
		return (1);
	return (0);
}

int	handle_elements(char *line, t_data *data, t_info *ptr)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (detect_directions(data, line + i))
		parse_directions(data, line + i, ptr);
	else if ((line[i] == 'C' || line[i] == 'F') \
		&& is_whitespace(line[i + 1]))
		parse_fc(data, line + i, ptr);
	else if (is_wall(line + i))
		return (1);
	else if (!empty_line(line + i))
	{
		data->info = ptr;
		exit_error(data, 1, "Cub3d: Invalid identifier or path");
	}
	return (0);
}

void	handle_file(int map_fd, t_data *data)
{
	t_info	*ptr;
	char	*line;
	int		node_index;

	line = ft_strdup("");
	ptr = NULL;
	node_index = 0;
	while (line)
	{
		free(line);
		line = get_next_line(map_fd);
		if (!empty_line(line))
		{
			add_node(data, &node_index, &ptr);
			if (handle_elements(line, data, ptr))
				break ;
			node_index++;
		}
	}
	data->info = ptr;
	analyze_elements(data);
	if (is_wall(line))
		handle_map(data, map_fd, line);
}

bool	parser(char **av, t_data *data)
{
	int	map_fd;

	data->map = NULL;
	map_fd = open(av[1], O_RDONLY);
	if (map_fd == -1)
	{
		perror("Cub3d");
		exit (EXIT_FAILURE);
	}
	if (ft_strnstr(av[1], ".cub", ft_strlen(av[1])) == 0)
		exit_error(data, 1, "Cub3d: Invalid  map format");
	handle_file(map_fd, data);
	if (!data->info)
		exit_error(data, 1, "Cub3d: There is no elements on the file");
	if (!data->map)
		exit_error(data, 1, "Cub3d: There is no map on file");
	close(map_fd);
	// display_list(data->info);
	// display_table(data->map);
	return (true);
}
