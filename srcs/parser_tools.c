/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:49:26 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/04 00:58:31 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int fl_line (char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' || line[i] != '\t' || line[i] != '1' || line[i] != '\n' || line[i] != '\0')
            return (0);
        i++;
    }
    return (1);
}

/// Function returns 0 in case of line validation, and returns -1 in case of error
int    check_line(char *line, t_data *data, t_map *ptr)
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
    else if (fl_line(line + i))
        return (1);
    else if (white_check(line + i))
    {
        printf ("The only exception: %s\n", line + i);
        data->lmap = ptr;
        exit_error(data, 1, "Cub3d: Invalid identifier or path");
    }
    return (0);
}

int check_map(char *line)
{
    char    *comps;
    int     i;
    int     j;

    i = 0;
    j = 0;
    comps = ft_strdup("SWNA01 ");
    /// EMPTY LINE INSIDE THE MAP
    if (white_check(line) == 0)
        return (-1);
    while (line[i])
    {
        while (comps[j])
        {
            if (line[i] != comps[j])
                return (-1);
            j++;
        }
        i++;
    }
    return (0);
}