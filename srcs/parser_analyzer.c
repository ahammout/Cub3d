/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:15:23 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/06 14:44:30 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int is_wall (char *line)
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

int check_map(char *line)
{
    char    *comps;
    int     i;
    int     j;

    i = 0;
    if (!line)
        return (0);
    comps = ft_strdup("\nSWNA01 ");
    if (empty_line(line))
        return (ft_putstr_fd("Cub3d: Impty line inside the map", 2), -1);
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
    return (0);
}

/// Function returns 0 in case of line validation, and returns -1 in case of error
