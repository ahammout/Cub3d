/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:00:34 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/05 18:50:48 by ahammout         ###   ########.fr       */
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

int get_color(char *line)
{
    int     color;
    char    *str;
    int     i;

    i = 0;
    str = ft_substr(line, 0, find_comma(line));
    if (all_isdigit(str))
        color = ft_atoi(str);
    else
        color = -1;
    free(str);
    return (color);
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

void    build_map(t_data *data, char *line)
{
    int i;
    int j;
    int s;

    i = 0;
    s = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '\n')
            s++;   
        i++;
    }
    i = 0;
    data->map = malloc(sizeof(char *) * s + 1);
    while(line[i])
    {
        data->map[j] = ft_substr(line + i, 0, find_char(line + i, '\n'));
        i += (find_char(line + i, '\n') + 1);
        j++;
    }
    data->map[j] = NULL;
}

void map_handler(t_data *data, int map_fd, char *holder)
{
    char    *line;
    char    *to_free;
    int     i;

    line = ft_strdup("");
    // printf("GET INTO THE MAP HANDLER\n");
    i = 0;
    while (line)
    {
        free(line);
        line = get_next_line(map_fd);
        if (check_map(line) == -1)
            exit_error(data, 1, NULL);
        // if line is Valid: join it with prev holder, PB: use ft_strjoin_free(char *)
        to_free = holder;
        holder = ft_strjoin(holder, line);
        if (line)
            free(to_free);
        i++;
    }
    build_map(data, holder);
    if (!fl_line(data->map[ft_2dstrlen(data->map) - 1]))
        exit_error(data, 1, "Cub3d: Map must be souronded by Walls");
}

void handle_file(int map_fd, t_data *data)
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
        if (check_elements(line, data, ptr))
            break;
        node_index++;
    }
    data->lmap = ptr;
    if (fl_line(line))
        map_handler(data, map_fd, line);
    // printf ("The map was parsed seccussfully");
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
    display_table(data->map);
    // printf ("End of parser\n");
    //-----------------------------
    return (true);
    
}