/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:15:23 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/05 18:56:30 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int fl_line (char *line)
{
    int i;

    i = 0;
    if (empty_line(line))
        return (0);
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '1' && line[i] != '\n' && line[i] != '\0')
            return (0);
        i++;
    }
    return (1);
}

int find_comma(char *line)
{
    int i;

    i = 0;
    while (line[i] != ',' && line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
        i++;
    return (i);
}

int floor_ceiling_handler(char *line)
{
    int i;
    int color;
    int vals;
    int comma;

    i = 0;
    vals = 0;
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
        }
    }
    return (0);
}

int check_map(char *line)
{
    char    *comps;
    int     i;
    int     j;

    i = 0;
    if (!line)
        return (0);
    comps = ft_strdup("\nSWNA01 ");
    /// EMPTY LINE INSIDE THE MAP
    if (empty_line(line))
        return (ft_putstr_fd("Cub3d: Impty line inside the map", 2), -1);
    // while (line[i] != ' ' && line[i] != '\t')
    //     i++;
    // if (line[i] != '1')
    //     return (ft_putstr_fd("Cub3d: Map must be surrounded by walls", 2), -1);
    while (line[i])
    {
        j = 0;
        while (comps[j])
        {
            if (line[i] == comps[j])
                break;
            j++;
        }
        if (!comps[j])
        return (ft_putstr_fd("Cub3d: Invalid comp", 2), -1);
        i++;
    }
    // if (line[i - 1] != '1')
    //     return (ft_putstr_fd("Cub3d: Map must be surrounded by walls", 2), -1);
    return (0);
}

/// Function returns 0 in case of line validation, and returns -1 in case of error
int    check_elements(char *line, t_data *data, t_map *ptr)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (direction_identifier(line + i))
    {
        if (direction_handler(line + i) != 1)
        {
            data->lmap = ptr;
            exit_error(data, 1, "Cub3d: Invalid identifier or path");
        }
        else
        {
            data->lmap->line = ft_strdup(line + i);
            // type
        }
    }
    else if ((line[i] == C || line[i] == F) && is_whitespace(line[i + 1]))
    {
        if (floor_ceiling_handler(line + i) == -1)
        {
            data->lmap = ptr;
            exit_error(data, 1, NULL);
        }
        else
        {
            data->lmap->line = ft_strdup(line + i);
            /// type 
        }
    }
    /// THIS CASE IS ABOUT CHECK THE WEN THE MAP BEGINS!!
    else if (fl_line(line + i))
        return (1);
    else if (!empty_line(line + i))
    {
        printf ("The only exception: %s\n", line + i);
        data->lmap = ptr;
        exit_error(data, 1, "Cub3d: Invalid identifier or path");
    }
    return (0);
}