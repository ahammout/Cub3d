/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:00:34 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/07 18:57:08 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

char    **get_element(t_data *data, char *identifier)
{
    t_info  *ptr;

    ptr = data->info;
    while (data->info)
    {
        if (data->info->type == identifier)
            return (data->info->elem);
        data->info = data->info->next;
    }
    data->info = ptr;
    return (NULL);
}

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

int direction_identifier(t_data *data, char *line)
{
    int i;

    i = 0;
    if (line[i] == 'S' && line[i + 1] == 'O' && is_whitespace(line[i + 2]))
    {
        data->info->type = SO;
        return (1);
    }
    else if (line[i] == 'W' && line[i + 1] == 'E' && is_whitespace(line[i + 2]))
    {
        data->info->type = WE;
        return (1);
    }
    else if (line[i] == 'N' && line[i + 1] == 'O' && is_whitespace(line[i + 2])) 
    {
        data->info->type = NO;
        return (1);
    }
    else if(line[i] == 'E' && line[i + 1] == 'A' && is_whitespace(line[i + 2]))
    {
        data->info->type = EA;
        return (1);
    }
    return (0);
}

int handle_elements(char *line, t_data *data, t_info *ptr)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (direction_identifier(data, line + i))
        parse_directions(data, line + i, ptr);
    else if ((line[i] == 'C' || line[i] == 'F') && is_whitespace(line[i + 1]))
        parse_fc(data, line + i, ptr);
    else if (is_wall(line + i))
        return (1);
    else if (!empty_line(line + i))
    {
        data->info = ptr;
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
        {
            add_node(data, &node_index, &ptr);
            if (handle_elements(line, data, ptr))
                break;
            node_index++;
        }
    }
    data->info = ptr;
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
    printf ("End of parser\n");
    //-----------------------------
    return (true);
    
}