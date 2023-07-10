/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 03:38:44 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/10 03:39:08 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

int	is_direction(char c)
{
	if (c == 'E' || c == 'S' || c == 'N' || c == 'W')
		return (1);
	return (0);
}

char	*open_path(char *line)
{
	char	*path;
	int		fd;
	int		i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	path = ft_strtrim(line + i, "\n ");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	close(fd);
	return (path);
}

int	check_path(char *line)
{
	int	path;
	int	i;

	path = 0;
	i = 0;
	if (line)
	{
		while (line[i])
		{
			while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
				i++;
			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			if (line[i] != '\0' && line[i] != '\n')
				path++;
		}
	}
	return (path);
}

void	parse_directions(t_data *data, char *line, t_info *ptr)
{
	char	*path;

	if (check_path(line) != 1)
	{
		data->info = ptr;
		exit_error(data, 1, "Cub3d: Invalid identifier or path\n");
	}
	path = open_path(line);
	if (path == NULL)
		exit_error(data, 1, "Cub3d: Invalid texture file\n");
	data->info->elem = malloc(sizeof(char *) * 2);
	data->info->elem[0] = ft_strdup(path);
	data->info->elem[1] = NULL;
	free(path);
}
