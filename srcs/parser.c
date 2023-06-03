/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:00:34 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/04 00:55:36 by ahammout         ###   ########.fr       */
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

bool handle_file(int map_fd, t_data *data)
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
        if (check_line (line, data, ptr))
        {
            printf ("Breaks here, nodes filled: %d\n", node_index);
            break;
        }
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
    handle_file(map_fd, data);
    display_list(data->lmap);
    // display_table(data->map);
    printf ("End of parser\n");
    //-----------------------------
    return (true);
    
}