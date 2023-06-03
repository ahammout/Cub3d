/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:00:34 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/02 11:36:38 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

// void    add_node(t_list map, int *new_node)
// {
//     t_list  node;

//     if (new_node == 0)
//     {
        
//     }
    
// }

int direction_identifier(char *line)
{
    int i;

    i = 0;
    if (line[i] == 'S' && line[i + 1] == 'O' && is_whitespace(line[i + 2]) \
        || line[i] == 'W' && line[i + 1] == 'E' && is_whitespace(line[i + 2]) \
        || line[i] == 'N' && line[i + 1] == 'O' && is_whitespace(line[i + 2]) \
        || line[i] == 'E' && line[i + 1] == 'A' && is_whitespace(line[i + 2]))
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

// int map_handler(char *line)
// {
    
// }

int is_map_begin(char *line)
{
    int i;
    char *comps = "NSEA10";

    i = 0;
    comps = ft_strdup("NSEA10");
    while (line[i])
    {
        if ()
        i++;
    }
}

/// Function returns 0 in case of line validation, and returns -1 in case of error
int    check_line(char *line, t_map ptr)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (direction_identifier(line + i))
    {
        if (direction_handler(line + i) != 1)
        {
            ft_putstr_fd("Cub3d: Invalid identifier or path", 2);
            exit (EXIT_FAILURE);
        }
    }
    else if ((line[i] == C || line[i] == F) && is_whitespace(line[i + 1]))
    {
        if (floor_ceiling_handler(line + i) == -1)
            exit (EXIT_FAILURE);
    }
    else if (is_map_begin(line + i))
    {
        if (map_handler(line + i) == -1)
            exit (EXIT_FAILURE);
    }
    else if (white_check(line + i))
    {
        ft_putstr_fd("Cub3d: Invalid identifier or path", 2);
        exit (EXIT_FAILURE);
    }
    return (0);
    
}

bool

bool file_to_list(int map_fd, t_data *data)
{
    t_map   ptr;
    char     *line;
    int     new_node;

    init_data(data);
    new_node = 0;
    line = ft_strdup("");
    ptr = data->lmap;
    while (line)
    {
        free(line);
        line = get_next_line(map_fd);
        printf("%s\n", line);
        check_line (line, ptr);
        // add_node(map, &new_node);
        // map.line = ft_strdup(line);
    }
    // map = ptr;
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
    // Last_map_check.
    // map_table = list_to_table(map);
    //-----------------------------
    return (true);
    
}