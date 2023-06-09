/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 03:40:28 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/28 01:25:40 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int get_color(char *line)
{
    int     color;
    char    *str;

    str = ft_substr(line, 0, find_comma(line));
    if (all_isdigit(str))
        color = ft_atoi(str);
    else
        color = -1;
    free(str);
    return (color);
}

int find_comma(char *line)
{
    int i;

    i = 0;
    while (line[i] != ',' && line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
        i++;
    return (i);
}

///@note This function needs to  be short
int check_fc(t_data *data, char *line)
{
    int i;
    int color;
    int vals;
    int comma;

    i = 0;
    vals = 0;
    if (line[0] == 'C')
        data->info->type = C;
    else if(line[0] == 'F')
        data->info->type = F;
    while (line[i])
    {
        comma = 0;
        while (line[i] != ',' && line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
            i++;
        while (line[i] && (line[i] == ',' || line[i] == ' ' || line[i] == '\t'))
        {
            if (line[i] == ',')
                comma++;
            if (comma > 1)
                return (ft_putstr_fd("Cub3d: Multiple commas between RGB values", 2), -1);
            i++;
        }
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
        {
            vals ++;
            color = get_color(line + i);
            if (!(color >= 0 && color <= 255) || (vals > 3) || color == -1)
                return (ft_putstr_fd ("Cub3d: RGB out of the range", 2), -1);
            else
            {
                data->info->elem[vals - 1] = ft_itoa(color);
            }
        }
    }
    return (0);
}

void    parse_fc(t_data *data, char *line, t_info *ptr)
{
    data->info->elem = malloc(sizeof(char *)  * 4);
    data->info->elem[3] = NULL;
    if (check_fc(data, line) == -1)
    {
        data->info = ptr;
        exit_error(data, 1, NULL);
    }
}

// int	find_comma(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i] != ',' && line[i] != ' ' 
// 		&& line[i] != '\n' && line[i] != '\0')
// 		i++;
// 	return (i);
// }

// int	get_color(char *line)
// {
// 	int		color;
// 	char	*str;

// 	str = ft_substr(line, 0, find_comma(line));
// 	if (all_isdigit(str))
// 		color = ft_atoi(str);
// 	else
// 		color = -1;
// 	free(str);
// 	return (color);
// }

// int	check_comma(char *line)
// {
// 	int comma;
// 	int	i;

// 	comma = 0;
// 	i = 0;
// 	while (line[i] != ',' && line[i] != ' ' 
// 		&& line[i] != '\t' && line[i] != '\0')
// 		i++;
// 	while (line[i] && (line[i] == ',' || 
// 		line[i] == ' ' || line[i] == '\t'))
// 	{
// 		if (line[i] == ',')
// 			comma++;
// 		if (comma > 1)
// 			return (ft_putstr_fd("Cub3d: Bad rgb format", 2), -1);
// 		i++;
// 	}
// 	return (i);
// }

// int	check_fc(t_data *data, char *line)
// {
// 	int vals;
// 	int color;
// 	int	i;

// 	i = 0;
// 	vals = 0;
// 	while (line[i])
// 	{
// 		while (line[i] != ',' && line[i] != ' ' 
// 			&& line[i] != '\t' && line[i] != '\0')
// 		i++;
// 		i += check_comma(line);
// 		if (i == -1)
// 			return (-1);
// 		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
// 		{
// 			vals ++;
// 			color = get_color(line + i);
// 			if (!(color >= 0 && color <= 255) || (vals > 3) || color == -1)
// 			{
// 				printf("Throwed from here\n");
// 				printf("Causes:\n Color: %d\nRGB: %d\n", color, vals);
// 				return (ft_putstr_fd ("Cub3d: rgb out of the range", 2), -1);
// 			}
// 			else
// 				data->info->elem[vals - 1] = ft_itoa(color);
// 		}
// 	}
// 	return (0);
// }

// void	parse_fc(t_data *data, char *line, t_info *ptr)
// {
// 	data->info->elem = malloc(sizeof(char *)  * 4);
// 	data->info->elem[3] = NULL;
// 	if (line[0] == 'C')
// 		data->info->type = C;
// 	else if (line[0] == 'F')
// 		data->info->type = F;
// 	if (check_fc(data, line) == -1)
// 	{
// 		data->info = ptr;
// 		exit_error(data, 1, NULL);
// 	}
// }
