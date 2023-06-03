/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:00:34 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/03 23:45:42 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int direction_identifier(char *line)
{
    int i;

    i = 0;
    if ((line[i] == 'S' && line[i + 1] == 'O' && is_whitespace(line[i + 2])) \
        || (line[i] == 'W' && line[i + 1] == 'E' && is_whitespace(line[i + 2])) \
        || (line[i] == 'N' && line[i + 1] == 'O' && is_whitespace(line[i + 2])) \
        || (line[i] == 'E' && line[i + 1] == 'A' && is_whitespace(line[i + 2])))
    {
        return (1);
    }
    return (0);
}

int find_comma(char *line)
{
    int i;

    i = 0;
    while (line[i] != ',' && line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
        i++;
    return (i);
}

int get_color(char *line)
{
    int     color;
    char    *str;
    int     i;

    i = 0;
    str = ft_substr(line, 0, find_comma(line));
    printf ("the number: %s.\n", str);
    if (all_isdigit(str))
        color = ft_atoi(str);
    else
        color = -1;
    return (color);
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

int direction_handler(char *line)
{
    int path;
    int i;

    path = 0;
    i = 0;
    while (line[i])
    {
        while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
            i++;
        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
            i++;
        if (line[i] != '\0' && line[i] != '\n')
            path++;
    }
    return (path);
    
}

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

void map_handler(t_data *data, int map_fd)
{
    char    *line;

    line = ft_strdup("");
    while (line)
    {
        free(line);
        line = get_next_line(map_fd);
        if (check_map(line) == -1)
            exit_error(data, 1, NULL);
        data->map = str_to_2d(data, line);
    }
    if (fl_line(data->map[ft_2dstrlen(data->map) - 1]) == -1)
        exit_error(data, 1, "Cub3d: Map must be souronded by Walls");
}

bool file_to_list(int map_fd, t_data *data)
{
    t_map   *ptr;
    char     *line;
    int     node_index;

    line = ft_strdup("");
    ptr = NULL;
    node_index = 0;
    while (line)
    {
        add_node(data, &node_index, &ptr);
        free(line);
        line = get_next_line(map_fd);
        printf("%s\n", line);
        if (check_line (line, data, ptr) == 0)
            break;
        node_index++;
    }
    data->lmap = ptr;
    if (fl_line(line))
    {
        data->map = str_to_2d(data, line);
        free(line);
        map_handler(data, map_fd);
    }
    printf ("The map was parsed seccussfully");
    return (true);
}

bool    parser(char **av, t_data *data)
{
    int     map_fd;

    map_fd = open(av[1], O_RDONLY);
    if (map_fd == -1)
    {
        perror("Cub3d");
        exit (EXIT_FAILURE);
    }
    file_to_list(map_fd, data);
    display_list(data->lmap);
    // display_table(data->map);
    printf ("End of parser\n");
    //-----------------------------
    return (true);
    
}