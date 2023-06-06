/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:00:34 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/06 04:16:23 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int closed_map(t_data *data)

int get_pure_paths(t_data *data);

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

void handle_map(t_data *data, int map_fd, char *holder)
{
    char    *line;
    char    *to_free;
    int     i;

    line = ft_strdup("");
    i = 0;
    while (line)
    {
        free(line);
        line = get_next_line(map_fd);
        if (check_map(line) == -1)
            exit_error(data, 1, NULL);
        to_free = holder;
        holder = ft_strjoin(holder, line);
        if (line)
            free(to_free);
        i++;
    }
    build_map(data, holder);
    if (!is_wall(data->map[ft_2dstrlen(data->map) - 1]) && !closed_map(data))
        exit_error(data, 1, "Cub3d: Map must be souronded by Walls");
    
}


int handle_elements(char *line, t_data *data, t_map *ptr)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (direction_identifier(line + i))
    {
        if (check_path(line + i) != 1)
        {
            data->lmap = ptr;
            exit_error(data, 1, "Cub3d: Invalid identifier or path");
        }
        else
            data->lmap->line = ft_strdup(line + i);
    }
    else if ((line[i] == C || line[i] == F) && is_whitespace(line[i + 1]))
    {
        if (check_fc(line + i) == -1)
        {
            data->lmap = ptr;
            exit_error(data, 1, NULL);
        }
        else
            data->lmap->line = ft_strdup(line + i);
    }
    else if (is_wall(line + i))
        return (1);
    else if (!empty_line(line + i))
    {
        data->lmap = ptr;
        exit_error(data, 1, "Cub3d: Invalid identifier or path");
    }
    return (0);
}

void handle_file(int map_fd, t_data *data)
{
    t_info   *ptr;
    char     *line;
    int     node_index;

    line = ft_strdup("");
    ptr = NULL;
    node_index = 0;
    while (line)
    {
        free(line);
        line = get_next_line(map_fd);
        if (!empty_line(line))
            add_node(data, &node_index, &ptr);
        if (handle_elements(line, data, ptr))
            break;
        node_index++;
    }
    data->lmap = ptr;
    if(!get_pure_paths(data))
        exit_error(data, 1, "Cub3d: Invalid path");
    if (is_wall(line))
        handle_map(data, map_fd, line);    
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
    display_list(data->info);
    display_table(data->map);
    // printf ("End of parser\n");
    //-----------------------------
    return (true);
    
}