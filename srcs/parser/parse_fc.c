/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 04:31:36 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/10 04:31:38 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

int	find_comma(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ',' && line[i] != ' ' \
		&& line[i] != '\n')
		i++;
	return (i);
}

int	get_color(char *line)
{
	int		color;
	char	*str;

	str = ft_substr(line, 0, find_comma(line));
	if (all_isdigit(str))
		color = ft_atoi(str);
	else
		color = -1;
	free(str);
	return (color);
}

int	comma_cont(char *line, int *cm_ptr, int *i_ptr)
{
	int	i;
	int	comma;

	i = *i_ptr;
	comma = *cm_ptr;
	while (line[i] && line[i] != ',' && line[i] != ' ' && line[i] != '\t')
			i++;
	while (line[i] && (line[i] == ',' || line[i] == ' ' || line[i] == '\t'))
	{
		if (line[i] == ',')
			comma++;
		if (comma > 1)
			return (ft_putstr_fd("Cub3d: duplicated commas\n", 2), -1);
		i++;
	}
	*cm_ptr = comma;
	*i_ptr = i;
	return (0);
}

int	check_fc(t_data *data, char *line)
{
	int	i;
	int	j;
	int	color;
	int	comma;

	i = 0;
	j = 0;
	while (line[i])
	{
		comma = 0;
		data->info->elem[j] = NULL;
		if (comma_cont(line, &comma, &i) == -1)
			return (-1);
		if (line[i] != ' ' && line[i] != '\t' \
			&& line[i] != '\0' && line[i] != '\n')
		{
			color = get_color(line + i);
			if (!(color >= 0 && color <= 255) || (j >= 3) || (color == -1))
				return (ft_putstr_fd ("Cub3d: bad RGB values\n", 2), -1);
			else
				data->info->elem[j] = ft_itoa(color);
			j ++;
		}
	}
	return (0);
}

void	parse_fc(t_data *data, char *line, t_info *ptr)
{
	data->info->elem = malloc(sizeof(char *) * 4);
	if (line[0] == 'C')
		data->info->type = C;
	else if (line[0] == 'F')
		data->info->type = F;
	if (check_fc(data, line) == -1)
	{
		data->info = ptr;
		exit_error(data, 1, NULL);
	}
}
